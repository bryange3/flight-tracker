// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef coPilot_h
#define coPilot_h

#include <iostream>
#include "crewMember.h"
using namespace std;

class CoPilot : public CrewMember {
    private:
        string ratingCode; // 4 characters
        double flightHours;
    public:
        CoPilot(string name, int ID, string status, string ratingCode, double flightHours);
        ~CoPilot();
    
        string getType();
        string getRatingCode();
        void setRatingCode(string ratingCode);
        double getFlightHours();
        void setFlightHours(double flightHours);
        void printInfo();
};

#endif /* coPilot_h */
