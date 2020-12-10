// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef flight_h
#define flight_h

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Flight {
    private:
        string flightID;
        string planeID;
        int numPilots;
        int numCopilots;
        int numCabin;
        vector<int>* pilotIDs;
        vector<int>* copilotIDs;
        vector<int>* cabinCrewIDs;
        tm startDateTime; // in GMT
        tm endDateTime;
        string startAirportCode; // 3 letters
        string endAirportCode;
        int numPassengers;
        string status; // active, completed, cancelled
    public:
        Flight(); // default constructor
        Flight(string flightID, string planeID, int numPilots, int numCopiltos, int numCabin, vector<int>* pilotIDs, vector<int>* copilotIDs, vector<int>* cabinCrewIDs, tm startDateTime, tm endDateTime, string startAirportCode, string endAirportCode, int numPassengers, string status);
        ~Flight(); // destructor

        // limits to prevent user from entering unrealistic values for respective flight attributes
        static const int minYear = 2019;
        static const int maxYear = 2020;
        static const int minMonth = 1;
        static const int maxMonth = 12;
        static const int minDay = 1;
        static const int maxDayFebNonLeap = 28;
        static const int maxDayFebLeap = 29;
        static const int maxDay30 = 30;
        static const int maxDay31 = 31;
        static const int minHour = 00;
        static const int maxHour = 23;
        static const int minMinute = 00;
        static const int maxMinute = 59;
        static const time_t minFlightTimeLength = 3600; // in seconds
        static const time_t maxFlightTimeLength = 86400; // in seconds
        static const time_t minGapBetweenFlights = 7200; // minimum gap between 2 flights using the same plane or crew member in seconds
        static const time_t flight8Hours = 28800;
        // TODO max num pilots
    
        string getFlightID();
        void setFlightID(string flightID);
        string getPlaneID();
        void setPlaneID(string planeID);
        int getNumPilots();
        void setNumPilots(int numPilots);
        int getNumCopilots();
        void setNumCopilots(int numCopilots);
        int getNumCabin();
        void setNumCabin(int numCabin);
        vector<int>* getPilotIDs();
        void setPilotIDs(vector<int>* pilotIDs);
        vector<int>* getCopilotIDs();
        void setCopilotIDs(vector<int>* copilotIDs);
        vector<int>* getCabinCrewIDs();
        void setCabinCrewIDs(vector<int>* cabinCrewIDs);
        tm getStartDateTime(); // in GMT
        void setStartDateTime(tm startDateTime);
        tm getEndDateTime();
        void setEndDateTime(tm endDateTime);
        string getStartAirportCode(); // 3 letters
        void setStartAirportCode(string startAirportCode);
        string getEndAirportCode();
        void setEndAirportCode(string endAirportCode);
        int getNumPassengers();
        void setNumPassengers(int numPassengers);
        string getStatus(); // active, complete, cancelled
        void setStatus(string status);
    
        void setTime(string hint);
        bool validateDatesAndTimes(tm start, tm end); // validate the start is earlier than the end time and validate flight is a realistic time length
        bool leapYear(int year); // true means passed in year is a leap year
        bool validateDayOfMonth(int maxDay, int day);
        static bool validate2FlightTimes(tm start1, tm end1, tm start2, tm end2, string hint); // check if two flights have overlapping times
        void markFlightCompleted(); // checks if a flight is complete
        bool flightCompletedOrCancelled();
        bool flightOver8Hours();
        void printInfo();
    
};

#endif

