package smartparkingsystem;

simple ParkingController
{
    parameters:
        int numSlots;
        double arrivalRate;
        double avgParkingDuration;
        double simulationTime;
        double sensorMalfunctionRate;
        double sensorRepairTime;
        
        @display("i=block/control");
        
    gates:
        input in[];
        output out[];
}