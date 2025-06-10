#include "ParkingController.h"

Define_Module(ParkingController);

ParkingController::ParkingController() {
    nextArrivalEvent = nullptr;
    simulationEndEvent = nullptr;
    vehicleIdCounter = 0;
    totalArrivals = 0;
    totalDepartures = 0;
    maxQueueLength = 0;
    totalWaitingTime = 0;
}

ParkingController::~ParkingController() {
    cancelAndDelete(nextArrivalEvent);
    cancelAndDelete(simulationEndEvent);

    for (auto& pair : sensorRepairEvents) {
        cancelAndDelete(pair.second);
    }
}

void ParkingController::initialize() {
    numSlots = par("numSlots");
    arrivalRate = par("arrivalRate");
    avgParkingDuration = par("avgParkingDuration");
    simulationTime = par("simulationTime");
    sensorMalfunctionRate = par("sensorMalfunctionRate");
    sensorRepairTime = par("sensorRepairTime");

    slotOccupied.resize(numSlots, false);
    slotSensorWorking.resize(numSlots, true);

    queueLengthSignal = registerSignal("queueLength");
    occupiedSlotsSignal = registerSignal("occupiedSlots");
    waitingTimeSignal = registerSignal("waitingTime");
    utilizationRateSignal = registerSignal("utilizationRate");
    vehicleArrivalSignal = registerSignal("vehicleArrival");
    vehicleDepartureSignal = registerSignal("vehicleDeparture");

    nextArrivalEvent = new NextArrival();
    scheduleAt(simTime(), nextArrivalEvent);

    simulationEndEvent = new SimulationEnd();
    scheduleAt(simulationTime, simulationEndEvent);

    scheduleSensorMalfunction();

    EV << "Smart Parking Controller initialized with " << numSlots << " slots" << endl;
}

void ParkingController::handleMessage(cMessage *msg) {
    if (msg == nextArrivalEvent) {
        handleArrival();
        scheduleNextArrival();
    }
    else if (msg == simulationEndEvent) {
        handleSimulationEnd();
    }
    else if (VehicleDeparture *departure = dynamic_cast<VehicleDeparture*>(msg)) {
        handleVehicleDeparture(departure);
    }
    else if (SensorMalfunction *malfunction = dynamic_cast<SensorMalfunction*>(msg)) {
        handleSensorMalfunction(malfunction);
    }
    else if (SensorRepair *repair = dynamic_cast<SensorRepair*>(msg)) {
        handleSensorRepair(repair);
    }
    else if (SlotStatusUpdate *update = dynamic_cast<SlotStatusUpdate*>(msg)) {
        handleSlotStatusUpdate(update);
    }

    updateStatistics();
}

void ParkingController::handleArrival() {
    totalArrivals++;

    Vehicle newVehicle;
    newVehicle.vehicleId = vehicleIdCounter++;
    newVehicle.arrivalTime = simTime();
    newVehicle.plannedDuration = exponential(avgParkingDuration);

    emit(vehicleArrivalSignal, (long)newVehicle.vehicleId);

    EV << "Vehicle " << newVehicle.vehicleId << " arrived at time " << simTime() << endl;

    int availableSlot = findAvailableSlot();
    if (availableSlot != -1) {
        assignVehicleToSlot(newVehicle, availableSlot);
        EV << "Vehicle " << newVehicle.vehicleId << " assigned to slot " << availableSlot << endl;
    } else {
        entryQueue.push(newVehicle);
        if ((int)entryQueue.size() > maxQueueLength) {
            maxQueueLength = entryQueue.size();
        }
        EV << "Vehicle " << newVehicle.vehicleId << " added to queue. Queue length: " << entryQueue.size() << endl;
    }
}

