// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <typeinfo>
#include "crewMembers.h"
#include "crewMember.h"
#include "pilot.h"
#include "coPilot.h"
#include "cabin.h"
using namespace std;

bool CrewMembers::emptyCrewMembersMap() {
    return crewMembers.empty();
}

CrewMember* CrewMembers::findCrewMember(int crewID) {
    map<int,CrewMember*>::iterator it = crewMembers.find(crewID);
    if(it != crewMembers.end())
    {
        // element found
        return it->second;
    }
    return NULL;
}

CrewMember* CrewMembers::newCrewMember(string name, int ID, string status, string type) {
    string ratingCode;
    double flightHours;
    string position;
    
    if (type == "pilot")
    {
        do {
            cout << "Enter 5 character rating code: ";
            cin >> ratingCode;
            if (ratingCode.size() != 5)
                cout << "Rating code must be 5 characters" << endl;
        } while (ratingCode.size() != 5);
        
        cout << "Enter cumulative flight hours: ";
        cin >> flightHours;
        
        return new Pilot(name, ID, status, ratingCode, flightHours);
    }
    else if (type == "copilot")
    {
        do {
            cout << "Enter 4 character rating code: ";
            cin >> ratingCode;
            if (ratingCode.size() != 4)
                cout << "Rating code must be 4 characters" << endl;
        } while (ratingCode.size() != 4);
        
        cout << "Enter cumulative flight hours: ";
        cin >> flightHours;
        
        return new CoPilot(name, ID, status, ratingCode, flightHours);
    }
    else
    {
        cin.ignore();
        do {
            cout << "Enter cabin member position (First Class, Business Class, Economy Front, Economy Rear, Lead): ";
            getline(cin, position);
            if ((position != "First Class") && (position != "Business Class") && (position != "Economy Front") && (position != "Economy Rear") && (position != "Lead"))
                cout << "Please enter a valid position" << endl;
        } while ((position != "First Class") && (position != "Business Class") && (position != "Economy Front") && (position != "Economy Rear") && (position != "Lead"));
        return new Cabin(name, ID, status, position);
    }
}

