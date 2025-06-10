#include "ParkingController.h"

Define_Module(ParkingController);

ParkingController::ParkingController() {
    nextArrivalEvent = nullptr;
    simulationEndEvent = nullptr;
    assignmentAnimationEvent = nullptr;
    vehicleIdCounter = 0;
    totalArrivals = 0;
    totalDepartures = 0;
    maxQueueLength = 0;
    totalWaitingTime = 0;
    currentAssignmentVehicle = -1;
    currentAssignmentSlot = -1;
    assignmentInProgress = false;
}

ParkingController::~ParkingController() {
    cancelAndDelete(nextArrivalEvent);
    cancelAndDelete(simulationEndEvent);
    cancelAndDelete(assignmentAnimationEvent);

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

    assignmentAnimationEvent = new cMessage("assignmentAnimation");

    scheduleSensorMalfunction();
    updateDisplay();

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
    else if (msg == assignmentAnimationEvent) {
        handleAssignmentAnimation();
    }
    else if (VehicleDeparture *departure = dynamic_cast<VehicleDeparture*>(msg)) {
        handleVehicleDeparture(departure);
    }
    else if (VehicleFromQueue *fromQueue = dynamic_cast<VehicleFromQueue*>(msg)) {
        handleVehicleFromQueue(fromQueue);
    }
    else if (SensorMalfunction *malfunction = dynamic_cast<SensorMalfunction*>(msg)) {
        handleSensorMalfunction(malfunction);
    }
    else if (SensorRepair *repair = dynamic_cast<SensorRepair*>(msg)) {
        handleSensorRepair(repair);
    }

    updateStatistics();
    updateDisplay();
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
    if (availableSlot != -1 && !assignmentInProgress) {
        // Direct assignment
        newVehicle.entryTime = simTime();
        assignVehicleToSlot(newVehicle, availableSlot);
        EV << "Vehicle " << newVehicle.vehicleId << " directly assigned to slot " << availableSlot << endl;
    } else {
        // Send to queue
        VehicleArrival *queueMsg = new VehicleArrival();
        queueMsg->setVehicleId(newVehicle.vehicleId);
        queueMsg->setArrivalTime(newVehicle.arrivalTime);
        sendToQueue(queueMsg);

        EV << "Vehicle " << newVehicle.vehicleId << " sent to queue" << endl;

        // Try to process queue if no assignment in progress
        if (!assignmentInProgress) {
            requestVehicleFromQueue();
        }
    }
}

void ParkingController::handleVehicleFromQueue(VehicleFromQueue *msg) {
    int vehicleId = msg->getVehicleId();

    EV << "Controller received vehicle " << vehicleId << " from queue" << endl;

    int availableSlot = findAvailableSlot();
    if (availableSlot != -1) {
        Vehicle vehicle;
        vehicle.vehicleId = vehicleId;
        vehicle.arrivalTime = msg->getArrivalTime();
        vehicle.queueEntryTime = msg->getQueueEntryTime();
        vehicle.entryTime = simTime();
        vehicle.plannedDuration = msg->getPlannedDuration();

        // Start visual assignment animation
        startAssignmentAnimation(vehicleId, availableSlot);

        // Store vehicle for later assignment completion
        parkedVehicles[vehicleId] = vehicle;

        EV << "Starting assignment animation for vehicle " << vehicleId << " to slot " << availableSlot << endl;
    } else {
        EV << "No available slot for vehicle " << vehicleId << ", sending back to queue" << endl;
        // Send back to queue (this shouldn't happen if queue management is correct)
        VehicleArrival *backToQueue = new VehicleArrival();
        backToQueue->setVehicleId(vehicleId);
        backToQueue->setArrivalTime(msg->getArrivalTime());
        sendToQueue(backToQueue);
    }

    delete msg;
}

void ParkingController::handleVehicleDeparture(VehicleDeparture *msg) {
    int vehicleId = msg->getVehicleId();
    int slotId = msg->getSlotId();

    totalDepartures++;
    emit(vehicleDepartureSignal, (long)vehicleId);

    EV << "Controller received departure notification: Vehicle " << vehicleId
       << " departed from slot " << slotId << " at time " << simTime() << endl;

    slotOccupied[slotId] = false;

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

    // Try to assign next vehicle from queue
    if (!assignmentInProgress) {
        requestVehicleFromQueue();
    }

    delete msg;
}

