#include "ParkingLot.h"

Define_Module(ParkingLot);

ParkingLot::ParkingLot() {
    nextArrivalEvent = nullptr;
    simulationEndEvent = nullptr;
    vehicleIdCounter = 0;
    totalArrivals = 0;
    totalDepartures = 0;
    maxQueueLength = 0;
    totalWaitingTime = 0;
}

ParkingLot::~ParkingLot() {
    cancelAndDelete(nextArrivalEvent);
    cancelAndDelete(simulationEndEvent);

    for (auto& pair : departureEvents) {
        cancelAndDelete(pair.second);
    }

    for (auto& pair : sensorRepairEvents) {
        cancelAndDelete(pair.second);
    }
}

void ParkingLot::initialize() {
    numSlots = par("numSlots");
    arrivalRate = par("arrivalRate");
    avgParkingDuration = par("avgParkingDuration");
    simulationTime = par("simulationTime");
    sensorMalfunctionRate = par("sensorMalfunctionRate");
    sensorRepairTime = par("sensorRepairTime");

    // Initialize parking slots with proper constructor
    parkingSlots.resize(numSlots);
    for (int i = 0; i < numSlots; i++) {
        parkingSlots[i].slotId = i;
        parkingSlots[i].occupied = false;
        parkingSlots[i].sensorWorking = true;
        parkingSlots[i].vehicleId = -1;
        parkingSlots[i].occupiedSince = 0;
    }

    // Register all signals
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

    EV << "Smart Parking System initialized with " << numSlots << " slots" << endl;
}

void ParkingLot::handleMessage(cMessage *msg) {
    if (msg == nextArrivalEvent) {
        handleArrival();
        scheduleNextArrival();
    }
    else if (msg == simulationEndEvent) {
        handleSimulationEnd();
    }
    else if (VehicleDeparture *departure = dynamic_cast<VehicleDeparture*>(msg)) {
        handleDeparture(departure);
    }
    else if (VehicleEntry *entry = dynamic_cast<VehicleEntry*>(msg)) {
        handleEntry(entry);
    }
    else if (SensorMalfunction *malfunction = dynamic_cast<SensorMalfunction*>(msg)) {
        handleSensorMalfunction(malfunction);
    }
    else if (SensorRepair *repair = dynamic_cast<SensorRepair*>(msg)) {
        handleSensorRepair(repair);
    }

    updateStatistics();
}

void ParkingLot::handleArrival() {
    totalArrivals++;

    // Use proper constructor
    Vehicle newVehicle;
    newVehicle.vehicleId = vehicleIdCounter++;
    newVehicle.arrivalTime = simTime();
    newVehicle.plannedDuration = exponential(avgParkingDuration);

    emit(vehicleArrivalSignal, (long)newVehicle.vehicleId);

    EV << "Vehicle " << newVehicle.vehicleId << " arrived at time " << simTime() << endl;

    int availableSlot = findAvailableSlot();
    if (availableSlot != -1) {
        assignVehicleToSlot(newVehicle, availableSlot);

        VehicleEntry *entry = new VehicleEntry();
        entry->setVehicleId(newVehicle.vehicleId);
        entry->setSlotId(availableSlot);
        scheduleAt(simTime(), entry);

        EV << "Vehicle " << newVehicle.vehicleId << " assigned to slot " << availableSlot << endl;
    } else {
        entryQueue.push(newVehicle);
        if ((int)entryQueue.size() > maxQueueLength) {
            maxQueueLength = entryQueue.size();
        }
        EV << "Vehicle " << newVehicle.vehicleId << " added to queue. Queue length: " << entryQueue.size() << endl;
    }
}

void ParkingLot::handleDeparture(VehicleDeparture *msg) {
    int vehicleId = msg->getVehicleId();
    int slotId = msg->getSlotId();

    totalDepartures++;
    emit(vehicleDepartureSignal, (long)vehicleId);

    EV << "Vehicle " << vehicleId << " departing from slot " << slotId << " at time " << simTime() << endl;

    parkingSlots[slotId].occupied = false;
    parkingSlots[slotId].vehicleId = -1;

    if (parkedVehicles.find(vehicleId) != parkedVehicles.end()) {
        Vehicle departingVehicle = parkedVehicles[vehicleId];
        parkedVehicles.erase(vehicleId);

        simtime_t actualDuration = simTime() - departingVehicle.entryTime;
        EV << "Vehicle " << vehicleId << " parked for " << actualDuration << " seconds" << endl;
    }

    departureEvents.erase(vehicleId);
    processQueuedVehicles();
    delete msg;
}