void CrewMembers::addCrewMember() {
    CrewMember* crewMember;
    string name;
    int crewID;
    string type;
    string choice;
    string status;
    
    cout << "ADD CREW MEMBER" << endl;
    do {
        cout << "Enter crew member ID: ";
        cin >> crewID;
        crewMember = findCrewMember(crewID);
        if (crewMember != NULL) {
            cout << "Crew member already exists" << endl;
            do {
                cout << "Would you like to enter a different crew member ID? (yes/no) ";
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
    } while (crewMember != NULL);
    
    cin.ignore();
    cout << "Enter name of the crew member: ";
    getline(cin, name);
    
    do {
         // TODO CORRECT???
        cout << "Enter crew member status (available, on leave, sick)";
        getline(cin, status);
        if ((status != "available") && (status != "on leave") && (status != "sick"))
            cout << "Please enter a valid status" << endl;
    } while ((status != "available") && (status != "on leave") && (status != "sick"));
    
    do {
        cout << "Enter crew member type (pilot, copilot, cabin): ";
        cin >> type;
        if ((type != "pilot") && (type != "copilot") && (type != "cabin"))
            cout << "Please enter 'pilot', 'copilot', or 'cabin'" << endl;
    } while ((type != "pilot") && (type != "copilot") && (type != "cabin"));
    
    crewMembers[crewID] = newCrewMember(name, crewID, status, type); // add CrewMember object to the map
}


void CrewMembers::editCrewMember() {
    int editOption;
    string choice;
    CrewMember* crewMember;
    string name;
    int crewID;
    string status;
    string ratingCode;
    string position;
    double flightHours;
    
    if (crewMembers.empty())
    {
        cout << "No crew members have been created, thus no crew members can be edited" << endl;
        return;
    }
    
    do {
        cout << "Enter crew member ID of crew member you want to edit: ";
        cin >> crewID;
        crewMember = findCrewMember(crewID);
        if (crewMember == NULL) {
            cout << "Crew member not found" << endl;
            do {
                cout << "Would you like to enter a different crew member ID? (yes/no) ";
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
    } while (crewMember == NULL);
    
    crewMember->printInfo();
    
    // initialize temporary variables
    name = crewMember->getName();
    
    if (crewMember->getType() == "Pilot")
    { // TODO COMPLETE FOR OTHER CREW MEMBERS
        do {
            cout << "0. Exit edit crew member mode" << endl;
            cout << "1. Edit name" << endl;
            cout << "2. Edit status" << endl;
            cout << "3. Edit 5 character rating code" << endl;
            cout << "4. Edit flight hours" << endl;
            cin >> editOption;
            
            if (editOption > 4)
                cout << "Enter an option between 0-4" << endl;
            
            switch(editOption)
            {
                case 0:
                    break;
                case 1:
                {
                    cin.ignore();
                    cout << "Enter new crew member name: ";
                    getline(cin, name);
                    crewMember->setName(name);
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    do {
                        cout << "Enter new crew member status (available, on leave, sick)";
                        getline(cin, status);
                        if ((status != "available") && (status != "on leave") && (status != "sick"))
                            cout << "Please enter a valid status" << endl;
                    } while ((status != "available") && (status != "on leave") && (status != "sick"));
                    crewMember->setStatus(status);
                    break;
                }
                case 3:
                {
                    do {
                        cout << "Enter new 5 character rating code: ";
                        cin >> ratingCode;
                        if (ratingCode.size() != 5)
                            cout << "Rating code must be 5 characters" << endl;
                    } while (ratingCode.size() != 5);
                    ((Pilot*)crewMember)->setRatingCode(ratingCode);
                }
                case 4:
                {
                    cout << "Enter cumulative flight hours: ";
                    cin >> flightHours;
                    ((Pilot*)crewMember)->setFlightHours(flightHours);
                }
                default:
                    break;
            }
        } while (editOption != 0);
    }
    else if (crewMember->getType() == "CoPilot")
    {
        do {
            cout << "0. Exit edit crew member mode" << endl;
            cout << "1. Edit name" << endl;
            cout << "2. Edit status" << endl;
            cout << "3. Edit 4 character rating code" << endl;
            cout << "4. Edit flight hours" << endl;
            cin >> editOption;
            
            if (editOption > 4)
                cout << "Enter an option between 0-4" << endl;
            
            switch(editOption)
            {
                case 0:
                    break;
                case 1:
                {
                    cin.ignore();
                    cout << "Enter new crew member name: ";
                    getline(cin, name);
                    crewMember->setName(name);
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    do {
                        cout << "Enter new crew member status (available, on leave, sick)";
                        getline(cin, status);
                        if ((status != "available") && (status != "on leave") && (status != "sick"))
                            cout << "Please enter a valid status" << endl;
                    } while ((status != "available") && (status != "on leave") && (status != "sick"));
                    crewMember->setStatus(status);
                    break;
                }
                case 3:
                {
                    do {
                        cout << "Enter new 4 character rating code: ";
                        cin >> ratingCode;
                        if (ratingCode.size() != 4)
                            cout << "Rating code must be 4 characters" << endl;
                    } while (ratingCode.size() != 4);
                    ((CoPilot*)crewMember)->setRatingCode(ratingCode);
                }
                case 4:
                {
                    cout << "Enter cumulative flight hours: ";
                    cin >> flightHours;
                    ((CoPilot*)crewMember)->setFlightHours(flightHours);
                }
                default:
                    break;
            }
        } while (editOption != 0);
    }
    else {
        do {
            cout << "0. Exit edit crew member mode" << endl;
            cout << "1. Edit name" << endl;
            cout << "2. Edit status" << endl;
            cout << "3. Edit position" << endl;
            cin >> editOption;
            
            if (editOption > 3)
                cout << "Enter an option between 0-3" << endl;
            
            switch(editOption)
            {
                case 0:
                    break;
                case 1:
                {
                    cin.ignore();
                    cout << "Enter new crew member name: ";
                    getline(cin, name);
                    crewMember->setName(name);
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    do {
                        cout << "Enter new crew member status (available, on leave, sick)";
                        getline(cin, status);
                        if ((status != "available") && (status != "on leave") && (status != "sick"))
                            cout << "Please enter a valid status" << endl;
                    } while ((status != "available") && (status != "on leave") && (status != "sick"));
                    crewMember->setStatus(status);
                    break;
                }
                case 3:
                {
                    cin.ignore();
                    do {
                        cout << "Enter new cabin member position (First Class, Business Class, Economy Front, Economy Rear, Lead): ";
                        getline(cin, position);
                        if ((position != "First Class") && (position != "Business Class") && (position != "Economy Front") && (position != "Economy Rear") && (position != "Lead"))
                            cout << "Please enter a valid position" << endl;
                    } while ((position != "First Class") && (position != "Business Class") && (position != "Economy Front") && (position != "Economy Rear") && (position != "Lead"));
                    ((Cabin*)crewMember)->setPosition(position);
                }
                default:
                    break;
            }
        } while (editOption != 0);
    }
}

void CrewMembers::deleteCrewMember(int crewID) {
    // TODO if crew member is in any flights, cannot be deleted
    
    CrewMember* crewMember = findCrewMember(crewID);
    if (crewMember != NULL)
    {
        delete crewMember; // deletes the crew member object
        crewMembers.erase(crewID); // deletes the map entry
    }
}

void CrewMembers::searchCrewMember() {
    CrewMember* crewMember;
    int crewID;
    
    cout << "Enter crew member ID of the crew member you want to check exists or not: ";
    cin >> crewID;
    crewMember = findCrewMember(crewID);
    if (crewMember != NULL)
    {
        cout << "Crew member with crew ID " << crewID << " exists" << endl;
        // TODO should I give the user more info about the existing crew member such as what flight the crew member may currently be on
    }
    else
    {
        cout << "Crew member with crew ID " << crewID << " does not exist" << endl;
    }
}

void CrewMembers::printAllCrewMembers() {
    map<int, CrewMember*>::iterator it;
    
    if (crewMembers.empty())
    {
        cout << "No crew members have been created" << endl;
        return;
    }
    
    cout << "Information for All Crew Members" << endl;
    for (it = crewMembers.begin(); it != crewMembers.end(); it++)
        ((*it).second)->printInfo();
}

void CrewMembers::printSingleCrewMember() {
    int crewID;
    
    if (crewMembers.empty())
    {
        cout << "No crew members have been created" << endl;
        return;
    }
    
    do {
        cout << "Enter the crew member ID of the crew member you would like details for: ";
        cin >> crewID;
        if (findCrewMember(crewID) == NULL)
            cout << "Crew member associated with that crew member ID could not be found" << endl;
    } while (findCrewMember(crewID) == NULL);
    findCrewMember(crewID)->printInfo();
}

int CrewMembers::getCrewCount(string type) {
    CrewMember* crewMember;
    map<int, CrewMember*>::iterator it;
    int count = 0;
    for (it = crewMembers.begin(); it != crewMembers.end(); it++)
    {
        crewMember = ((*it).second);
        if (crewMember->getType() == type)
        {
            count++;
        }
    }
    return count;
}

void CrewMembers::storeCabin() {
    ofstream fout;
    fout.open("cabin.dat");
    CrewMember* crewMember;
    map<int, CrewMember*>::iterator it;
    
    fout << getCrewCount("Cabin") << endl;
    for (it = crewMembers.begin(); it != crewMembers.end(); it++)
    {
        crewMember = ((*it).second);
        if (crewMember->getType() == "Cabin")
        {
            fout << crewMember->getID() << endl;
            fout << crewMember->getName() << endl;
            fout << crewMember->getStatus() << endl;
            fout << ((Cabin*)crewMember)->getPosition() << endl;
        }
    }
    fout.close();
}

void CrewMembers::storePilot() {
    ofstream fout;
    fout.open("pilot.dat");
    CrewMember* crewMember;
    map<int, CrewMember*>::iterator it;
    
    fout << getCrewCount("Pilot") << endl;
    for (it = crewMembers.begin(); it != crewMembers.end(); it++)
    {
        crewMember = ((*it).second);
        if (crewMember->getType() == "Pilot")
        {
            fout << crewMember->getID() << endl;
            fout << crewMember->getName() << endl;
            fout << crewMember->getStatus() << endl;
            fout << ((Pilot*)crewMember)->getRatingCode() << endl;
            fout << ((Pilot*)crewMember)->getFlightHours() << endl;
        }
    }
    fout.close();
}

void CrewMembers::storeCoPilot() {
    ofstream fout;
    fout.open("copilot.dat");
    CrewMember* crewMember;
    map<int, CrewMember*>::iterator it;
    
    fout << getCrewCount("CoPilot") << endl;
    for (it = crewMembers.begin(); it != crewMembers.end(); it++)
    {
        crewMember = ((*it).second);
        if (crewMember->getType() == "CoPilot")
        {
            fout << crewMember->getID() << endl;
            fout << crewMember->getName() << endl;
            fout << crewMember->getStatus() << endl;
            fout << ((CoPilot*)crewMember)->getRatingCode() << endl;
            fout << ((CoPilot*)crewMember)->getFlightHours() << endl;
        }
    }
    fout.close();
}

void CrewMembers::store() {
    storePilot();
    storeCoPilot();
    storeCabin();
}

void CrewMembers::loadCabin() {
    ifstream fin;
    int numCrew;
    fin.open("cabin.dat");
    string name;
    int ID;
    string status;
    string position;
    vector<Flight*> flights;
    
    fin >> numCrew;
    for (int i = 0; i < numCrew; i++)
    {
        fin >> ID;
        fin.ignore();
        getline(fin, name);
        fin >> status;
        fin.ignore();
        getline(fin, position);
        crewMembers[ID] = new Cabin(name, ID, status, position);
    }
    fin.close();
}

void CrewMembers::loadPilot() {
    ifstream fin;
    int numCrew;
    fin.open("pilot.dat");
    string name;
    int ID;
    string status;
    string ratingCode;
    double flightHours;
    vector<Flight*> flights;
    
    fin >> numCrew;
    for (int i = 0; i < numCrew; i++)
    {
        fin >> ID;
        fin.ignore();
        getline(fin, name);
        fin >> status;
        fin >> ratingCode;
        fin >> flightHours;
        crewMembers[ID] = new Pilot(name, ID, status, ratingCode, flightHours);
    }
    fin.close();
}

void CrewMembers::loadCoPilot() {
    ifstream fin;
    int numCrew;
    fin.open("copilot.dat");
    string name;
    int ID;
    string status;
    string ratingCode;
    double flightHours;
    vector<Flight*> flights;
    
    fin >> numCrew;
    for (int i = 0; i < numCrew; i++)
    {
        fin >> ID;
        fin.ignore();
        getline(fin, name);
        fin >> status;
        fin >> ratingCode;
        fin >> flightHours;
        crewMembers[ID] = new CoPilot(name, ID, status, ratingCode, flightHours);
    }
    fin.close();
}

void CrewMembers::load() {
    loadCabin();
    loadPilot();
    loadCoPilot();
}
