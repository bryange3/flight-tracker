// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include "coPilot.h"
using namespace std;

CoPilot::CoPilot(string name, int ID, string status, string ratingCode, double flightHours)
    : CrewMember(name, ID, status)
{
    this->ratingCode = ratingCode;
    this->flightHours = flightHours;
}

CoPilot::~CoPilot() {
    
}

string CoPilot::getType() {
    return "CoPilot";
}

string CoPilot::getRatingCode() {
    return ratingCode;
}

void CoPilot::setRatingCode(string ratingCode) {
    this->ratingCode = ratingCode;
}

double CoPilot::getFlightHours() {
    return flightHours;
}

void CoPilot::setFlightHours(double flightHours) {
    this->flightHours = flightHours;
}

void CoPilot::printInfo() {
    cout << endl << "COPILOT INFO" << endl;
    cout << "Name: " << name << ", Crew member ID: " << ID << ", Status: " << status << ", Rating code: " << ratingCode << ", Flight hours: " << flightHours << endl;
}
