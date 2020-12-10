// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include <fstream>
#include <ctime>
#include "flight.h"
using namespace std;

Flight::Flight() { // default constructor
    status = "active"; // when creating a flight, it's automatically set to active by default
}

Flight::Flight(string flightID, string planeID, int numPilots, int numCopilots, int numCabin, vector<int>* pilotIDs, vector<int>* copilotIDs, vector<int>* cabinCrewIDs, tm startDateTime, tm endDateTime, string startAirportCode, string endAirportCode, int numPassengers, string status) {
    this->flightID = flightID;
    this->planeID = planeID;
    this->numPilots = numPilots;
    this->numCopilots = numCopilots;
    this->numCabin = numCabin;
    this->pilotIDs = pilotIDs;
    this->copilotIDs = copilotIDs;
    this->cabinCrewIDs = cabinCrewIDs;
    this->startDateTime = startDateTime; // in GMT
    this->endDateTime = endDateTime;
    this->startAirportCode = startAirportCode; // 3 letters
    this->endAirportCode = endAirportCode;
    this->numPassengers = numPassengers;
    this->status = status; // active, completed, cancelled
}

Flight::~Flight() { // destructor
    if (pilotIDs != NULL)
        delete pilotIDs;
    if (copilotIDs != NULL)
        delete copilotIDs;
    if (cabinCrewIDs != NULL)
        delete cabinCrewIDs;
}

string Flight::getFlightID() {
    return flightID;
}

void Flight::setFlightID(string flightID) {
    this->flightID = flightID;
}

string Flight::getPlaneID() {
    return planeID;
}

void Flight::setPlaneID(string planeID) {
    this->planeID = planeID;
}

int Flight::getNumPilots() {
    return numPilots;
}

void Flight::setNumPilots(int numPilots) {
    this->numPilots = numPilots;
}

int Flight::getNumCopilots() {
    return numCopilots;
}

void Flight::setNumCopilots(int numCopilots) {
    this->numCopilots = numCopilots;
}

int Flight::getNumCabin() {
    return numCabin;
}

void Flight::setNumCabin(int numCabin) {
    this->numCabin = numCabin;
}

vector<int>* Flight::getCopilotIDs() {
    return copilotIDs;
}

void Flight::setCopilotIDs(vector<int>* copilotIDs) {
    this->copilotIDs = copilotIDs;
}

vector<int>* Flight::getPilotIDs() {
    return pilotIDs;
}

void Flight::setPilotIDs(vector<int>* pilotIDs) {
    this->pilotIDs = pilotIDs;
}

vector<int>* Flight::getCabinCrewIDs() {
    return cabinCrewIDs;
}

void Flight::setCabinCrewIDs(vector<int>* cabinCrewIDs) {
    this->cabinCrewIDs = cabinCrewIDs;
}

tm Flight::getStartDateTime() { // in GMT
    return startDateTime;
}

void Flight::setStartDateTime(tm startDateTime) {
    this->startDateTime = startDateTime;
}

tm Flight::getEndDateTime() {
    return endDateTime;
}

void Flight::setEndDateTime(tm endDateTime) {
    this->endDateTime = endDateTime;
}

string Flight::getStartAirportCode() { // 3 letters
    return startAirportCode;
}

void Flight::setStartAirportCode(string startAirportCode) {
    this->startAirportCode = startAirportCode;
}

string Flight::getEndAirportCode() {
    return endAirportCode;
}

void Flight::setEndAirportCode(string endAirportCode) {
    this->endAirportCode = endAirportCode;
}

int Flight::getNumPassengers() {
    return numPassengers;
}

void Flight::setNumPassengers(int numPassengers) {
    this->numPassengers = numPassengers;
}

string Flight::getStatus() { // active, completed, cancelled
    return status;
}

void Flight::setStatus(string status) {
    this->status = status;
}

void Flight::setTime(string hint) {
    int month;
    int day;
    int year;
    int hour;
    int minute;
    // long valid;
    string choice;
    tm tempDateTime;
    bool validDay;

        if (hint == "start")
        {
            cout << "Enter flight start time information in GMT" << endl;
        }
        else
        {
            cout << "Enter flight end time information in GMT" << endl;
        }
        
        do {
            cout << "Enter year (YYYY): "; cin >> year;
            if ((year > maxYear) || (year < minYear))
                cout << "Please enter a year between " << minYear << " and " << maxYear << endl;
        } while ((year > maxYear) || (year < minYear));
        
        do {
            cout << "Enter month (1-12): "; cin >> month;
            if ((month > maxMonth) || (year < minMonth))
                cout << "Please enter a month between " << minMonth << " and " << maxMonth << endl;
        } while ((month > maxMonth) || (month < minMonth));
        
        do {
            cout << "Enter day of the month in the format ##: "; cin >> day;
            if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
            {
                validDay = validateDayOfMonth(maxDay31, day);
            }
            else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
            {
                validDay = validateDayOfMonth(maxDay30, day);
            }
            else // february case
            {
                if (leapYear(year))
                {
                    validDay = validateDayOfMonth(maxDayFebLeap, day);
                }
                else
                {
                    validDay = validateDayOfMonth(maxDayFebNonLeap, day);
                }
            }
        } while (validDay == false);
        
        do {
            cout << "Enter hour of the day in the format ## (24-hour time in GMT): "; cin >> hour;
            if ((hour > maxHour) || (hour < minHour))
                cout << "Please enter an hour of the day between " << minHour << " and " << maxHour << endl;
        } while ((hour > maxHour) || (hour < minHour));
    
        do {
            cout << "Enter minute of the day in the format ##: "; cin >> minute;
            if ((hour > maxMinute) || (hour < minMinute))
                cout << "Please enter a minute of the day between " << minMinute << " and " << maxMinute << endl;
        } while ((hour > maxMinute) || (hour < minMinute));
    
        tempDateTime.tm_year = year-1900; // years start from 1900
        tempDateTime.tm_mon = month-1; // months start from 0 http://www.cplusplus.com/reference/ctime/tm/
        tempDateTime.tm_mday = day;
        tempDateTime.tm_hour = hour;
        tempDateTime.tm_min = minute;
        tempDateTime.tm_sec = 0; // make sure seconds is set (to prevent error with random number of seconds)
    
        if (hint == "start")
        {
            startDateTime = tempDateTime; // assign temporary date and time information to startDateTime
        }
        else
        {
            endDateTime = tempDateTime; // assign temporary date and time information to endDateTime
        }
        return; // leave function
}

