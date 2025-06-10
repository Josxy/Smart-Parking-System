#ifndef PARKINGLOT_H
#define PARKINGLOT_H

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
    simtime_t entryTime;
    simtime_t departureTime;
    int assignedSlot;
    double plannedDuration;

    Vehicle() : vehicleId(-1), arrivalTime(0), entryTime(0),
                departureTime(0), assignedSlot(-1), plannedDuration(0) {}

    Vehicle(int id, simtime_t arrival) : vehicleId(id), arrivalTime(arrival),
                                        entryTime(0), departureTime(0),
                                        assignedSlot(-1), plannedDuration(0) {}
};

struct ParkingSlot {
    int slotId;
    bool occupied;
    bool sensorWorking;
    int vehicleId;
    simtime_t occupiedSince;

    ParkingSlot() : slotId(-1), occupied(false), sensorWorking(true),
                   vehicleId(-1), occupiedSince(0) {}

    ParkingSlot(int id) : slotId(id), occupied(false), sensorWorking(true),
                         vehicleId(-1), occupiedSince(0) {}
};

class ParkingLot : public cSimpleModule {
private:
    // System parameters
    int numSlots;
    double arrivalRate;
    double avgParkingDuration;
    double simulationTime;
    double sensorMalfunctionRate;
    double sensorRepairTime;

    // System state
    std::vector<ParkingSlot> parkingSlots;
    std::queue<Vehicle> entryQueue;
    std::map<int, Vehicle> parkedVehicles;
    std::set<int> malfunctioningSensors;

    // Event management
    cMessage *nextArrivalEvent;
    cMessage *simulationEndEvent;
    std::map<int, cMessage*> departureEvents;
    std::map<int, cMessage*> sensorRepairEvents;

    // Statistics
    int vehicleIdCounter;
    int totalArrivals;
    int totalDepartures;
    int maxQueueLength;
    double totalWaitingTime;

    // Signals - ADD THESE MISSING DECLARATIONS
    simsignal_t queueLengthSignal;
    simsignal_t occupiedSlotsSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t utilizationRateSignal;
    simsignal_t vehicleArrivalSignal;
    simsignal_t vehicleDepartureSignal;

public:
    ParkingLot();
    virtual ~ParkingLot();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

private:
    void handleArrival();
    void handleDeparture(VehicleDeparture *msg);
    void handleEntry(VehicleEntry *msg);
    void handleSensorMalfunction(SensorMalfunction *msg);
    void handleSensorRepair(SensorRepair *msg);
    void handleSimulationEnd();

    void scheduleNextArrival();
    int findAvailableSlot();
    void assignVehicleToSlot(Vehicle &vehicle, int slotId);
    void processQueuedVehicles();
    void updateStatistics();
    void generateReport();

    void scheduleSensorMalfunction();
    bool isSlotAvailable(int slotId);
    int getAvailableSlots();
    int getOccupiedSlots();
};

#endif
