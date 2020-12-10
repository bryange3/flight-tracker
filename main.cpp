// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include <fstream>
#include "plane.h"
#include "planes.h"
#include "crewMember.h"
#include "crewMembers.h"
#include "flight.h"
#include "flights.h"
using namespace std;

void storeAll(Planes planes, CrewMembers crewMembers, Flights flights) {
    planes.store();
    crewMembers.store();
    flights.store();
}

void loadAll(Planes planes, CrewMembers crewMembers, Flights flights) {
    ifstream fin;
    
    // requires that all data files exist in order to load
    fin.open("planes.dat");
    if (fin.fail())
    {
	cout << "Missing file, so could not load" << endl;
	return;
    }
    fin.close();
    fin.open("pilot.dat");
    if (fin.fail())
    {
        cout << "Missing file, so could not load" << endl;
        return;
    }
    fin.close();
    fin.open("copilot.dat");
    if (fin.fail())
    {
        cout << "Missing file, so could not load" << endl;
        return;
    }
    fin.close();
    fin.open("cabin.dat");
    if (fin.fail())
    {
        cout << "Missing file, so could not load" << endl;
        return;
    }
    fin.close();
    fin.open("flights.dat");
    if (fin.fail())
    {
        cout << "Missing file, so could not load" << endl;
        return;
    }
    fin.close();
    
    // load
    planes.load();
    crewMembers.load();
    flights.load();
}

