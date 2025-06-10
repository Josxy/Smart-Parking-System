#include "ParkingSlot1.h"

Define_Module(ParkingSlot1);

ParkingSlot1::ParkingSlot1() {
    slotId = -1;
    occupied = false;
    sensorWorking = true;
    occupiedByVehicle = -1;
    occupiedSince = 0;
}

ParkingSlot1::~ParkingSlot1() {
}

void ParkingSlot1::initialize() {
    slotId = par("slotId");
    occupied = par("occupied");
    sensorWorking = par("sensorWorking");
    occupiedByVehicle = par("occupiedByVehicle");

    slotOccupiedSignal = registerSignal("slotOccupied");
    sensorStatusSignal = registerSignal("sensorStatus");

    updateDisplay();
}

void ParkingSlot1::handleMessage(cMessage *msg) {
    // Handle messages from parking lot
    if (SlotAssignment *assignment = dynamic_cast<SlotAssignment*>(msg)) {
        occupySlot(assignment->getVehicleId());
    }
    else if (VehicleDeparture *departure = dynamic_cast<VehicleDeparture*>(msg)) {
        freeSlot();
    }
    else if (SensorMalfunction *malfunction = dynamic_cast<SensorMalfunction*>(msg)) {
        setSensorStatus(false);
    }
    else if (SensorRepair *repair = dynamic_cast<SensorRepair*>(msg)) {
        setSensorStatus(true);
    }

    delete msg;
}

void ParkingSlot1::occupySlot(int vehicleId) {
    occupied = true;
    occupiedByVehicle = vehicleId;
    occupiedSince = simTime();

    emit(slotOccupiedSignal, true);
    updateDisplay();

    EV << "Slot " << slotId << " occupied by vehicle " << vehicleId << endl;
}

void ParkingSlot1::freeSlot() {
    occupied = false;
    occupiedByVehicle = -1;
    occupiedSince = 0;

    emit(slotOccupiedSignal, false);
    updateDisplay();

    EV << "Slot " << slotId << " freed" << endl;
}

void ParkingSlot1::setSensorStatus(bool working) {
    sensorWorking = working;
    emit(sensorStatusSignal, working);
    updateDisplay();

    EV << "Slot " << slotId << " sensor " << (working ? "repaired" : "malfunctioned") << endl;
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
