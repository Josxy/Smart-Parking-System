package smartparkingsystem;

simple ParkingController
{
    parameters:
        int numSlots = default(20);
        double arrivalRate = default(0.05);
        double avgParkingDuration = default(1800.0);
        double simulationTime = default(7200.0);
        double sensorMalfunctionRate = default(0.001);
        double sensorRepairTime = default(300.0);
        
        @display("i=block/control");
        
    gates:
        // Slot connections
        input slotIn[];
        output slotOut[];
        
        // Queue connections  
        input queueIn;
        output queueOut;
}