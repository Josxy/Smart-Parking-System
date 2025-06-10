#ifndef PARKINGQUEUE_H
#define PARKINGQUEUE_H

#include <omnetpp.h>
#include <queue>
#include <vector>
#include "SmartParkingMessages_m.h"

using namespace omnetpp;

struct QueuedVehicle {
    int vehicleId;
    simtime_t arrivalTime;
    simtime_t queueEntryTime;
    double plannedDuration;

    QueuedVehicle(int id, simtime_t arrival, simtime_t entry, double duration)
        : vehicleId(id), arrivalTime(arrival), queueEntryTime(entry), plannedDuration(duration) {}
};

class ParkingQueue : public cSimpleModule {
private:
    std::queue<QueuedVehicle> waitingVehicles;
    int maxQueueSize;

    simsignal_t queueLengthSignal;
    simsignal_t vehicleQueuedSignal;
    simsignal_t vehicleDequeuedSignal;

public:
    ParkingQueue();
    virtual ~ParkingQueue();

    bool isEmpty() const { return waitingVehicles.empty(); }
    int getQueueLength() const { return waitingVehicles.size(); }
    bool isFull() const { return waitingVehicles.size() >= (size_t)maxQueueSize; }

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

private:
    void addVehicleToQueue(const QueuedVehicle& vehicle);
    QueuedVehicle removeVehicleFromQueue();
    void updateDisplay();
    void sendVehicleToController(const QueuedVehicle& vehicle);
};

#endif
