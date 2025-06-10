message VehicleArrival {
    int vehicleId;
    simtime_t arrivalTime;
}

message VehicleDeparture {
    int vehicleId;
    int slotId;
    simtime_t departureTime;
}

message VehicleEntry {
    int vehicleId;
    int slotId;
}

message SlotAssignment {
    int vehicleId;
    int slotId;
    simtime_t assignmentTime;
    double parkingDuration;
}

message SensorMalfunction {
    int sensorId;
    double repairDuration;
}

message SensorRepair {
    int sensorId;
}

message SimulationEnd {
}

message NextArrival {
}

message SlotStatusUpdate {
    int slotId;
    bool occupied;
    bool sensorWorking;
    int vehicleId;
}

message VehicleDequeue {
    // Request to remove vehicle from queue
}

message VehicleFromQueue {
    int vehicleId;
    simtime_t arrivalTime;
    simtime_t queueEntryTime;
    double plannedDuration;
}

message AssignmentInProgress {
    int vehicleId;
    int slotId;
    simtime_t assignmentTime;
}