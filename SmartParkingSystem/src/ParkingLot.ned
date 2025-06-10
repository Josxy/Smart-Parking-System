package smartparkingsystem;

import smartparkingsystem.ParkingSlot1;
import smartparkingsystem.ParkingController;

module ParkingLot
{
    parameters:
        int numSlots = default(20);
        double arrivalRate = default(0.05);
        double avgParkingDuration = default(1800.0);
        double simulationTime = default(7200.0);
        double sensorMalfunctionRate = default(0.001);
        double sensorRepairTime = default(300.0);
        
        @display("bgb=1000,700;bgi=background/terrain");
        
        @signal[queueLength](type=long);
        @signal[occupiedSlots](type=long);
        @signal[waitingTime](type=simtime_t);
        @signal[utilizationRate](type=double);
        @signal[vehicleArrival](type=long);
        @signal[vehicleDeparture](type=long);
        
        @statistic[queueLength](title="Queue Length"; record=vector,mean,max);
        @statistic[occupiedSlots](title="Occupied Slots"; record=vector,mean);
        @statistic[waitingTime](title="Waiting Time"; record=vector,mean,histogram);
        @statistic[utilizationRate](title="Utilization Rate"; record=vector,mean);
        @statistic[vehicleArrival](title="Vehicle Arrivals"; record=count,vector);
        @statistic[vehicleDeparture](title="Vehicle Departures"; record=count,vector);
        
    submodules:
        controller: ParkingController {
            numSlots = parent.numSlots;
            arrivalRate = parent.arrivalRate;
            avgParkingDuration = parent.avgParkingDuration;
            simulationTime = parent.simulationTime;
            sensorMalfunctionRate = parent.sensorMalfunctionRate;
            sensorRepairTime = parent.sensorRepairTime;
            @display("p=100,50;i=block/control;is=l");
        }
        
        slot[numSlots]: ParkingSlot1 {
            slotId = index;
            @display("p=${200 + (index % 8) * 100},${150 + int(index / 8) * 80};is=l");
        }
        
    connections:
        for i=0..numSlots-1 {
            controller.out++ --> slot[i].in;
            slot[i].out --> controller.in++;
        }
}