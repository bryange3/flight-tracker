// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <fstream>
#include "flights.h"
#include "flight.h"
#include "planes.h"
#include "plane.h"
#include "crewMembers.h"
#include "crewMember.h"
using namespace std;

Flight* Flights::findFlight(string flightID) {
    map<string,Flight*>::iterator it = flights.find(flightID);
    if(it != flights.end())
    {
        // element found
        return it->second;
    }
    return NULL;
}

void Flights::searchFlight() {
    Flight* flight;
    string flightID;
    
    cout << "Enter flight ID of the flight you want to check exists or not: ";
    cin >> flightID;
    
    flight = findFlight(flightID);
    if (flight != NULL)
    {
        cout << "Flight with flight ID " << flightID << " exists" << endl;
    }
    else
    {
        cout << "Flight with flight ID " << flightID << " does not exist" << endl;
    }
}

vector<Flight*>* Flights::findPlaneFlights(string planeID) { // if null, plane is not scheduled for any flights
    map<string, vector<Flight*>*>::iterator it = planeIDtoFlightPtrs.find(planeID);
    if(it != planeIDtoFlightPtrs.end())
    {
        // element found
        return it->second;
    }
    return NULL;
}

vector<Flight*>* Flights::findCrewMemberFlights(int crewID) { // if null, plane is not scheduled for any flights
    map<int, vector<Flight*>*>::iterator it = crewIDtoFlightPtrs.find(crewID);
    if(it != crewIDtoFlightPtrs.end())
    {
        // element found
        return it->second;
    }
    return NULL;
}

bool Flights::validatePlaneFlightTimes(Flight* flightPtr, string hint) { // returns true for valid plane flight times and false for invalid plane flight times
    string planeID = flightPtr->getPlaneID();
    vector<Flight*>* flightsUsingPlane = findPlaneFlights(planeID);
    if (flightsUsingPlane == NULL)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < flightsUsingPlane->size(); i++)
        {
            if ((hint == "edit") && (flightPtr == flightsUsingPlane->at(i)))
            { // when editing, don't check flight times against flight being edited
                continue;
            }
            if (flightsUsingPlane->at(i)->flightCompletedOrCancelled() == false)
            { // only check passed in flight times against active flights
                if (validate2FlightTimes(flightPtr, flightsUsingPlane->at(i), "plane") == false)
                {
                    return false;
                }
            }
        }
        return true;
    }
    
}

bool Flights::validateCrewMemberFlightTimes(Flight* flightPtr, int crewID, string hint) { // returns true for valid crew member flight times and false for invalid crew member flight times - potential flight for the crew member
    
    vector<Flight*>* flightsUsingCrewMember = findCrewMemberFlights(crewID);
    if (flightsUsingCrewMember == NULL)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < flightsUsingCrewMember->size(); i++)
        {
            if ((hint == "edit") && (flightPtr == flightsUsingCrewMember->at(i)))
            { // when editing, don't check flight times against flight being edited
                continue;
            }
            if (flightsUsingCrewMember->at(i)->flightCompletedOrCancelled() == false)
            { // only check passed in flight times against active flights
                if (validate2FlightTimes(flightPtr, flightsUsingCrewMember->at(i), "crew member") == false)
                {
                    return false;
                }
            }
        }
        return true;
    }
    
}

bool Flights::validate2FlightTimes(Flight* flightPtr1, Flight* flightPtr2, string hint) { // returns true for valid and false for invalid flight times
    tm flight1Start = flightPtr1->getStartDateTime();
    tm flight1End = flightPtr1->getEndDateTime();
    tm flight2Start = flightPtr2->getStartDateTime();
    tm flight2End = flightPtr2->getEndDateTime();
    
    return Flight::validate2FlightTimes(flight1Start, flight1End, flight2Start, flight2End, hint);
}

