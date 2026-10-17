//Lab 24|COMSC 210|Ismael Hadi
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string names[], string colors[]);
void display_trip(list<Goat> trip);

int main_menu() {
    int choice = 0;
    //Engine loop
    while (true) {
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << "[1] Add a goat" << endl << "[2] Delete a goat" << endl << "[3] List goats" << endl << "[4] Quit" << endl;
        cout << "Choice --> ";
        cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
            return choice;
        }
        else {
            cout << "Choice must be an integer between 1 and 4, try again" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
};

int main() {
    srand(time(0));
    bool again;
    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();
    
    list<Goat> myList;

    int choice = 0;
    while (choice != 4) {
        choice = main_menu();
        if (choice == 1) {
            add_goat(myList, names, colors);
        }
        if (choice == 2) {
            delete_goat(myList);
        }
        if (choice == 3) {
            display_trip(myList);
        }
    }



    return 0;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    int age = rand() % (MAX_AGE + 1);
    int idxcolor  = rand() % SZ_COLORS;
    int idxname = rand() % SZ_NAMES;
    Goat temp;
    temp.set_age(age);
    temp.set_color(colors[idxcolor]);
    temp.set_name(names[idxname]);
    trip.push_back(temp);
}

void display_trip(list<Goat> trip) {
    int i = 1;
    for (Goat g : trip) {
        cout << "[" << i++ << "] " << g.get_name() << " (" << g.get_age() << ", " <<  g.get_color() <<")" << endl;
    }
    cout << endl;
}

int select_goat(list<Goat> trip) {
    int choice = 0;
    cout << "Current list of goats: " << endl;
    display_trip(trip);
    cout << "Select a goat by entering its index, then press enter: ";
    cin >> choice;
    return choice;
}

void delete_goat(list<Goat> &trip) {
   if (trip.empty()) {
    cout << "Empty list, no goats to delete" << endl;
    return;
   }
   int choice = select_goat(trip);
   int i = 1;
   auto it = trip.begin();
   for (Goat g : trip) {
    if (i == choice) {
        break;
    }
    i++;
    it++;
   }
   trip.erase(it);
}