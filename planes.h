// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#ifndef planes_h
#define planes_h

#include <iostream>
#include <map>
#include <vector>
#include "plane.h"
using namespace std;

class Planes {
	private:
		map<string, Plane*> planes; // map<planeID, Plane*>
    
	public:
        // limits to prevent user from entering unrealistic values for respective plane attributes
        static const int minNumSeats = 10;
        static const int maxNumSeats = 400;
        static const int minRange = 100;
        static const int maxRange = 10000;
        static const int minNumCrew = 2;
        static const int maxNumCrew = 12;
    
        bool emptyPlanesMap(); // returns true if the planes map is empty
        Plane* findPlane(string planeID);
		void addPlane();
		void editPlane();
        void deletePlane(string planeID);
        void searchPlane();
        void printAllPlanes();
        void printSinglePlane();
        void store();
        void load();
};

#endif