bool Flight::validateDatesAndTimes(tm start, tm end) { // validates flight time for a flight
    time_t startSinceEpoch = mktime(&start);
    time_t endSinceEpoch = mktime(&end);
    
    if (startSinceEpoch >= endSinceEpoch)
    {
        cout << "Start date and time must come before end date and time" << endl;
        return false;
    }
    time_t flightTimeLength = endSinceEpoch - startSinceEpoch;
    if ((flightTimeLength > maxFlightTimeLength) || (flightTimeLength < minFlightTimeLength))
    {
        cout << "Flight time length must be between " << minFlightTimeLength/3600 << " and " << maxFlightTimeLength/3600 << " hours" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool Flight::leapYear(int year) {
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool Flight::validateDayOfMonth(int maxDay, int day) {
    if ((day > maxDay) || (day < minDay))
    {
        cout << "Please enter a day of the month between " << minDay << " and " << maxDay << endl;
        return false;
    }
    else
    {
        return true;
    }
}


// TODO to be used when checking with planes and crew members
bool Flight::validate2FlightTimes(tm start1, tm end1, tm start2, tm end2, string hint) { // check that 2 flights using the same plane do not conflict in any way - returns true for valid and false for invalid flight times
    time_t startSinceEpoch1 = mktime(&start1);
    time_t endSinceEpoch1 = mktime(&end1);
    time_t startSinceEpoch2 = mktime(&start2);
    time_t endSinceEpoch2 = mktime(&end2);
    time_t flightGap;
    
    if (startSinceEpoch2 > endSinceEpoch1)
    { // start time of flight 2 comes after end time of flight 1
        flightGap = startSinceEpoch2 - endSinceEpoch1;
        if (flightGap < minGapBetweenFlights)
        {
            cout << "Not enough of a time gap between this flight and another flight involving the same " << hint << endl;
            return false;
        }
        else
        {
            return true;
        }
    }
    else if (endSinceEpoch2 < startSinceEpoch1)
    { // end time of flight 2 comes before start time of flight 1
        flightGap = startSinceEpoch1 - endSinceEpoch2;
        if (flightGap < minGapBetweenFlights)
        {
            cout << "Not enough of a time gap between this flight and another flight involving the same " << hint << endl;
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        cout << "Current flight overlaps with another flight involving the same " << hint << endl; // TODO check this
        return false;
    }
}

void Flight::markFlightCompleted() {
    time_t currentTime = time(0);
    tm *gmtm = gmtime(&currentTime);
    time_t currentSinceEpoch = mktime(gmtm);
    time_t endSinceEpoch = mktime(&endDateTime);
    
    if(status == "active")
    {
        if (endSinceEpoch <= currentSinceEpoch)
        {
            status = "completed";
        }
    }
}

bool Flight::flightCompletedOrCancelled() {
    if ((status == "cancelled") || (status == "completed"))
        return true;
    else
        return false;
}

bool Flight::flightOver8Hours() {
    time_t flightStart = mktime(&startDateTime);
    time_t flightEnd = mktime(&endDateTime);
    time_t flightTimeLength = flightStart - flightEnd;
    
    if (flightTimeLength > flight8Hours)
        return true;
    else
        return false;
}

void Flight::printInfo() {
    cout << endl << "Flight ID: " << flightID << " ";
    cout << "Plane ID: " << planeID << " ";
    cout << "Number of pilots: " << numPilots << " ";
    cout << "Number of copilots: " << numCopilots << " ";
    cout << "Number of cabin crew members: " << numCabin << " ";
    cout << endl << "Pilot IDs: ";
    for (int i = 0; i < pilotIDs->size(); i++)
    {
        cout << pilotIDs->at(i) << " ";
    }
    cout << endl << "Copilot IDs: ";
    for (int i = 0; i < copilotIDs->size(); i++)
    {
        cout << copilotIDs->at(i) << " ";
    }
    cout << endl << "Cabin crew member IDs: ";
    for (int i = 0; i < cabinCrewIDs->size(); i++)
    {
        cout << cabinCrewIDs->at(i) << " ";
    }
    cout << endl << "Start date and time: " << asctime(&startDateTime);
    cout << "End date and time: " << asctime(&endDateTime);
    cout << "Starting airport code: " << startAirportCode << " ";
    cout << "Ending airport code: " << endAirportCode << " ";
    cout << "Number of passengers: " << numPassengers << " ";
    cout << "Status: " << status << endl;
}