int main() {
    int option, planeOption, crewMemberOption, flightOption;
    Planes planes;
    CrewMembers crewMembers;
    Flights flights;
    
    loadAll(planes, crewMembers, flights);
    
    cout << "CSCE 1040.001 - HW4" << endl;
    cout << "Bryan Ge - bryange@my.unt.edu" << endl << endl;
    
    do { // overal program menu
        cout << "- Mean Green Airlines Application -" << endl << "What would you like to do?" << endl << endl;
        cout << "0. Quit program" << endl;
        cout << "1. Plane operations" << endl;
        cout << "2. Crew member operations" << endl;
        cout << "3. Flight operations" << endl;
        cout << "4. Store all information" << endl;
        cout << "5. Load information" << endl << endl;
        cin >> option;
        
        switch (option)
        {
            case 0:
                break;
            case 1:
            {
                do { // plane operations menu
                    cout << endl << "Plane Operations" << endl << "What would you like to do?" << endl << endl;
                    cout << "0. Quit plane operations" << endl;
                    cout << "1. Add a plane" << endl;
                    cout << "2. Edit a plane" << endl;
                    cout << "3. Delete a plane" << endl;
                    cout << "4. Find a plane" << endl;
                    cout << "5. Print all planes" << endl;
                    cout << "6. Print details for a single plane" << endl;
                    cin >> planeOption;
                    cout << endl;
                    
                    switch (planeOption)
                    {
                        case 0:
                            break;
                        case 1:
                        {
                            planes.addPlane();
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 2:
                        {
                            planes.editPlane();
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 3:
                        {
                            if (planes.emptyPlanesMap())
                            { // no planes exist in the planes map
                                cout << "No planes have been created, thus no planes can be deleted" << endl;
                                break;
                            }
                            string planeID;
                            cout << "Enter plane ID for plane to delete: ";
                            cin >> planeID;
                            if (planes.findPlane(planeID) == NULL)
                            { // plane cannot be found given the plane ID
                                cout << "Invalid plane ID" << endl;
                                break;
                            }
                            if (flights.findPlaneFlights(planeID) == NULL)
                            { // plane is not scheduled for any flights
                                planes.deletePlane(planeID);
                                storeAll(planes, crewMembers, flights);
                            }
                            else
                            {
                                cout << "Plane has been assigned to flights, so plane was not deleted" << endl;
                            }
                            break;
                        }
                        case 4:
                        {
                            planes.searchPlane();
                            break;
                        }
                        case 5:
                        {
                            planes.printAllPlanes();
                            break;
                        }
                        case 6:
                        {
                            planes.printSinglePlane();
                            break;
                        }
                        default:
                            break;
                    }
                } while (planeOption != 0);
                break;
            }
            case 2:
            {
                do { // crew member operations menu
                    cout << endl << "Crew Member Operations" << endl << "What would you like to do?" << endl << endl;
                    cout << "0. Quit crew member operations" << endl;
                    cout << "1. Add a crew member" << endl;
                    cout << "2. Edit a crew member" << endl;
                    cout << "3. Delete a crew member" << endl;
                    cout << "4. Find a crew member" << endl;
                    cout << "5. Print all crew members' information" << endl;
                    cout << "6. Print details for a single crew member" << endl;
                    cin >> crewMemberOption;
                    cout << endl;
                    
                    switch (crewMemberOption)
                    {
                        case 0:
                            break;
                        case 1:
                        {
                            crewMembers.addCrewMember();
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 2:
                        {
                            crewMembers.editCrewMember();
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 3:
                        {
                            if (crewMembers.emptyCrewMembersMap())
                            { // no crew members exist
                                cout << "No crew members have been created, thus no crew members can be deleted" << endl;
                                break;
                            }
                            int crewID;
                            cout << "Enter crew member ID for crew member to delete: ";
                            cin >> crewID;
                            if (flights.findCrewMemberFlights(crewID) == NULL)
                            { // crew member is not scheduled for any flights
                                crewMembers.deleteCrewMember(crewID);
                                storeAll(planes, crewMembers, flights);
                            }
                            else
                            {
                                cout << "Crew member has been assigned to flights, so crew member was not deleted" << endl;
                            }
                            break;
                        }
                        case 4:
                        {
                            crewMembers.searchCrewMember();
                            break;
                        }
                        case 5:
                        {
                            crewMembers.printAllCrewMembers();
                            break;
                        }
                        case 6:
                        {
                            crewMembers.printSingleCrewMember();
                            break;
                        }
                        default:
                            break;
                    }
                } while (crewMemberOption != 0);
                break;
            }
            case 3:
            {
                do { // flight operations menu
                    cout << endl << "Flight Operations" << endl << "What would you like to do?" << endl << endl;
                    cout << "0. Quit flight operations" << endl;
                    cout << "1. Add a flight" << endl;
                    cout << "2. Edit a flight" << endl;
                    cout << "3. Delete a flight" << endl;
                    cout << "4. Find a flight" << endl;
                    cout << "5. Print all flights' information" << endl;
                    cout << "6. Print details for a single flight" << endl;
                    cout << "7. Print flights of a certain flight status" << endl;
                    cout << "8. Print assignment schedule for a plane" << endl;
                    cout << "9. Delete completed and cancelled flights" << endl;
                    cin >> flightOption;
                    cout << endl;
                    
                    switch (flightOption)
                    {
                        case 0:
                            break;
                        case 1:
                        {
                            flights.addFlight(&planes, &crewMembers);
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 2:
                        {
                            flights.editFlight(&planes, &crewMembers);
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 3:
                        {
                            flights.deleteFlight();
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        case 4:
                        {
                            flights.searchFlight();
                            break;
                        }
                        case 5:
                        {
                            flights.printAllFlights();
                            break;
                        }
                        case 6:
                        {
                            flights.printSingleFlight();
                            break;
                        }
                        case 7:
                        {
                            flights.printFlightsBasedOnStatus();
                            break;
                        }
                        case 8:
                        {
                            flights.printAssignmentScheduleForPlane();
                            break;
                        }
                        case 9:
                        {
                            flights.deleteCompletedCancelledFlights();
                            storeAll(planes, crewMembers, flights);
                            break;
                        }
                        default:
                            break;
                    }
                } while (flightOption != 0);
                break;
            }
            case 4:
            {
                storeAll(planes, crewMembers, flights);
                cout << "Information successfully stored" << endl;
                break;
            }
            case 5:
            {
                loadAll(planes, crewMembers, flights);
                cout << "Information successfully loaded" << endl;
                break;
            }
            default:
                break;
        }
    } while (option != 0);
    
    return 0;
}

