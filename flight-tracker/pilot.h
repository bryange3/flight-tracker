// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef pilot_h
#define pilot_h

#include <iostream>
#include "crewMember.h"
using namespace std;

class Pilot : public CrewMember {
    private:
        string ratingCode; // 5 characters
        double flightHours;
    public:
        Pilot(string name, int ID, string status, string ratingCode, double flightHours);
        ~Pilot();
    
        string getType();
        string getRatingCode();
        void setRatingCode(string ratingCode);
        double getFlightHours();
        void setFlightHours(double flightHours);
        void printInfo();
};

#endif /* pilot_h */