void ParkingController::startAssignmentAnimation(int vehicleId, int slotId) {
    assignmentInProgress = true;
    currentAssignmentVehicle = vehicleId;
    currentAssignmentSlot = slotId;

    // Schedule animation completion in 1 second
    scheduleAt(simTime() + 1.0, assignmentAnimationEvent);

    // Update display to show assignment in progress
    updateDisplay();
}

void ParkingController::handleAssignmentAnimation() {
    if (assignmentInProgress) {
        // Complete the assignment
        Vehicle &vehicle = parkedVehicles[currentAssignmentVehicle];
        vehicle.assignedSlot = currentAssignmentSlot;
        slotOccupied[currentAssignmentSlot] = true;

        // Send assignment to slot
        SlotAssignment *assignment = new SlotAssignment();
        assignment->setVehicleId(currentAssignmentVehicle);
        assignment->setSlotId(currentAssignmentSlot);
        assignment->setAssignmentTime(simTime());
        assignment->setParkingDuration(vehicle.plannedDuration);
        sendToSlot(currentAssignmentSlot, assignment);

        EV << "Assignment completed: Vehicle " << currentAssignmentVehicle
           << " assigned to slot " << currentAssignmentSlot << endl;

        // Reset animation state
        assignmentInProgress = false;
        currentAssignmentVehicle = -1;
        currentAssignmentSlot = -1;

        // Try to process next vehicle from queue
        requestVehicleFromQueue();
    }
}

void ParkingController::requestVehicleFromQueue() {
    if (findAvailableSlot() != -1 && !assignmentInProgress) {
        VehicleDequeue *dequeueMsg = new VehicleDequeue();
        sendToQueue(dequeueMsg);
    }
}

void ParkingController::assignVehicleToSlot(Vehicle &vehicle, int slotId) {
    vehicle.assignedSlot = slotId;
    slotOccupied[slotId] = true;
    parkedVehicles[vehicle.vehicleId] = vehicle;

    SlotAssignment *assignment = new SlotAssignment();
    assignment->setVehicleId(vehicle.vehicleId);
    assignment->setSlotId(slotId);
    assignment->setAssignmentTime(simTime());
    assignment->setParkingDuration(vehicle.plannedDuration);
    sendToSlot(slotId, assignment);
}

void ParkingController::updateDisplay() {
    std::string status;
    std::string color = "blue";

    if (assignmentInProgress) {
        status = "ASSIGNING\nVehicle " + std::to_string(currentAssignmentVehicle) +
                "\nto Slot " + std::to_string(currentAssignmentSlot);
        color = "yellow";
    } else {
        int available = getAvailableSlots();
        int occupied = getOccupiedSlots();
        status = "CONTROLLER\nAvailable: " + std::to_string(available) +
                "\nOccupied: " + std::to_string(occupied);
        color = available > 0 ? "green" : "red";
    }

    char displayStr[300];
    sprintf(displayStr, "i=block/control;bgb=150,100;p=,,,%s;t=%s",
            color.c_str(), status.c_str());
    getDisplayString().parse(displayStr);
}

void ParkingController::handleSensorMalfunction(SensorMalfunction *msg) {
    int sensorId = msg->getSensorId();
    double repairDuration = msg->getRepairDuration();

    EV << "Controller: Sensor " << sensorId << " malfunctioned at time " << simTime() << endl;

    if (sensorId < numSlots) {
        slotSensorWorking[sensorId] = false;
        malfunctioningSensors.insert(sensorId);

        SensorMalfunction *slotMsg = new SensorMalfunction(*msg);
        sendToSlot(sensorId, slotMsg);

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

        SensorRepair *slotMsg = new SensorRepair(*msg);
        sendToSlot(sensorId, slotMsg);
    }

    sensorRepairEvents.erase(sensorId);

    if (!assignmentInProgress) {
        requestVehicleFromQueue();
    }
    scheduleSensorMalfunction();

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

void ParkingController::updateStatistics() {
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
    if (slotId >= 0 && slotId < gateSize("slotOut")) {
        send(msg, "slotOut", slotId);
    } else {
        delete msg;
    }
}

void ParkingController::sendToQueue(cMessage *msg) {
    send(msg, "queueOut");
}

void ParkingController::finish() {
    generateReport();
}
