package smartparkingsystem;

simple ParkingSlot1
{
    parameters:
        int slotId;
        bool occupied = default(false);
        bool sensorWorking = default(true);
        int occupiedByVehicle = default(-1);
        
        @display("i=block/rxtx;bgb=40,30");
        
        @signal[slotOccupied](type=bool);
        @signal[sensorStatus](type=bool);
        
        @statistic[slotOccupied](title="Slot Occupied"; record=vector);
        @statistic[sensorStatus](title="Sensor Status"; record=vector);
        
    gates:
        input in;
        output out;
}