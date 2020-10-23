// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef plane_h
#define plane_h

#include <iostream>
using namespace std;

class Plane {
	private:
		string make;
		int model;
		string ID;
		int numSeats;
		int range; // range in miles
		int minCrew;
	public:
        Plane(string make, int model, string ID, int numSeats, int range, int minCrew); // parameterized constructor
        ~Plane(); // destructor
    
        string getMake();
		void setMake(string make);
		int getModel();
		void setModel(int model);
		string getID();
		void setID(string ID);
		int getNumSeats();
		void setNumSeats(int numSeats);
		int getRange();
		void setRange(int range);
		int getMinCrew();
		void setMinCrew(int minCrew);
		void printInfo();
};

#endif

