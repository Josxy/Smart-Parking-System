package smartparkingsystem;

import smartparkingsystem.ParkingLot;

network SmartParkingNetwork
{
    submodules:
        parkingLot: ParkingLot {
            @display("p=200,150");
        }
}