bool Flights::validateNumSeatsForPass(Plane* plane, int numExpectedPassengers) {
    if (plane->getNumSeats() < numExpectedPassengers)
    {
        cout << "Not enough seats on the plane for " << numExpectedPassengers << " passengers" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

void Flights::addFlight(Planes* planes, CrewMembers* crewMembers) { // TODO before adding a flight, update all flight statuses & delete the completed/cancelled flights
    Flight* flight;
    Plane* plane;
    CrewMember* crewMember;
    string flightID;
    string planeID;
    int numPilots;
    int numCopilots;
    int numCabin;
    int tempCrewID;
    tm startDateTime;
    tm endDateTime;
    string startAirportCode; // 3 letters
    string endAirportCode;
    int numPassengers;
    string status; // active, complete, cancelled
    string choice;
    bool flightOver8Hours;
    
    cout << "ADD FLIGHT" << endl;
    do {
        cout << "Enter flight ID: ";
        cin >> flightID;
        flight = findFlight(flightID);
        if (flight != NULL) {
            cout << "Flight already exists" << endl;
            do {
                cout << "Would you like to enter a different flight ID? (yes/no) ";
                cin >> choice;
                if ((choice != "yes") && (choice != "no"))
                {
                    cout << "Please answer yes or no." << endl;
                }
                else
                {
                    if (choice == "no")
                    {
                        return; // leave function
                    }
                    else
                    {
                        break; // break out of inner do-while loop
                    }
                }
            } while (true);
        }
    } while (flight != NULL);
    flight = new Flight();
    flight->setFlightID(flightID);
    
    cout << "Enter the number of passengers on the flight: "; // TODO check for numPassengers
    cin >> numPassengers;
    flight->setNumPassengers(numPassengers);
    
    do {
        do {
            cout << "Enter plane ID/tail number: ";
            cin >> planeID;
            plane = planes->findPlane(planeID);
            if (plane == NULL) {
                cout << "Plane does not exist" << endl;
                do {
                    cout << "Would you like to enter a different plane ID? (yes/no) ";
                    cin >> choice;
                    if ((choice != "yes") && (choice != "no"))
                    {
                        cout << "Please answer yes or no." << endl;
                    }
                    else
                    {
                        if (choice == "no")
                        {
                            return; // leave function
                        }
                        else
                        {
                            break; // break out of inner do-while loop
                        }
                    }
                } while (true);
            }
        } while (plane == NULL); // validates plane ID
    } while (validateNumSeatsForPass(plane, numPassengers) == false); // verifies that there are enough seats for the number of passengers the user chooses
    flight->setPlaneID(planeID);

    map<string, Flight*>::iterator it;
    
    for (it = flights.begin(); it != flights.end(); it++)
    {
        ((*it).second)->markFlightCompleted();
    }
    
    do {
        do {
            flight->setTime("start"); // TODO are these correct
            startDateTime = flight->getStartDateTime();
            flight->setTime("end");
            endDateTime = flight->getEndDateTime();
            cout << endl;
        } while (flight->validateDatesAndTimes(startDateTime, endDateTime) == false);
    } while (validatePlaneFlightTimes(flight, "add") == false); // do-while loop checks for overlapping flights involving the same
    
    flightOver8Hours = flight->flightOver8Hours();
    
    if (flightOver8Hours == true)
    {
        do {
            cout << "Enter number of pilots (not including copilots): ";
            cin >> numPilots;
            if (numPilots < 2)
                cout << "This flight is over 8 hours so there must be at least 2 pilots" << endl;
        } while (numPilots < 2);
        flight->setNumPilots(numPilots);
        do {
            cout << "Enter number of copilots: ";
            cin >> numCopilots;
            if (numCopilots < 2)
                cout << "This flight is over 8 hours so there must be at least 2 copilots" << endl;
        } while (numCopilots < 2);
        flight->setNumCopilots(numCopilots);
        do {
            cout << "Enter number of cabin crew members: ";
            cin >> numCabin;
            if (numCabin < 2*(plane->getMinCrew()))
                cout << "This flight is over 8 hours so the number of cabin crew members must be double the plane's minimum number of cabin crew members (at least " << 2*(plane->getMinCrew()) << " cabin crew members)" << endl;
        } while (numCabin < 2*(plane->getMinCrew()));
        flight->setNumCabin(numCabin);
    }
    else
    {
        cout << "Enter number of pilots (not including copilots): ";
        cin >> numPilots;
        flight->setNumPilots(numPilots);
        cout << "Enter number of copilots: ";
        cin >> numCopilots;
        flight->setNumCopilots(numCopilots);
        do {
            cout << "Enter number of cabin crew members: ";
            cin >> numCabin;
            if (numCabin < plane->getMinCrew())
                cout << "The minimum number of cabin crew members for the plane used for this flight is " << plane->getMinCrew() << endl;
        } while (numCabin < plane->getMinCrew());
        flight->setNumCabin(numCabin);
    }
    
    vector<int>* pilotIDs = new vector<int>();
    // TODO make sure no crew member ID is added twice
    for (int i = 0; i < numPilots; i++)
    {
        do {
            cout << "Enter pilot ID: ";
            cin >> tempCrewID;
            crewMember = crewMembers->findCrewMember(tempCrewID);
            if (crewMember == NULL)
            {
                cout << "This crew member does not exist" << endl;
            }
            else
            {
                if (crewMember->getType() != "Pilot")
                {
                    cout << "Please enter the crew member ID of a pilot" << endl;
                    crewMember = NULL;
                    continue;
                }
                if (validateCrewMemberFlightTimes(flight, tempCrewID, "add") == false)
                {
                    cout << "This crew member is assigned to another flight which conflicts with this flight time" << endl;
                    crewMember = NULL; // makes loop run again because the crew member given is not valid
                    continue;
                }
                if ((crewMember->getStatus() == "on leave") || (crewMember->getStatus() == "sick"))
                {
                    cout << "This crew member is not available (either on leave or sick)" << endl;
                    crewMember = NULL; // makes loop run again because the crew member given is not valid
                }
            }
        } while (crewMember == NULL);
        pilotIDs->push_back(tempCrewID);
    }
    flight->setPilotIDs(pilotIDs);
    
    vector<int>* copilotIDs = new vector<int>();
    for (int i = 0; i < numCopilots; i++)
    {
        do {
            cout << "Enter copilot ID: ";
            cin >> tempCrewID;
            crewMember = crewMembers->findCrewMember(tempCrewID);
            if (crewMember == NULL)
            {
                cout << "This crew member does not exist" << endl;
            }
            else
            {
                if (crewMember->getType() != "CoPilot")
                {
                    cout << "Please enter the crew member ID of a copilot" << endl;
                    crewMember = NULL;
                    continue;
                }
                if (validateCrewMemberFlightTimes(flight, tempCrewID, "add") == false)
                {
                    cout << "This crew member is assigned to another flight which conflicts with this flight time" << endl;
                    crewMember = NULL; // makes loop run again because the crew member given is not valid
                    continue;
                }
                if ((crewMember->getStatus() == "on leave") || (crewMember->getStatus() == "sick"))
                {
                    cout << "This crew member is not available (either on leave or sick)" << endl;
                    crewMember = NULL; // makes loop run again because the crew member given is not valid
                }
            }
        } while (crewMember == NULL);
        copilotIDs->push_back(tempCrewID);
    }
    flight->setCopilotIDs(copilotIDs);
    
    vector<int>* cabinCrewIDs = new vector<int>();
    for (int i = 0; i < numCabin; i++)
    {
        do {
            cout << "Enter cabin crew member ID: ";
            cin >> tempCrewID;
            crewMember = crewMembers->findCrewMember(tempCrewID);
            if (crewMember == NULL)
            {
                cout << "This crew member does not exist" << endl;
            }
            else
            {
                if (crewMember->getType() != "Cabin")
                {
                    cout << "Please enter the crew member ID of a cabin crew member" << endl;
                    crewMember = NULL;
                    continue;
                }
                if (validateCrewMemberFlightTimes(flight, tempCrewID, "add") == false)
                {
                    cout << "This crew member is assigned to another flight which conflicts with this flight time" << endl;
                    crewMember = NULL; // makes loop run again because the crew member given is not valid
                    continue;
                }
                if ((crewMember->getStatus() == "on leave") || (crewMember->getStatus() == "sick"))
                {
                    cout << "This crew member is not available (either on leave or sick)" << endl;
                    crewMember = NULL; // makes loop run again because the crew member given is not valid
                }
            }
        } while (crewMember == NULL);
        cabinCrewIDs->push_back(tempCrewID);
    }
    flight->setCabinCrewIDs(cabinCrewIDs);
    
    //TODO check airport codes for 3 letters
    //TODO check that start and end codes are not the same
    do {
        do {
            cout << "Enter starting airport code: ";
            cin >> startAirportCode;
            if (startAirportCode.size() != 3)
            {
                cout << "Airport code must be 3 letters long" << endl;
            }
        } while (startAirportCode.size() != 3);
    
        do {
            cout << "Enter ending airport code: ";
            cin >> endAirportCode;
            if (endAirportCode.size() != 3)
            {
                cout << "Airport code must be 3 letters long" << endl;
            }
        } while (endAirportCode.size() != 3);
        
        if (startAirportCode == endAirportCode)
        {
            cout << "Starting and ending airport code must be different" << endl;
        }
    } while (startAirportCode == endAirportCode);
    
    flight->setStartAirportCode(startAirportCode);
    flight->setEndAirportCode(endAirportCode);
    
    addFlightToPlaneIDtoFlightPtrs(flight);
    addFlightToCrewIDtoFlightPtrs(flight);
    flights[flightID] = flight;
}


void Flights::editFlight(Planes* planes, CrewMembers* crewMembers) { // TODO TODO TODO DO U NEED TO CHECK IF THE FLIGHT IS CURRENTLY IN FLIGHT BEFORE EDITING
    // can only edit status to cancelled or complete
    int editOption;
    Flight* flight;
    Plane* plane;
    CrewMember* crewMember;
    string flightID;
    string planeID;
    int numPilots;
    int numCopilots;
    int numCabin;
    int tempCrewID;
    tm startDateTime; // in GMT
    tm endDateTime;
    string startAirportCode; // 3 letters
    string endAirportCode;
    int numPassengers;
    string status;
    string choice;
    bool flightOver8Hours;
    
    if (flights.empty())
    {
        cout << "No flights have been created, thus no flights can be edited" << endl;
        return;
    }
    
    do {
        // TODO check if the planes vector is empty
        cout << "Enter flight ID of the flight you want to edit: ";
        cin >> flightID;
        flight = findFlight(flightID);
        if (flight == NULL) {
            cout << "Flight not found" << endl;
            do {
                cout << "Would you like to enter a different flight ID? (yes/no) ";
                cin >> choice;
                if ((choice != "yes") && (choice != "no"))
                {
                    cout << "Please answer yes or no." << endl;
                }
                else
                {
                    if (choice == "no")
                    {
                        return; // leave function
                    }
                    else
                    {
                        break; // break out of inner do-while loop
                    }
                }
            } while (true);
        }
    } while (flight == NULL);
    
    flight->markFlightCompleted();
    flight->printInfo();
    
    // initiliaze temp variables - TODO add when doing other checks
    plane = planes->findPlane(flight->getPlaneID());
    numPassengers = flight->getNumPassengers();
    
    do {
        cout << "0. Exit edit flight mode" << endl;
        cout << "1. Edit plane ID" << endl;
        cout << "2. Edit number of pilots & pilot IDs" << endl;
        cout << "3. Edit number of copilots & copilot IDs" << endl;
        cout << "4. Edit number of cabin crew members & cabin crew member IDs" << endl;
        cout << "5. Edit flight times" << endl;
        cout << "6. Edit start airport code" << endl;
        cout << "7. Edit end airport code" << endl;
        cout << "8. Edit number of passengers" << endl;
        cout << "9. Edit status" << endl;
        cin >> editOption;
        
        if (editOption > 10)
            cout << "Enter an option between 0-10" << endl;
        
        switch(editOption)
        {
            case 0:
                break;
            case 1:
            {
                do {
                    do {
                        cout << "Enter new plane ID/tail number: ";
                        cin >> planeID;
                        plane = planes->findPlane(planeID);
                        if (plane == NULL) {
                            cout << "Plane does not exist" << endl;
                            do {
                                cout << "Would you like to enter a different plane ID? (yes/no) ";
                                cin >> choice;
                                if ((choice != "yes") && (choice != "no"))
                                {
                                    cout << "Please answer yes or no." << endl;
                                }
                                else
                                {
                                    if (choice == "no")
                                    {
                                        return; // leave function
                                    }
                                    else
                                    {
                                        break; // break out of inner do-while loop
                                    }
                                }
                            } while (true);
                        }
                    } while (plane == NULL); // validates plane ID
                } while (validateNumSeatsForPass(plane, numPassengers) == false); // verifies that there are enough seats for the number of passengers the user chooses
                flight->setPlaneID(planeID);
                // TODO check new plane with time, number of passengers, minimum number of crew
                break;
            }
            case 2: // TODO check number of pilots with the 8 hour check & check pilot IDs with time
                // TODO for vectors of IDs -- CLEAR VECTORS BEFORE UPDATING WITH NEW IDS?
                // TODO for all crew member functions: make sure no one crew member is added twice to the vectors
            {
                flightOver8Hours = flight->flightOver8Hours();
                
                // prompt user for new number of pilots
                if (flightOver8Hours == true)
                {
                    do {
                        cout << "Enter new number of pilots (not including copilots): ";
                        cin >> numPilots;
                        if (numPilots < 2)
                            cout << "This flight is over 8 hours so there must be at least 2 pilots" << endl;
                    } while (numPilots < 2);
                    flight->setNumPilots(numPilots);
                }
                else
                {
                    cout << "Enter new number of pilots (not including copilots): ";
                    cin >> numPilots;
                    flight->setNumPilots(numPilots);
                }
                
                vector<int>* pilotIDs = new vector<int>();
                
                // prompt user for new pilot IDs
                for (int i = 0; i < numPilots; i++)
                {
                    do {
                        cout << "Enter pilot ID: ";
                        cin >> tempCrewID;
                        crewMember = crewMembers->findCrewMember(tempCrewID);
                        if (crewMember == NULL)
                        {
                            cout << "This crew member does not exist" << endl;
                        }
                        else
                        {
                            if (crewMember->getType() != "Pilot")
                            {
                                cout << "Please enter the crew member ID of a pilot" << endl;
                                crewMember = NULL;
                                continue;
                            }
                            bool existingPilotID = false;
                            for (int w = 0; w < flight->getPilotIDs()->size(); w++)
                            {
                                if (flight->getPilotIDs()->at(w) == tempCrewID)
                                {
                                    existingPilotID = true;
                                    break;
                                }
                            }
                            if ((existingPilotID == false) && (validateCrewMemberFlightTimes(flight, tempCrewID, "edit") == false))
                            {
                                cout << "This crew member is assigned to another flight which conflicts with this flight time" << endl;
                                crewMember = NULL; // makes loop run again because the crew member given is not valid
                            }
                        }
                    } while (crewMember == NULL);
                    pilotIDs->push_back(tempCrewID);
                }
                
                deleteFlightFromCrewIDtoFlightPtrs(flight->getPilotIDs(), flight);
                delete flight->getPilotIDs(); // delete old vector of pilot IDs
                flight->setPilotIDs(pilotIDs);
                addFlightForCrewMembersToCrewIDtoFlightPtrs(pilotIDs, flight);
                break;
            }
            case 3:
            {
                flightOver8Hours = flight->flightOver8Hours();
                
                // prompt user for new number of copilots
                if (flightOver8Hours == true)
                {
                    do {
                        cout << "Enter new number of copilots: ";
                        cin >> numCopilots;
                        if (numCopilots < 2)
                            cout << "This flight is over 8 hours so there must be at least 2 copilots" << endl;
                    } while (numCopilots < 2);
                    flight->setNumCopilots(numCopilots);
                }
                else
                {
                    cout << "Enter new number of copilots: ";
                    cin >> numCopilots;
                    flight->setNumCopilots(numCopilots);
                }
                
                vector<int>* copilotIDs = new vector<int>();
                
                //prompt user for new copilot IDs
                for (int i = 0; i < numCopilots; i++)
                {
                    do {
                        cout << "Enter copilot ID: ";
                        cin >> tempCrewID;
                        crewMember = crewMembers->findCrewMember(tempCrewID);
                        if (crewMember == NULL)
                        {
                            cout << "This crew member does not exist" << endl;
                        }
                        else
                        {
                            if (crewMember->getType() != "CoPilot")
                            {
                                cout << "Please enter the crew member ID of a copilot" << endl;
                                crewMember = NULL;
                                continue;
                            }
                            bool existingCopilotID = false;
                            for (int w = 0; w < flight->getCopilotIDs()->size(); w++)
                            {
                                if (flight->getCopilotIDs()->at(w) == tempCrewID)
                                {
                                    existingCopilotID = true;
                                    break;
                                }
                            }
                            if ((existingCopilotID == false) && (validateCrewMemberFlightTimes(flight, tempCrewID, "edit") == false))
                            {
                                cout << "This crew member is assigned to another flight which conflicts with this flight time" << endl;
                                crewMember = NULL; // makes loop run again because the crew member given is not valid
                            }
                        }
                    } while (crewMember == NULL);
                    copilotIDs->push_back(tempCrewID);
                }
                
                deleteFlightFromCrewIDtoFlightPtrs(flight->getCopilotIDs(), flight); //
                delete flight->getCopilotIDs(); // delete old vector of pilot IDs
                flight->setCopilotIDs(copilotIDs);
                addFlightForCrewMembersToCrewIDtoFlightPtrs(copilotIDs, flight);
                break;
            }
            case 4:
            {
                flightOver8Hours = flight->flightOver8Hours();
                
                if (flightOver8Hours == true)
                {
                    do {
                        cout << "Enter new number of cabin crew members: ";
                        cin >> numCabin;
                        if (numCabin < 2*(plane->getMinCrew()))
                            cout << "This flight is over 8 hours so the number of cabin crew members must be double the plane's minimum number of cabin crew members (at least " << 2*(plane->getMinCrew()) << " cabin crew members)" << endl;
                    } while (numCabin < 2*(plane->getMinCrew()));
                    flight->setNumCabin(numCabin);
                }
                else
                {
                    do {
                        cout << "Enter new number of cabin crew members: ";
                        cin >> numCabin;
                        if (numCabin < plane->getMinCrew())
                            cout << "The minimum number of cabin crew members for the plane used for this flight is " << plane->getMinCrew() << endl;
                    } while (numCabin < plane->getMinCrew());
                    flight->setNumCabin(numCabin);
                }
                
                vector<int>* cabinCrewIDs = new vector<int>();
                
                // prompt user for new cabin crew member IDs
                for (int i = 0; i < numCabin; i++)
                {
                    do {
                        cout << "Enter new cabin crew member ID: ";
                        cin >> tempCrewID;
                        crewMember = crewMembers->findCrewMember(tempCrewID);
                        if (crewMember == NULL)
                        {
                            cout << "This crew member does not exist" << endl;
                        }
                        else
                        {
                            if (crewMember->getType() != "Cabin")
                            {
                                cout << "Please enter the crew member ID of a cabin crew member" << endl;
                                crewMember = NULL;
                                continue;
                            }
                            bool existingCabinID = false;
                            for (int w = 0; w < flight->getCabinCrewIDs()->size(); w++)
                            {
                                if (flight->getCabinCrewIDs()->at(w) == tempCrewID)
                                {
                                    existingCabinID = true;
                                    break;
                                }
                            }
                            if ((existingCabinID == false) && (validateCrewMemberFlightTimes(flight, tempCrewID, "edit") == false))
                            {
                                cout << "This crew member is assigned to another flight which conflicts with this flight time" << endl;
                                crewMember = NULL; // makes loop run again because the crew member given is not valid
                            }
                        }
                    } while (crewMember == NULL);
                    cabinCrewIDs->push_back(tempCrewID);
                }
                
                deleteFlightFromCrewIDtoFlightPtrs(flight->getCabinCrewIDs(), flight); //
                delete flight->getCabinCrewIDs(); // delete old vector of pilot IDs
                flight->setCabinCrewIDs(cabinCrewIDs);
                addFlightForCrewMembersToCrewIDtoFlightPtrs(cabinCrewIDs, flight);
                break;
            }
            case 5:
            {
                do {
                    do {
                        flight->setTime("start"); // TODO are these correct
                        startDateTime = flight->getStartDateTime();
                        flight->setTime("end");
                        endDateTime = flight->getEndDateTime();
                    } while (flight->validateDatesAndTimes(startDateTime, endDateTime) == false);
                } while (validatePlaneFlightTimes(flight, "edit") == false); // do-while loop checks for overlapping flights involving the same
                break;
            }
            case 6:
            {
                cout << "Enter new starting airport code: ";
                cin >> startAirportCode;
                flight->setStartAirportCode(startAirportCode);
                break;
            }
            case 7:
            {
                cout << "Enter new ending airport code: ";
                cin >> endAirportCode;
                flight->setEndAirportCode(endAirportCode);
                break;
            }
            case 8:
            {
                cout << "Enter the new number of passengers on the flight: "; // TODO check for numPassengers
                cin >> numPassengers;
                flight->setNumPassengers(numPassengers);
                break;
            }
            case 9: // TODO check status
            {
                do {
                    cout << "Enter new status of the flight (active, completed, cancelled): ";
                    cin >> status;
                    if ((status != "active") && (status != "completed") && (status != "cancelled"))
                    {
                        cout << "Please enter active, completed, or cancelled" << endl;
                    }
                } while ((status != "active") && (status != "completed") && (status != "cancelled"));
                flight->setStatus(status);
                break;
            }
            default:
                break;
        }
    } while (editOption != 0);
}

void Flights::deleteFlight() {
    /*
     1. delete object in the vector associated with the map entry with the planeID/crewID
     2. if the vector is empty, erase the map entry
    */
    Flight* flight;
    string flightID;
    string choice;
    
    do {
        cout << "Enter flight ID: ";
        cin >> flightID;
        flight = findFlight(flightID);
        if (flight == NULL) {
            cout << "Flight does not exist" << endl;
            do {
                cout << "Would you like to enter a different flight ID? (yes/no) ";
                cin >> choice;
                if ((choice != "yes") && (choice != "no"))
                {
                    cout << "Please answer yes or no." << endl;
                }
                else
                {
                    if (choice == "no")
                    {
                        return; // leave function
                    }
                    else
                    {
                        break; // break out of inner do-while loop
                    }
                }
            } while (true);
        }
    } while (flight == NULL);

    flights.erase(flightID);
    deleteFlightsFromPlaneIDtoFlightPtrs(flight);
    deleteFlightsFromCrewIDtoFlightPtrs(flight);
    delete flight;
}

void Flights::printAllFlights() {
    if (flights.empty())
    {
        cout << "No flights have been created" << endl;
        return;
    }
    
    map<string, Flight*>::iterator it;
    
    cout << "Information for All Flights" << endl;
    for (it = flights.begin(); it != flights.end(); it++)
    {
        ((*it).second)->markFlightCompleted();
        ((*it).second)->printInfo();
    }
}

void Flights::printSingleFlight() {
    if (flights.empty())
    {
        cout << "No flights have been created" << endl;
        return;
    }
    
    string flightID;
    
    do {
        cout << "Enter the flight ID of the flight you would like details for: ";
        cin >> flightID;
        if (findFlight(flightID) == NULL)
            cout << "Flight associated with that flight ID could not be found" << endl;
    } while (findFlight(flightID) == NULL);
    flights.at(flightID)->markFlightCompleted();
    flights.at(flightID)->printInfo();
}

void Flights::printFlightsBasedOnStatus() {
    if (flights.empty())
    {
        cout << "No flights have been created" << endl;
        return;
    }
    
    string status;
    map<string, Flight*>::iterator it;
    
    do {
        cout << "Enter status of the flights you want to print (active, completed, cancelled): ";
        cin >> status;
        if ((status != "active") && (status != "completed") && (status != "cancelled"))
        {
            cout << "Please enter active, completed, or cancelled" << endl;
        }
    } while ((status != "active") && (status != "completed") && (status != "cancelled"));
    
    for (it = flights.begin(); it != flights.end(); it++)
    {
        (it->second)->markFlightCompleted();
        if (it->second->getStatus() == status)
        {
            it->second->printInfo();
        }
    }
}

void Flights::deleteCompletedCancelledFlights() {
    map<string, Flight*>::iterator it;
    Flight* flight;
    
    for (it = flights.begin(); it != flights.end(); it++)
    {
        (it->second)->markFlightCompleted();
        flight = it->second;
        if (flight->flightCompletedOrCancelled())
        {
            deleteFlightsFromPlaneIDtoFlightPtrs(flight);
            deleteFlightsFromCrewIDtoFlightPtrs(flight);
            flights.erase(flight->getFlightID()); // deletes the map entry
            delete flight; // deletes the flight object
        }
    }
}

void Flights::deleteFlightsFromPlaneIDtoFlightPtrs(Flight* flight) {
    string planeID = flight->getPlaneID();
    
    vector<Flight*>* planeFlights = findPlaneFlights(planeID);
    if (planeFlights != NULL)
    {
        for (int i = 0; i < planeFlights->size(); i++)
        {
            if (flight == planeFlights->at(i))
            {
                planeFlights->erase(planeFlights->begin() + i); // deletes Flight pointer from vector of Flight pointers
                if (planeFlights->size() == 0)
                { // no flights exist in the vector associated with the key flight->getPlaneID(), so we must erase the map entry
                    planeIDtoFlightPtrs.erase(flight->getPlaneID()); // deletes the map entry
                }
            }
        }
    }
    else
        cout << "This plane was not assigned any flights, so there are no flights to delete" << endl;
}

void Flights::deleteFlightsFromCrewIDtoFlightPtrs(Flight* flight) {
    deleteFlightFromCrewIDtoFlightPtrs(flight->getPilotIDs(), flight);
    deleteFlightFromCrewIDtoFlightPtrs(flight->getCopilotIDs(), flight);
    deleteFlightFromCrewIDtoFlightPtrs(flight->getCabinCrewIDs(), flight);
}

void Flights::deleteFlightFromCrewIDtoFlightPtrs(vector<int>* crewIDs, Flight* flight) {
    map<int,vector<Flight*>*>::iterator it;
    vector<Flight*>* crewFlights = NULL;
    int currCrewID;
    
    for (int i = 0; i < crewIDs->size(); i++)
    { // iterate through all crew IDs from the vector
        currCrewID = crewIDs->at(i); // set current crew ID to the crew ID at position i of the vector
        it = crewIDtoFlightPtrs.find(currCrewID); // find map entry for the current crew ID in the map crewIDtoFlightPtrs
        if (it != crewIDtoFlightPtrs.end())
        { // element found in the map
            crewFlights = it->second; // assigns vector of flights associated with the crewID from the crewIDtoFlightPtrs map
        }
        if (crewFlights != NULL)
        { // the vector exists (vector != NULL)
            for (int w = 0; w < crewFlights->size(); w++)
            { // iterate through the entire vector of flights
                if (flight == crewFlights->at(w))
                { // passed in flight to delete has the same contents as the Flight* found at position w
                    crewFlights->erase(crewFlights->begin() + w); // deletes Flight pointer from vector of Flight pointers
                    if (crewFlights->size() == 0)
                    { // no flights exist in the vector, so map entry must be erased
                        crewIDtoFlightPtrs.erase(currCrewID); // deletes the map entry
                    }
                }
            }
        }
        else
            cout << "This plane was not assigned any flights, so there are no flights to delete" << endl;
    }
}

void Flights::addFlightToPlaneIDtoFlightPtrs(Flight* flight) {
    string planeID = flight->getPlaneID();
    vector<Flight*>* flightPtrs;
    
    if (findPlaneFlights(planeID) == NULL)
    { // map entry using the planeID does not exist, meaning the planeID is not used by any flights
        flightPtrs = new vector<Flight*>;
        planeIDtoFlightPtrs[planeID] = flightPtrs;
    }
    else
    {
        flightPtrs = planeIDtoFlightPtrs.at(planeID);
    }
    flightPtrs->push_back(flight);
}

void Flights::addFlightToCrewIDtoFlightPtrs(Flight* flight) { // loop through all the crew members in the flight
    /*
     1. get crew ID from passed in flight
     2. check if planeID has been used by other flights by checking if vector pointer for the planeID is NULL in the PlaneIDtoFlightPtrs map

     */
    addFlightForCrewMembersToCrewIDtoFlightPtrs(flight->getPilotIDs(), flight);
    addFlightForCrewMembersToCrewIDtoFlightPtrs(flight->getCopilotIDs(), flight);
    addFlightForCrewMembersToCrewIDtoFlightPtrs(flight->getCabinCrewIDs(), flight);
}

void Flights::addFlightForCrewMembersToCrewIDtoFlightPtrs(vector<int>* crewIDs, Flight* flight) {
    vector<Flight*>* flightPtrs;
    for (int i = 0; i < crewIDs->size(); i++)
    {
        if (findCrewMemberFlights(crewIDs->at(i)) == NULL)
        { // map entry using the crewID at element i does not exist, meaning the crewID is not used by any flights
            flightPtrs = new vector<Flight*>;
            crewIDtoFlightPtrs[crewIDs->at(i)] = flightPtrs;
        }
        else
        {
            flightPtrs = crewIDtoFlightPtrs.at(crewIDs->at(i));
        }
        flightPtrs->push_back(flight);
    }
}
    

void Flights::printAssignmentScheduleForPlane() {
    string planeID;
    
    cout << "Enter ID/tail number of the plane you want to view the assignment schedule of: ";
    cin >> planeID;
    
    if (findPlaneFlights(planeID) == NULL)
    { // map entry using the planeID does not exist, meaning the planeID is not used by any flights
        cout << "Plane is not used on any flights" << endl;
    }
    else
    {
        vector<Flight*>* flightPtrs = findPlaneFlights(planeID);
        if (flightPtrs != NULL)
        {
            for (int i = 0; i < flightPtrs->size(); i++)
            {
                flightPtrs->at(i)->markFlightCompleted();
                flightPtrs->at(i)->printInfo();
            }
        }
        else
        {
            cout << "Plane is not used on any flights" << endl;
        }
    }
}

void Flights::printAssignmentScheduleForCrewMember() {
    int crewID;
    
    cout << "Enter crew member ID of the crew member you want to view the assignment schedule of: ";
    cin >> crewID;
    if (findCrewMemberFlights(crewID) == NULL)
    { // map entry using the crewID does not exist, meaning the crewID is not assigned to any flights
        cout << "Crew member is not assigned to any flights" << endl;
    }
    else
    {
        vector<Flight*>* flightPtrs = findCrewMemberFlights(crewID); // assigns vector of flights associated with the planeID from the planeIDtoFlightPtrs map
        if (flightPtrs != NULL)
        {
            for (int i = 0; i < flightPtrs->size(); i++)
            {
                flightPtrs->at(i)->markFlightCompleted();
                flightPtrs->at(i)->printInfo();
            }
        }
        else
        {
            cout << "This crew member is not assigned to any flights" << endl;
        }
    }
}

void Flights::store() {
    ofstream fout;
    fout.open("flights.dat");
    tm temp;
    Flight* flight;
    map<string, Flight*>::iterator it;
    
    fout << flights.size() << endl; // number of existing flights
    for (it = flights.begin(); it != flights.end(); it++)
    {
        flight = ((*it).second);
        fout << flight->getFlightID() << endl;
        fout << flight->getPlaneID() << endl;
        fout << flight->getNumPilots() << endl;
        for (int i = 0; i < flight->getNumPilots(); i++)
        {
            fout << flight->getPilotIDs()->at(i) << endl;
        }
        fout << flight->getNumCopilots() << endl;
        for (int i = 0; i < flight->getNumCopilots(); i++)
        {
            fout << flight->getCopilotIDs()->at(i) << endl;
        }
        fout << flight->getNumCabin() << endl;
        for (int i = 0; i < flight->getNumCabin(); i++)
        {
            fout << flight->getCabinCrewIDs()->at(i) << endl;
        }
        temp = flight->getStartDateTime();
        fout << mktime(&temp) << endl;
        temp = flight->getEndDateTime();
        fout << mktime(&temp) << endl;
        fout << flight->getStartAirportCode() << endl;
        fout << flight->getEndAirportCode() << endl;
        fout << flight->getNumPassengers() << endl;
        fout << flight->getStatus() << endl;
    }
    fout.close();
}

void Flights::load() {
    ifstream fin;
    int numFlights;
    string flightID;
    string planeID;
    int numPilots;
    int numCopilots;
    int numCabin;
    int crewID;
    vector<int>* pilotIDs;
    vector<int>* copilotIDs;
    vector<int>* cabinCrewIDs;
    time_t startDateTime; // in GMT
    time_t endDateTime;
    tm* start;
    tm* end;
    string startAirportCode; // 3 letters
    string endAirportCode;
    int numPassengers;
    string status;
    fin.open("flights.dat");
    Flight* flight;
    
    fin >> numFlights;
    for (int i = 0; i < numFlights; i++)
    {
        fin >> flightID;
        fin >> planeID;
        fin >> numPilots;
        pilotIDs = new vector<int>();
        for (int i = 0; i < numPilots; i++)
        {
            fin >> crewID;
            pilotIDs->push_back(crewID);
        }
        fin >> numCopilots;
        copilotIDs = new vector<int>();
        for (int i = 0; i < numCopilots; i++)
        {
            fin >> crewID;
            copilotIDs->push_back(crewID);
        }
        fin >> numCabin;
        cabinCrewIDs = new vector<int>();
        for (int i = 0; i < numCabin; i++)
        {
            fin >> crewID;
            cabinCrewIDs->push_back(crewID);
        }
        fin >> startDateTime;
        start = gmtime(&startDateTime);
        fin >> endDateTime;
        end = gmtime(&endDateTime);
        fin >> startAirportCode;
        fin >> endAirportCode;
        fin >> numPassengers;
        fin >> status;
        flight = new Flight(flightID, planeID, numPilots, numCopilots, numCabin, pilotIDs, copilotIDs, cabinCrewIDs, *start, *end, startAirportCode, endAirportCode, numPassengers, status);
        addFlightToPlaneIDtoFlightPtrs(flight);
        addFlightToCrewIDtoFlightPtrs(flight);
        flights[flightID] = flight;
    }
    
    fin.close();
}

