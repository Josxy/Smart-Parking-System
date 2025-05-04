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
Each evenet includes:
  * Type of event
  * Scheduled time of event
Events are stored in a priority queue, with the earliest event always processed next. This ensures that all activities within the simulation occur in the correct order over time.
### Time Advance Mechanism
The simulation clock advances using a next-event time advance mechanism.
Instead of progressing in fixed time intervals, the simulation jumps directly to the time of the next scheduled event from the FEL.
### Event scheduling Approach
1. Initialize
  * The simulation starts by scheduling the first vehicle arrival and the simulation end event. 
2. Process events
  The simulation continuously:

    * Retrieves the next event from the FEL,

    * Advances the clock to the event’s time,

    * Executes the event logic.
3. Event execution
Each event updates the state of the parking lot and may schedule new events. For example:
  * A vehicle arrival checks for free slots. If available, a parking start event is scheduled; otherwise, the vehicle joins the waiting queue.
  * A parking end (departure) frees up a slot and, if there are waiting vehicles, triggers the next parking start e
**Future Evenets**
* **Arrival event:**??
* **Service completion event:**??
* **Stopping event:**?? kalani anlamadim bunlari rapora mi koymaliyiz buraya mi

## Simulation Program

## Verification and Validation
