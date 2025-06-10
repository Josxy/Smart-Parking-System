#ifndef PARKINGSLOT1_H
#define PARKINGSLOT1_H

#include <omnetpp.h>
#include "SmartParkingMessages_m.h"

using namespace omnetpp;

class ParkingSlot1 : public cSimpleModule {
private:
    int slotId;
    bool occupied;
    bool sensorWorking;
    int occupiedByVehicle;
    simtime_t occupiedSince;
    double parkingDuration;

    // Self-scheduled departure event
    cMessage *departureEvent;

    simsignal_t slotOccupiedSignal;
    simsignal_t sensorStatusSignal;

public:
    ParkingSlot1();
    virtual ~ParkingSlot1();

    bool isOccupied() const { return occupied; }
    bool isSensorWorking() const { return sensorWorking; }
    bool isAvailable() const { return !occupied && sensorWorking; }
    int getSlotId() const { return slotId; }
    int getOccupiedByVehicle() const { return occupiedByVehicle; }

    void occupySlot(int vehicleId, double duration);
    void setSensorStatus(bool working);

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

private:
    void updateDisplay();
    void scheduleDeparture();
    void processDeparture();
    void sendDepartureNotification();
};

#endif
