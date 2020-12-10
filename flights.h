// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef flights_h
#define flights_h

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "flight.h"
#include "planes.h"
#include "crewMembers.h"
using namespace std;

class Flights {
	private:
		map<string, vector<Flight*>*> planeIDtoFlightPtrs; // map plane ID to a pointer of a vector of Flight pointers
        map<int, vector<Flight*>*> crewIDtoFlightPtrs; // map crew ID to a pointer of a vector Flight pointers
        map<string, Flight*> flights; // map flight ID to a Flight pointer
	public:
        Flight* findFlight(string flightID);
        void searchFlight();
        vector<Flight*>* findPlaneFlights(string planeID); // if null, plane is not scheduled for any flights
        vector<Flight*>* findCrewMemberFlights(int crewID);
    
        bool validatePlaneFlightTimes(Flight* flightPtr, string hint); // validates that the plane is not being used in multiple flights at the same time
        bool validateCrewMemberFlightTimes(Flight* flightPtr, int crewID, string hint); // validates that a crew member isn't being assigned to multiple flights at the same time
        bool validate2FlightTimes(Flight* flightPtr1, Flight* flightPtr2, string hint); // given 2 flights, check if they are overlapping
        bool validateNumSeatsForPass(Plane* plane, int numExpectedPassengers);
    
        void addFlight(Planes* planes, CrewMembers* crewMembers);
        void addFlightToPlaneIDtoFlightPtrs(Flight* flight);
        void addFlightToCrewIDtoFlightPtrs(Flight* flight);
        void addFlightForCrewMembersToCrewIDtoFlightPtrs(vector<int>* crewIDs, Flight* flight);
        void editFlight(Planes* planes, CrewMembers* crewMembers);
        void deleteFlight();
        void deleteCompletedCancelledFlights();
        void deleteFlightsFromPlaneIDtoFlightPtrs(Flight* flight); // to be used to delete map entries from the planeIDtoFlightPtrs map in deleteCompletedCancelledFlights function
        void deleteFlightsFromCrewIDtoFlightPtrs(Flight* flight);
        void deleteFlightFromCrewIDtoFlightPtrs(vector<int>* crewIDs, Flight* flight);
    
        void printAllFlights();
        void printSingleFlight();
        void printFlightsBasedOnStatus();
        void printAssignmentScheduleForPlane();
        void printAssignmentScheduleForCrewMember();
        void store();
        void load();
};

#endif

