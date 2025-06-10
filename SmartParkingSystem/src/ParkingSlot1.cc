#include "ParkingSlot1.h"

Define_Module(ParkingSlot1);

ParkingSlot1::ParkingSlot1() {
    slotId = -1;
    occupied = false;
    sensorWorking = true;
    occupiedByVehicle = -1;
    occupiedSince = 0;
    parkingDuration = 0;
    departureEvent = nullptr;
}

ParkingSlot1::~ParkingSlot1() {
    cancelAndDelete(departureEvent);
}

void ParkingSlot1::initialize() {
    slotId = par("slotId");
    occupied = par("occupied");
    sensorWorking = par("sensorWorking");
    occupiedByVehicle = par("occupiedByVehicle");

    slotOccupiedSignal = registerSignal("slotOccupied");
    sensorStatusSignal = registerSignal("sensorStatus");

    departureEvent = new cMessage("departure");

    updateDisplay();

    EV << "Parking Slot " << slotId << " initialized" << endl;
}

void ParkingSlot1::handleMessage(cMessage *msg) {
    if (msg == departureEvent) {
        // Vehicle is departing from this slot
        processDeparture();
    }
    else if (SlotAssignment *assignment = dynamic_cast<SlotAssignment*>(msg)) {
        // Controller assigned a vehicle to this slot
        double duration = assignment->getParkingDuration();
        occupySlot(assignment->getVehicleId(), duration);
        delete msg;
    }
    else if (SensorMalfunction *malfunction = dynamic_cast<SensorMalfunction*>(msg)) {
        setSensorStatus(false);
        delete msg;
    }
    else if (SensorRepair *repair = dynamic_cast<SensorRepair*>(msg)) {
        setSensorStatus(true);
        delete msg;
    }
    else {
        delete msg;
    }
}

void ParkingSlot1::occupySlot(int vehicleId, double duration) {
    if (occupied || !sensorWorking) {
        EV << "Cannot occupy slot " << slotId << " - already occupied or sensor not working" << endl;
        return;
    }

    occupied = true;
    occupiedByVehicle = vehicleId;
    occupiedSince = simTime();
    parkingDuration = duration;

    emit(slotOccupiedSignal, true);
    updateDisplay();

    // Schedule departure
    scheduleDeparture();

    EV << "Slot " << slotId << " occupied by vehicle " << vehicleId
       << " for " << duration << " seconds" << endl;
}

void ParkingSlot1::setSensorStatus(bool working) {
    sensorWorking = working;
    emit(sensorStatusSignal, working);
    updateDisplay();

    EV << "Slot " << slotId << " sensor " << (working ? "repaired" : "malfunctioned") << endl;

    if (!working && occupied) {
        // If sensor fails while occupied, we can't detect departure
        EV << "Warning: Sensor failure while slot " << slotId << " is occupied!" << endl;
    }
}

void ParkingSlot1::scheduleDeparture() {
    if (departureEvent->isScheduled()) {
        cancelEvent(departureEvent);
    }
    scheduleAt(simTime() + parkingDuration, departureEvent);
}

void ParkingSlot1::processDeparture() {
    if (!occupied) {
        EV << "Warning: Departure event for empty slot " << slotId << endl;
        return;
    }

    EV << "Vehicle " << occupiedByVehicle << " departing from slot " << slotId
       << " at time " << simTime() << endl;

    // Send departure notification to controller
    sendDepartureNotification();

    // Clear slot
    occupied = false;
    int departingVehicle = occupiedByVehicle;
    occupiedByVehicle = -1;
    occupiedSince = 0;
    parkingDuration = 0;

    emit(slotOccupiedSignal, false);
    updateDisplay();

    EV << "Slot " << slotId << " is now free" << endl;
}

void ParkingSlot1::sendDepartureNotification() {
    VehicleDeparture *departure = new VehicleDeparture();
    departure->setVehicleId(occupiedByVehicle);
    departure->setSlotId(slotId);
    departure->setDepartureTime(simTime());

    send(departure, "out");

    EV << "Slot " << slotId << " sent departure notification for vehicle "
       << occupiedByVehicle << " to controller" << endl;
}

void ParkingSlot1::updateDisplay() {
    std::string color;
    std::string icon;
    std::string text;

    if (!sensorWorking) {
        color = "red";
        icon = "status/stop";
        text = "SENSOR\nERROR";
    } else if (occupied) {
        color = "orange";
        icon = "misc/car";
        text = std::to_string(occupiedByVehicle);
    } else {
        color = "green";
        icon = "misc/square";
        text = "FREE";
    }

    char displayStr[200];
    sprintf(displayStr, "i=%s;bgb=60,40;p=,,,%s;t=%s", icon.c_str(), color.c_str(), text.c_str());
    getDisplayString().parse(displayStr);
}
