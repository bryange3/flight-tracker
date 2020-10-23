// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include "plane.h"
using namespace std;

Plane::Plane(string make, int model, string ID, int numSeats, int range, int minCrew) {
    this->make = make;
    this->model = model;
    this->ID = ID;
    this->numSeats = numSeats;
    this->range = range;
    this->minCrew = minCrew;
}

Plane::~Plane() {
    
}

string Plane::getMake() {
    return make;
}

void Plane::setMake(string make) {
    this->make = make;
}

int Plane::getModel() {
    return model;
}

void Plane::setModel(int model) {
    this->model = model;
}

string Plane::getID() {
    return ID;
}

void Plane::setID(string ID) {
    this->ID = ID;
}

int Plane::getNumSeats() {
    return numSeats;
}
void Plane::setNumSeats(int numSeats) {
    this->numSeats = numSeats;
}

int Plane::getRange() {
    return range;
}

void Plane::setRange(int range) {
    this->range = range;
}

int Plane::getMinCrew() {
    return minCrew;
}

void Plane::setMinCrew(int minCrew) {
    this->minCrew = minCrew;
}

void Plane::printInfo() {
    cout << endl << "PLANE INFORMATION" << endl;
    cout << "Make: " << make << ", Model: " << model << ", Plane ID: " << ID << ", Number of seats: " << numSeats << ", Range (miles): " << range << ", Minimum number of cabin crew: " << minCrew << endl;
}

