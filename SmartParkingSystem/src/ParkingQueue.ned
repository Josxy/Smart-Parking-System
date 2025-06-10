package smartparkingsystem;

simple ParkingQueue
{
    parameters:
        int maxQueueSize = default(50);
        @display("i=block/queue;bgb=120,300");
        
        @signal[queueLength](type=long);
        @signal[vehicleQueued](type=long);
        @signal[vehicleDequeued](type=long);
        
        @statistic[queueLength](title="Queue Length"; record=vector,mean,max);
        @statistic[vehicleQueued](title="Vehicles Queued"; record=count,vector);
        @statistic[vehicleDequeued](title="Vehicles Dequeued"; record=count,vector);
        
    gates:
        input in;
        output out;
}