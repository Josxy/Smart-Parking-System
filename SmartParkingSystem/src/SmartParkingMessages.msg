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