void ParkingLot::handleEntry(VehicleEntry *msg) {
    int vehicleId = msg->getVehicleId();
    int slotId = msg->getSlotId();

    if (parkedVehicles.find(vehicleId) != parkedVehicles.end()) {
        Vehicle &vehicle = parkedVehicles[vehicleId];
        vehicle.entryTime = simTime();

        simtime_t waitingTime = vehicle.entryTime - vehicle.arrivalTime;
        totalWaitingTime += SIMTIME_DBL(waitingTime);
        emit(waitingTimeSignal, waitingTime);

        EV << "Vehicle " << vehicleId << " entered slot " << slotId << " after waiting " << waitingTime << " seconds" << endl;

        VehicleDeparture *departure = new VehicleDeparture();
        departure->setVehicleId(vehicleId);
        departure->setSlotId(slotId);
        departure->setDepartureTime(simTime() + vehicle.plannedDuration);

        departureEvents[vehicleId] = departure;
        scheduleAt(simTime() + vehicle.plannedDuration, departure);
    }

    delete msg;
}

void ParkingLot::handleSensorMalfunction(SensorMalfunction *msg) {
    int sensorId = msg->getSensorId();
    double repairDuration = msg->getRepairDuration();

    EV << "Sensor " << sensorId << " malfunctioned at time " << simTime() << endl;

    if (sensorId < numSlots) {
        parkingSlots[sensorId].sensorWorking = false;
        malfunctioningSensors.insert(sensorId);

        SensorRepair *repair = new SensorRepair();
        repair->setSensorId(sensorId);

        sensorRepairEvents[sensorId] = repair;
        scheduleAt(simTime() + repairDuration, repair);
    }

    delete msg;
}

void ParkingLot::handleSensorRepair(SensorRepair *msg) {
    int sensorId = msg->getSensorId();

    EV << "Sensor " << sensorId << " repaired at time " << simTime() << endl;

    if (sensorId < numSlots) {
        parkingSlots[sensorId].sensorWorking = true;
        malfunctioningSensors.erase(sensorId);
    }

    sensorRepairEvents.erase(sensorId);
    processQueuedVehicles();
    scheduleSensorMalfunction();

    delete msg;
}

void ParkingLot::handleSimulationEnd() {
    EV << "Simulation ended at time " << simTime() << endl;
    generateReport();
    endSimulation();
}

void ParkingLot::scheduleNextArrival() {
    double interArrivalTime = exponential(1.0 / arrivalRate);
    scheduleAt(simTime() + interArrivalTime, nextArrivalEvent);
}

int ParkingLot::findAvailableSlot() {
    for (int i = 0; i < numSlots; i++) {
        if (isSlotAvailable(i)) {
            return i;
        }
    }
    return -1;
}

void ParkingLot::assignVehicleToSlot(Vehicle &vehicle, int slotId) {
    vehicle.assignedSlot = slotId;
    parkingSlots[slotId].occupied = true;
    parkingSlots[slotId].vehicleId = vehicle.vehicleId;
    parkingSlots[slotId].occupiedSince = simTime();
    parkedVehicles[vehicle.vehicleId] = vehicle;
}

void ParkingLot::processQueuedVehicles() {
    while (!entryQueue.empty()) {
        int availableSlot = findAvailableSlot();
        if (availableSlot == -1) {
            break;
        }

        Vehicle waitingVehicle = entryQueue.front();
        entryQueue.pop();

        assignVehicleToSlot(waitingVehicle, availableSlot);

        VehicleEntry *entry = new VehicleEntry();
        entry->setVehicleId(waitingVehicle.vehicleId);
        entry->setSlotId(availableSlot);
        scheduleAt(simTime(), entry);

        EV << "Queued vehicle " << waitingVehicle.vehicleId << " assigned to slot " << availableSlot << endl;
    }
}

void ParkingLot::updateStatistics() {
    emit(queueLengthSignal, (long)entryQueue.size());
    emit(occupiedSlotsSignal, (long)getOccupiedSlots());

    double utilization = (double)getOccupiedSlots() / numSlots;
    emit(utilizationRateSignal, utilization);
}

void ParkingLot::generateReport() {
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

void ParkingLot::scheduleSensorMalfunction() {
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

bool ParkingLot::isSlotAvailable(int slotId) {
    if (slotId < 0 || slotId >= numSlots) {
        return false;
    }
    return !parkingSlots[slotId].occupied && parkingSlots[slotId].sensorWorking;
}

int ParkingLot::getAvailableSlots() {
    int count = 0;
    for (int i = 0; i < numSlots; i++) {
        if (isSlotAvailable(i)) {
            count++;
        }
    }
    return count;
}

int ParkingLot::getOccupiedSlots() {
    int count = 0;
    for (int i = 0; i < numSlots; i++) {
        if (parkingSlots[i].occupied) {
            count++;
        }
    }
    return count;
}

void ParkingLot::finish() {
    generateReport();
}
