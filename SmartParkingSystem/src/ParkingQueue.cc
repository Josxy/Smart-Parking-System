#include "ParkingQueue.h"

Define_Module(ParkingQueue);

ParkingQueue::ParkingQueue() {
}

ParkingQueue::~ParkingQueue() {
}

void ParkingQueue::initialize() {
    maxQueueSize = par("maxQueueSize");

    queueLengthSignal = registerSignal("queueLength");
    vehicleQueuedSignal = registerSignal("vehicleQueued");
    vehicleDequeuedSignal = registerSignal("vehicleDequeued");

    updateDisplay();

    EV << "Parking Queue initialized with max size: " << maxQueueSize << endl;
}

void ParkingQueue::handleMessage(cMessage *msg) {
    if (VehicleArrival *arrival = dynamic_cast<VehicleArrival*>(msg)) {
        // Vehicle wants to join queue
        if (!isFull()) {
            QueuedVehicle vehicle(arrival->getVehicleId(), arrival->getArrivalTime(),
                                 simTime(), exponential(1800));
            addVehicleToQueue(vehicle);
            EV << "Vehicle " << arrival->getVehicleId() << " joined queue at position "
               << waitingVehicles.size() << endl;
        } else {
            EV << "Queue is full! Vehicle " << arrival->getVehicleId() << " rejected" << endl;
        }
        delete msg;
    }
    else if (dynamic_cast<VehicleDequeue*>(msg)) {
        // Controller requests next vehicle from queue
        if (!isEmpty()) {
            QueuedVehicle vehicle = removeVehicleFromQueue();
            sendVehicleToController(vehicle);
            EV << "Vehicle " << vehicle.vehicleId << " dequeued and sent to controller" << endl;
        } else {
            EV << "Queue is empty, cannot dequeue vehicle" << endl;
        }
        delete msg;
    }
}

void ParkingQueue::addVehicleToQueue(const QueuedVehicle& vehicle) {
    waitingVehicles.push(vehicle);
    emit(queueLengthSignal, (long)waitingVehicles.size());
    emit(vehicleQueuedSignal, (long)vehicle.vehicleId);
    updateDisplay();
}

QueuedVehicle ParkingQueue::removeVehicleFromQueue() {
    QueuedVehicle vehicle = waitingVehicles.front();
    waitingVehicles.pop();
    emit(queueLengthSignal, (long)waitingVehicles.size());
    emit(vehicleDequeuedSignal, (long)vehicle.vehicleId);
    updateDisplay();
    return vehicle;
}

void ParkingQueue::updateDisplay() {
    int queueLen = waitingVehicles.size();

    std::string text = "QUEUE\n" + std::to_string(queueLen) + " vehicles";
    std::string color;

    if (queueLen == 0) {
        color = "green";
    } else if (queueLen >= maxQueueSize) {
        color = "red";
    } else if (queueLen > maxQueueSize * 0.7) {
        color = "orange";
    } else {
        color = "yellow";
    }

    char displayStr[300];
    sprintf(displayStr, "i=block/queue;bgb=120,300;p=,,,%s;t=%s", color.c_str(), text.c_str());
    getDisplayString().parse(displayStr);

    // Additional visual feedback
    if (queueLen > 0) {
        // Show some visual indication of vehicles waiting
        std::string detailedText = text + "\nWaiting...";
        sprintf(displayStr, "i=block/queue;bgb=120,300;p=,,,%s;t=%s", color.c_str(), detailedText.c_str());
        getDisplayString().parse(displayStr);
    }
}

void ParkingQueue::sendVehicleToController(const QueuedVehicle& vehicle) {
    VehicleFromQueue *vehicleMsg = new VehicleFromQueue();
    vehicleMsg->setVehicleId(vehicle.vehicleId);
    vehicleMsg->setArrivalTime(vehicle.arrivalTime);
    vehicleMsg->setQueueEntryTime(vehicle.queueEntryTime);
    vehicleMsg->setPlannedDuration(vehicle.plannedDuration);

    send(vehicleMsg, "out");
}
