#ifndef PARKINGCONTROLLER_H
#define PARKINGCONTROLLER_H

#include <omnetpp.h>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include "SmartParkingMessages_m.h"

using namespace omnetpp;

struct Vehicle {
    int vehicleId;
    simtime_t arrivalTime;
    simtime_t queueEntryTime;
    simtime_t entryTime;
    simtime_t departureTime;
    int assignedSlot;
    double plannedDuration;

    Vehicle() : vehicleId(-1), arrivalTime(0), queueEntryTime(0), entryTime(0),
                departureTime(0), assignedSlot(-1), plannedDuration(0) {}
};

class ParkingController : public cSimpleModule {
private:
    int numSlots;
    double arrivalRate;
    double avgParkingDuration;
    double simulationTime;
    double sensorMalfunctionRate;
    double sensorRepairTime;

    std::map<int, Vehicle> parkedVehicles;
    std::set<int> malfunctioningSensors;
    std::vector<bool> slotOccupied;
    std::vector<bool> slotSensorWorking;

    cMessage *nextArrivalEvent;
    cMessage *simulationEndEvent;
    cMessage *assignmentAnimationEvent;
    std::map<int, cMessage*> sensorRepairEvents;

    // Assignment animation
    int currentAssignmentVehicle;
    int currentAssignmentSlot;
    bool assignmentInProgress;

    int vehicleIdCounter;
    int totalArrivals;
    int totalDepartures;
    int maxQueueLength;
    double totalWaitingTime;

    simsignal_t queueLengthSignal;
    simsignal_t occupiedSlotsSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t utilizationRateSignal;
    simsignal_t vehicleArrivalSignal;
    simsignal_t vehicleDepartureSignal;

public:
    ParkingController();
    virtual ~ParkingController();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

private:
    void handleArrival();
    void handleVehicleDeparture(VehicleDeparture *msg);
    void handleVehicleFromQueue(VehicleFromQueue *msg);
    void handleSensorMalfunction(SensorMalfunction *msg);
    void handleSensorRepair(SensorRepair *msg);
    void handleSimulationEnd();
    void handleAssignmentAnimation();

    void scheduleNextArrival();
    void requestVehicleFromQueue();
    int findAvailableSlot();
    void assignVehicleToSlot(Vehicle &vehicle, int slotId);
    void startAssignmentAnimation(int vehicleId, int slotId);
    void updateStatistics();
    void generateReport();
    void updateDisplay();

    void scheduleSensorMalfunction();
    bool isSlotAvailable(int slotId);
    int getAvailableSlots();
    int getOccupiedSlots();

    void sendToSlot(int slotId, cMessage *msg);
    void sendToQueue(cMessage *msg);
};

#endif
