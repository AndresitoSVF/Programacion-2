#include <iostream>
#include <List.hpp>
#include <string>


using namespace std;


void readKValues(List<int>& kValues, int n) {
    int value;
    for (int i = 0; i < n; i++) {
        cin >> value;
        kValues.insertEnd(value);
    }
}

void readPeople(List<List<string> >& people) {
    int i = 0;
    string value;
    while (cin >> value) {
        if (people.getSize() <= i) {
            people.insertEnd(List<string>());
        }
        people[i].insertEnd(value);
        i++;

        while (cin.peek() == ' ') {
            cin.ignore();
        }

        if (cin.peek() == '\n') {
            i = 0;
        }
    }
}

string chooseWinner(int k, List<string>& people) {

    bool reverse = false;
    string winner = "";
    int current = 1;
    string person;

    while (people.getSize() > 1) {

        if (reverse) {
            person = people[people.getSize() - 1];
            people.removeEnd();
            if (k > current) {
                people.insertStart(person);
            } else {
                current = 0;
                reverse = !reverse;
            }
        } else {
            person = people[0];
            people.removeStart();
            if (k > current) {
                people.insertEnd(person);
            } else {
                current = 0;
                reverse = !reverse;
            }
        }

        ++current;
    }

    winner = people[0];

    return winner;
}

int main() {

    int testCases;
    List<int> kValues;
    List<List<string> > people;
    string winner;
    
    cin >> testCases; 
    readKValues(kValues, testCases);
    readPeople(people);

    for (int i = 0; i < testCases; i++) {
        winner = chooseWinner(kValues[i], people[i]);
        cout << winner << "\n";    
    }

    return 0;
}
