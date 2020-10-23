// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include "pilot.h"
using namespace std;

Pilot::Pilot(string name, int ID, string status, string ratingCode, double flightHours)
    : CrewMember(name, ID, status)
{
    this->ratingCode = ratingCode;
    this->flightHours = flightHours;
}

Pilot::~Pilot() {
    
}

string Pilot::getType() {
    return "Pilot";
}

string Pilot::getRatingCode() {
    return ratingCode;
}

void Pilot::setRatingCode(string ratingCode) {
    this->ratingCode = ratingCode;
}

double Pilot::getFlightHours() {
    return flightHours;
}

void Pilot::setFlightHours(double flightHours) {
    this->flightHours = flightHours;
}

void Pilot::printInfo() {
    cout << endl << "PILOT INFO" << endl;
    cout << "Name: " << name << ", Crew member ID: " << ID << ", Status: " << status << ", Rating code: " << ratingCode << ", Flight hours: " << flightHours << endl;
}