void ParkingController::handleVehicleDeparture(VehicleDeparture *msg) {
    int vehicleId = msg->getVehicleId();
    int slotId = msg->getSlotId();

    totalDepartures++;
    emit(vehicleDepartureSignal, (long)vehicleId);

    EV << "Controller received departure notification: Vehicle " << vehicleId
       << " departed from slot " << slotId << " at time " << simTime() << endl;

    // Update controller's slot tracking
    slotOccupied[slotId] = false;

    // Calculate waiting time and parking duration
    if (parkedVehicles.find(vehicleId) != parkedVehicles.end()) {
        Vehicle departingVehicle = parkedVehicles[vehicleId];
        parkedVehicles.erase(vehicleId);

        simtime_t waitingTime = departingVehicle.entryTime - departingVehicle.arrivalTime;
        simtime_t actualDuration = simTime() - departingVehicle.entryTime;

        totalWaitingTime += SIMTIME_DBL(waitingTime);
        emit(waitingTimeSignal, waitingTime);

        EV << "Vehicle " << vehicleId << " waited " << waitingTime
           << " seconds and parked for " << actualDuration << " seconds" << endl;
    }

    // Process queued vehicles
    processQueuedVehicles();

    delete msg;
}

void ParkingController::handleSensorMalfunction(SensorMalfunction *msg) {
    int sensorId = msg->getSensorId();
    double repairDuration = msg->getRepairDuration();

    EV << "Controller: Sensor " << sensorId << " malfunctioned at time " << simTime() << endl;

    if (sensorId < numSlots) {
        slotSensorWorking[sensorId] = false;
        malfunctioningSensors.insert(sensorId);

        // Send malfunction message to slot
        SensorMalfunction *slotMsg = new SensorMalfunction(*msg);
        sendToSlot(sensorId, slotMsg);

        // Schedule repair
        SensorRepair *repair = new SensorRepair();
        repair->setSensorId(sensorId);

        sensorRepairEvents[sensorId] = repair;
        scheduleAt(simTime() + repairDuration, repair);
    }

    delete msg;
}

void ParkingController::handleSensorRepair(SensorRepair *msg) {
    int sensorId = msg->getSensorId();

    EV << "Controller: Sensor " << sensorId << " repaired at time " << simTime() << endl;

    if (sensorId < numSlots) {
        slotSensorWorking[sensorId] = true;
        malfunctioningSensors.erase(sensorId);

        // Send repair message to slot
        SensorRepair *slotMsg = new SensorRepair(*msg);
        sendToSlot(sensorId, slotMsg);
    }

    sensorRepairEvents.erase(sensorId);
    processQueuedVehicles();
    scheduleSensorMalfunction();

    delete msg;
}

void ParkingController::handleSlotStatusUpdate(SlotStatusUpdate *msg) {
    int slotId = msg->getSlotId();
    bool occupied = msg->getOccupied();
    bool sensorWorking = msg->getSensorWorking();
    int vehicleId = msg->getVehicleId();

    EV << "Controller received status update from slot " << slotId
       << ": occupied=" << occupied << ", sensor=" << sensorWorking
       << ", vehicle=" << vehicleId << endl;

    // Update controller's tracking
    slotOccupied[slotId] = occupied;
    slotSensorWorking[slotId] = sensorWorking;

    if (!occupied) {
        // Slot became free, try to assign waiting vehicles
        processQueuedVehicles();
    }

    delete msg;
}

void ParkingController::handleSimulationEnd() {
    EV << "Simulation ended at time " << simTime() << endl;
    generateReport();
    endSimulation();
}

void ParkingController::scheduleNextArrival() {
    double interArrivalTime = exponential(1.0 / arrivalRate);
    scheduleAt(simTime() + interArrivalTime, nextArrivalEvent);
}

int ParkingController::findAvailableSlot() {
    for (int i = 0; i < numSlots; i++) {
        if (isSlotAvailable(i)) {
            return i;
        }
    }
    return -1;
}

