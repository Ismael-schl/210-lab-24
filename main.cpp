//Lab 24|COMSC 210|Ismael Hadi
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string names[], string colors[]);
void display_trip(set<Goat> trip);

int main_menu() {
    int choice = 0;
    //Engine loop
    while (true) {
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << "[1] Add a goat" << endl << "[2] Delete a goat" << endl << "[3] Display set of goats" << endl << "[4] Quit" << endl;
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
    
    set<Goat> mySet;

    int choice = 0;
    while (choice != 4) {
        choice = main_menu();
        if (choice == 1) {
            add_goat(mySet, names, colors);
        }
        if (choice == 2) {
            delete_goat(mySet);
        }
        if (choice == 3) {
            display_trip(mySet);
        }
    }



    return 0;
}

//This function adds a goat to the set and assigns random names and colors to these goats
void add_goat(set<Goat> &trip, string names[], string colors[]) {
    int age = rand() % (MAX_AGE + 1);
    int idxcolor  = rand() % SZ_COLORS;
    int idxname = rand() % SZ_NAMES;
    Goat temp;
    temp.set_age(age);
    temp.set_color(colors[idxcolor]);
    temp.set_name(names[idxname]);
    trip.insert(temp);
}

//This function displays the current goats on the trip in a neat format
void display_trip(set<Goat> trip) {
    int i = 1;
    for (Goat g : trip) {
        cout << "[" << i++ << "] " << g.get_name() << " (" << g.get_age() << ", " <<  g.get_color() <<")" << endl;
    }
    cout << endl;
}

//This function allows the user to select a goat from the set after displaying it
int select_goat(set<Goat> trip) {
    int choice = 0;
    cout << "Current set of goats: " << endl;
    display_trip(trip);
    cout << "Select a goat by entering its index, then press enter: ";
    cin >> choice;
    return choice;
}

//This function allows the user to delete a goat from the set after displaying it. It considers the empty set case as well
void delete_goat(set<Goat> &trip) {
   if (trip.empty()) {
    cout << "Empty set, no goats to delete" << endl;
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