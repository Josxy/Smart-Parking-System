# Smart Parking System
## Terminology and Concepts
Definition: 

* **Goal:** 
Goal of this project is to simulate Smart Parking System that monitors parking space availability and inform users about spot avaliability.
* **Random variables:**
  * Number of vehicles enter at a time
  * Number of vehicles exit at a time
  * How much time spent parked for each vehicle
* **System State:** 
  * Number of filled and unfilled slots
  * Assignment status of parking slot
  * Queue length at enterence
  * List of vehicles on waiting line
  * List of vehicles assigned
* **Entitites:** 
  * Parking lot
  * Vehicles
  * Sensors
* **Events:**
  * Enter of new vehicle
  * Exit of parked vehicle 
  * Malfunction on sensors collect avaliability data from lot
* **Activities:**
  * Parking duration
  * Offline malfunction fix duration
* **Delay:**
  * Time waiting for a slot to become available
  * Vehicle waiting in queue due to full lot or sensor malfunction
## Components
### Lists 
  * Entry Queue: A list of vehicles waiting for a parking slot.
  * Parking Slot List: Tracks the status (free or occupied) of each parking space. 
### Future Event List (FEL)
  1. Arrival Event
  * This event represents a vehicle arriving at the parking facility.
  * Initially, an arrival event is scheduled at time 0.
  * When the simulation clock reaches the time of an arrival event, a new vehicle is introduced into the system.
  * After processing the current arrival, a new arrival event is scheduled based on the interarrival time distribution.

  2. Service Completion Event
  * This event represents the end of a vehicle’s parking duration.
  * It is scheduled when a vehicle successfully occupies a parking slot.
  * When triggered, it frees up the corresponding slot and may initiate parking for the next vehicle in the waiting queue (if any).

  3. Stopping Event
  * This event determines when the simulation should stop.
  * It is scheduled at the beginning (time 0) for a future time TE, which could be:
    * A fixed simulation run time (e.g., simulate 8 hours), or
    * A condition-based stop, such as after a certain number of vehicles have been served or a performance metric stabilizes.
  * Once this event is triggered, the simulation terminates and results are recorded.
### Time Advance Mechanism
The simulation clock advances using a next-event time advance mechanism.
Instead of progressing in fixed time intervals, the simulation jumps directly to the time of the next scheduled event from the FEL.
### Event scheduling Approach
1. **Initialize**  
   The simulation starts by scheduling the first vehicle arrival and the simulation end event.

2. **Process events**  
   The simulation continuously:  
   * Retrieves the next event from the FEL,  
   * Advances the clock to the event’s time,  
   * Executes the event logic.

3. **Event execution**  
   Each event updates the state of the parking lot and may schedule new events. For example:  
   * A vehicle arrival checks for free slots. If available, a parking start event is scheduled; otherwise, the vehicle joins the waiting queue.  
   * A parking end (departure) frees up a slot and, if there are waiting vehicles, triggers the next parking start event.
**Future Evenets**
* **Arrival event:**??
* **Service completion event:**??
* **Stopping event:**?? kalani anlamadim bunlari rapora mi koymaliyiz buraya mi

## Simulation Program

## Verification and Validation