void ParkingController::assignVehicleToSlot(Vehicle &vehicle, int slotId) {
    vehicle.assignedSlot = slotId;
    vehicle.entryTime = simTime();
    slotOccupied[slotId] = true;
    parkedVehicles[vehicle.vehicleId] = vehicle;

    // Send assignment message to slot with parking duration
    SlotAssignment *assignment = new SlotAssignment();
    assignment->setVehicleId(vehicle.vehicleId);
    assignment->setSlotId(slotId);
    assignment->setAssignmentTime(simTime());
    assignment->setParkingDuration(vehicle.plannedDuration);
    sendToSlot(slotId, assignment);

    EV << "Controller assigned vehicle " << vehicle.vehicleId
       << " to slot " << slotId << " for " << vehicle.plannedDuration << " seconds" << endl;
}

void ParkingController::processQueuedVehicles() {
    while (!entryQueue.empty()) {
        int availableSlot = findAvailableSlot();
        if (availableSlot == -1) {
            break;
        }

        Vehicle waitingVehicle = entryQueue.front();
        entryQueue.pop();

        assignVehicleToSlot(waitingVehicle, availableSlot);

        EV << "Assigned queued vehicle " << waitingVehicle.vehicleId
           << " to slot " << availableSlot << endl;
    }
}

void ParkingController::updateStatistics() {
    emit(queueLengthSignal, (long)entryQueue.size());
    emit(occupiedSlotsSignal, (long)getOccupiedSlots());

    double utilization = (double)getOccupiedSlots() / numSlots;
    emit(utilizationRateSignal, utilization);
}

void ParkingController::generateReport() {
    EV << "\n=== SMART PARKING SYSTEM SIMULATION REPORT ===" << endl;
    EV << "Simulation Duration: " << simTime() << " seconds" << endl;
    EV << "Total Arrivals: " << totalArrivals << endl;
    EV << "Total Departures: " << totalDepartures << endl;
    EV << "Vehicles Still Parked: " << parkedVehicles.size() << endl;
    EV << "Vehicles in Queue: " << entryQueue.size() << endl;
    EV << "Maximum Queue Length: " << maxQueueLength << endl;

    if (totalDepartures > 0) {
        EV << "Average Waiting Time: " << (totalWaitingTime / totalDepartures) << " seconds" << endl;
    }

    double finalUtilization = (double)getOccupiedSlots() / numSlots;
    EV << "Final Utilization Rate: " << (finalUtilization * 100) << "%" << endl;
    EV << "Number of Malfunctioning Sensors: " << malfunctioningSensors.size() << endl;
    EV << "======================================================" << endl;
}

void ParkingController::scheduleSensorMalfunction() {
    if (uniform(0, 1) < sensorMalfunctionRate) {
        int randomSensor = intuniform(0, numSlots - 1);
        if (malfunctioningSensors.find(randomSensor) == malfunctioningSensors.end()) {
            double malfunctionTime = exponential(3600);
            double repairDuration = exponential(sensorRepairTime);

            SensorMalfunction *malfunction = new SensorMalfunction();
            malfunction->setSensorId(randomSensor);
            malfunction->setRepairDuration(repairDuration);

            scheduleAt(simTime() + malfunctionTime, malfunction);
        }
    }
}

bool ParkingController::isSlotAvailable(int slotId) {
    if (slotId < 0 || slotId >= numSlots) {
        return false;
    }
    return !slotOccupied[slotId] && slotSensorWorking[slotId];
}

int ParkingController::getAvailableSlots() {
    int count = 0;
    for (int i = 0; i < numSlots; i++) {
        if (isSlotAvailable(i)) {
            count++;
        }
    }
    return count;
}

int ParkingController::getOccupiedSlots() {
    int count = 0;
    for (int i = 0; i < numSlots; i++) {
        if (slotOccupied[i]) {
            count++;
        }
    }
    return count;
}

void ParkingController::sendToSlot(int slotId, cMessage *msg) {
    if (slotId >= 0 && slotId < gateSize("out")) {
        send(msg, "out", slotId);
    } else {
        delete msg;
    }
}

void ParkingController::finish() {
    generateReport();
}
