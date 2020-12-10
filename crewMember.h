// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef crewMember_h
#define crewMember_h

#include <iostream>
#include <vector>
#include "flight.h"
using namespace std;

class CrewMember {
    protected:
        string name;
        int ID;
        string status;
        vector<Flight*> flights;
    public:
        CrewMember(string name, int ID, string status); // parameterized constructor
        ~CrewMember(); // destructor
    
        virtual string getType();
        string getName();
        void setName(string name);
        int getID();
        void setID(int ID);
        string getStatus();
        void setStatus(string status);
        virtual void printInfo();
};

#endif /* crewMember_h */

