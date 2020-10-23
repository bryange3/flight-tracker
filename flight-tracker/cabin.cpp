// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include "cabin.h"
#include <iostream>
using namespace std;

Cabin::Cabin(string name, int ID, string status, string position)
    : CrewMember(name, ID, status)
{
    this->position = position;
}

Cabin::~Cabin() {
    
}

string Cabin::getType() {
    return "Cabin";
}

string Cabin::getPosition() {
    return position;
}

void Cabin::setPosition(string position) {
    this->position = position;
}

void Cabin::printInfo() {
    cout << endl << "CABIN CREW MEMBER INFO" << endl;
    cout << "Name: " << name << ", Crew member ID: " << ID << ", Status: " << status << ", Position: " << position << endl;
}
