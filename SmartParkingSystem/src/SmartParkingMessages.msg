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

// New message for slot status updates
message SlotStatusUpdate {
    int slotId;
    bool occupied;
    bool sensorWorking;
    int vehicleId;
}