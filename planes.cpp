// Bryan Ge - bryange@my.unt.edu
// This is a flights scheduler and handler program designed to give the user all kinds of abilites in terms of handling various flights and the factors involved in flights including planes, crew members, etc.

#include <iostream>
#include <map>
#include <fstream>
#include <iterator>
#include "planes.h"
#include "plane.h"
using namespace std;

bool Planes::emptyPlanesMap() {
    return planes.empty();
}

Plane* Planes::findPlane(string planeID) {
    map<string,Plane*>::iterator it = planes.find(planeID);
    if(it != planes.end())
    {
        // element found
        return it->second;
    }
    return NULL;
}

void Planes::addPlane() {
        Plane* plane;
        string planeID;
        string make;
        int model;
        int numSeats;
        int range; // range in miles
        int minCrew;
        string choice;

        cout << "ADD PLANE" << endl;
        do {
                cout << "Enter plane ID/tail number: ";
                cin >> planeID;
                plane = findPlane(planeID);
                if (plane != NULL) { // plane exists
                        cout << "Plane already exists" << endl;
                        do {
                                cout << "Would you like to enter a different plane ID? (yes/no) ";
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
        } while (plane != NULL);
        cin.ignore();
        cout << "Enter make: "; getline(cin, make);
        cout << "Enter model: "; cin >> model;
        do { // prompt user for number of seats and check to make sure it is a reasonable number
            cout << "Enter number of seats: "; cin >> numSeats;
            if (numSeats < minNumSeats)
                cout << "Number of seats cannot be less than " << minNumSeats << endl;
            if (numSeats > maxNumSeats)
                cout << "Number of seats cannot be greater than " << maxNumSeats << endl;
        } while ((numSeats < minNumSeats) || (numSeats > maxNumSeats));
        do { // prompt user for range and check to make sure it is a reasonable number
            cout << "Enter range (miles): "; cin >> range;
            if (range < minRange)
                cout << "Range cannot be less than " << minRange << " miles" << endl;
            if (range > maxRange)
                cout << "Range cannot be greater than " << maxRange << " miles" << endl;
        } while ((range < minRange) || (range > maxRange));
        do { // prompt user for minimum number of crew and check to make sure it is a reasonable number
            cout << "Enter minimum number of crew: "; cin >> minCrew;
            if (minCrew < minNumCrew)
                cout << "Minimum number of crew cannot be less than " << minNumCrew << endl;
            if (minCrew > maxNumCrew)
                cout << "Minimum number of crew cannot be greater than " << maxNumCrew << endl;
        } while ((minCrew < minNumCrew) || (minCrew > maxNumCrew));
    planes[planeID] = new Plane(make, model, planeID, numSeats, range, minCrew); // add plane object to the map
}


void Planes::editPlane() { // TODO should be able to edit plane after flight
	int editOption;
    string choice = "yes";
	Plane* plane;
	string planeID;
	string make;
    int model;
    int numSeats;
    int range; // range in miles
    int minCrew;

    if (planes.empty())
    {
        cout << "No planes have been created, thus no planes can be edited" << endl;
        return;
    }
    
	do {
		cout << "Enter ID/tail number of the plane you want to edit: ";
		cin >> planeID;
		plane = findPlane(planeID);
		if (plane == NULL) {
			cout << "Plane not found" << endl;
			do {
				cout << "Would you like to enter a different plane ID? (yes/no) ";
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
    } while (plane == NULL);

	plane->printInfo();

	do {
       		cout << "0. Exit edit plane mode" << endl;
            cout << "1. Edit make" << endl;
            cout << "2. Edit model" << endl;
            cout << "3. Edit number of seats" << endl;
            cout << "4. Edit range" << endl;
            cout << "5. Edit minimum number of cabin crew" << endl;
        	cin >> editOption;

        if (editOption > 5)
            cout << "Enter an option between 0-5" << endl;
        
		switch(editOption)
		{
			case 0:
				break;
			case 1:
            {
                cin.ignore();
                cout << "Enter new make: "; getline(cin, make);
                plane->setMake(make);
				break;
            }
			case 2:
            {
				cout << "Enter new model: "; cin >> model;
                plane->setModel(model);
				break;
            }
			case 3:
            {
                do {
                    cout << "Enter new number of seats: "; cin >> numSeats;
                    if (numSeats < minNumSeats)
                        cout << "Number of seats cannot be less than " << minNumSeats << endl;
                    if (numSeats > maxNumSeats)
                        cout << "Number of seats cannot be greater than " << maxNumSeats << endl;
                } while ((numSeats < minNumSeats) || (numSeats > maxNumSeats));
                plane->setNumSeats(numSeats);
				break;
                
                // TODO validate the flights that the plane's being used on have enough seats for num of passengers
            }
			case 4:
            {
                do {
                    cout << "Enter new range (miles): "; cin >> range;
                    if (range < minRange)
                        cout << "Range cannot be less than " << minRange << " miles" << endl;
                    if (range > maxRange)
                        cout << "Range cannot be greater than " << maxRange << " miles" << endl;
                } while ((range < minRange) || (range > maxRange));
                plane->setRange(range);
                break;
            }
			case 5:
            {
                do {
                    cout << "Enter new minimum number of crew: "; cin >> minCrew;
                    if (minCrew < minNumCrew)
                        cout << "Minimum number of crew cannot be less than " << minNumCrew << endl;
                    if (minCrew > maxNumCrew)
                        cout << "Minimum number of crew cannot be greater than " << maxNumCrew << endl;
                } while ((minCrew < minNumCrew) || (minCrew > maxNumCrew));
                plane->setMinCrew(minCrew);
                break;
                // TODO validate with flights
            }
            default:
                break;
		}
    } while (editOption != 0);
}

void Planes::deletePlane(string planeID) {
    // TODO check if plane is used by any flights
    
    Plane* plane = findPlane(planeID);
    if (plane != NULL)
    {
        delete plane; // deletes the plane object
        planes.erase(planeID); // deletes the map entry
    }
}

void Planes::searchPlane() {
    Plane* plane;
    string planeID;
    
    cout << "Enter plane ID of the plane you want to check exists or not: ";
    cin >> planeID;
    plane = findPlane(planeID);
    if (plane != NULL)
    {
        cout << "Plane with plane ID " << planeID << " exists" << endl;
        // TODO should I give the user more info about the existing plane such as the flight the plane may be currently used for
    }
    else
    {
        cout << "Plane with plane ID " << planeID << " does not exist" << endl;
    }
}

void Planes::printAllPlanes() {
    if (planes.empty())
    {
        cout << "No planes have been created" << endl;
        return;
    }
    
    map<string, Plane*>::iterator it;
    
    cout << "Information for All Planes" << endl;
    for (it = planes.begin(); it != planes.end(); it++)
        ((*it).second)->printInfo();
}

void Planes::printSinglePlane() {
    string planeID;

    if (planes.empty())
    {
        cout << "No planes have been created" << endl;
        return;
    }
    
    do {
        cout << "Enter the plane ID of the plane you would like details for: ";
        cin >> planeID;
        if (findPlane(planeID) == NULL)
            cout << "Plane associated with that plane ID could not be found" << endl;
    } while (findPlane(planeID) == NULL);
    planes.at(planeID)->printInfo();
}

void Planes::store() {
    ofstream fout;
    fout.open("planes.dat");
    Plane* plane;
    map<string, Plane*>::iterator it;
    
    fout << planes.size() << endl; // number of existing planes
    for (it = planes.begin(); it != planes.end(); it++)
    {
        plane = ((*it).second);
        fout << plane->getMake() << endl;
        fout << plane->getModel() << endl;
        fout << plane->getID() << endl;
        fout << plane->getNumSeats() << endl;
        fout << plane->getRange() << endl;
        fout << plane->getMinCrew() << endl;
    }
    fout.close();
}

void Planes::load() {
    ifstream fin;
    int numPlanes;
    fin.open("planes.dat");
    string make;
    int model;
    string ID;
    int numSeats;
    int range; // range in miles
    int minCrew;
    
    fin >> numPlanes;
    for (int i = 0; i < numPlanes; i++)
    {
        fin.ignore();
        getline(fin, make);
        fin >> model;
        fin >> ID;
        fin >> numSeats;
        fin >> range;
        fin >> minCrew;
        planes[ID] = new Plane(make, model, ID, numSeats, range, minCrew); // add plane object to the map
    }
    fin.close();
}

