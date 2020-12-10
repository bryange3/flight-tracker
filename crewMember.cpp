// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include "crewMember.h"
using namespace std;

CrewMember::CrewMember(string name, int ID, string status) {
    this->name = name;
    this->ID = ID;
    this->status = status;
}

CrewMember::~CrewMember() {
    
}

string CrewMember::getType() {
    return "CrewMember";
}

string CrewMember::getName() {
    return name;
}
void CrewMember::setName(string name) {
    this->name = name;
}

int CrewMember::getID() {
    return ID;
}

void CrewMember::setID(int ID) {
    this->ID = ID;
}

string CrewMember::getStatus() {
    return status;
}

void CrewMember::setStatus(string status) {
    this->status = status;
}

void CrewMember::printInfo() {
    cout << endl << "CREW MEMBER INFO" << endl;
    cout << "Name: " << name << ", Crew member ID: " << ID << ", Status: " << status << endl;
}

