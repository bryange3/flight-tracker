// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef crewMembers_h
#define crewMembers_h

#include <iostream>
#include <map>
#include "crewMember.h"
#include "pilot.h"
#include "coPilot.h"
#include "cabin.h"
using namespace std;

class CrewMembers {
    private:
        map<int, CrewMember*> crewMembers; // map<crewID, CrewMember*>
    public:
        CrewMember* newCrewMember(string name, int ID, string status, string type);
        bool emptyCrewMembersMap();
        CrewMember* findCrewMember(int crewID);
        void addCrewMember();
        void editCrewMember();
        void deleteCrewMember(int crewID);
        void searchCrewMember();
        void printAllCrewMembers();
        void printSingleCrewMember();
        int getCrewCount(string type);
        void storeCabin();
        void storePilot();
        void storeCoPilot();
        void store();
        void loadCabin();
        void loadPilot();
        void loadCoPilot();
        void load();
};

#endif /* crewMembers_h */
