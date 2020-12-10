// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef cabin_h
#define cabin_h

#include <iostream>
#include "crewMember.h"
using namespace std;

class Cabin : public CrewMember {
    private:
        string position;
    public:
        Cabin(string name, int ID, string status, string position);
        ~Cabin();
    
        string getType();
        string getPosition();
        void setPosition(string position);
        void printInfo();
};

#endif /* cabin_h */
