//
//  main.cpp
//  Club Dues
//
//  Created by Caden Finley on 10/23/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include "p2set2.h"
#include "p2queue2.h"
using namespace std;
int main() {
    Set<string> pastYearMembers;
    Set<string> newYearMembers;
    Queue<string> pastYearQueue;
    Queue<string> newYearQueue;
    ifstream pastFile("8A_past.txt");
    if (pastFile.is_open()) {
        string line;
        while (getline(pastFile, line)) {
            if (line.find("Membership roll: ") == 0) {
                int n = stoi(line.substr(17));
                for (int i = 0; i < n; ++i) {
                    getline(pastFile, line);
                    pastYearMembers.insert(line);
                    pastYearQueue.push(line);
                }
            }
        }
        pastFile.close();
    }
    ifstream newFile("8A_new.txt");
    if (newFile.is_open()) {
        string line;
        while (getline(newFile, line)) {
            if (line.find("Membership roll: ") == 0) {
                int n = stoi(line.substr(17));
                for (int i = 0; i < n; ++i) {
                    getline(newFile, line);
                    newYearMembers.insert(line);
                    newYearQueue.push(line);
                }
            }
        }
        newFile.close();
    }
    Set<string> renewedMembers;
    Set<string> newMembers;
    string pastYearCheck;
    string newYearCheck;
    for (int i = 0; i < pastYearMembers.getSize(); i++) {
        pastYearCheck = pastYearQueue.pop();
        if (newYearMembers.contains(pastYearCheck)) {
            renewedMembers.insert(pastYearCheck);
        }
    }
    for (int i = 0; i < newYearMembers.getSize(); i++) {
        newYearCheck = newYearQueue.pop();
        if (!pastYearMembers.contains(newYearCheck)) {
            newMembers.insert(newYearCheck);
        }
    }
    int membershipFee = 80;
    int discount = 18;
    int oldMemberDues = renewedMembers.getSize() * (membershipFee - discount);
    int newMemberDues = newMembers.getSize() * membershipFee;
    int totalExpected = oldMemberDues + newMemberDues;
    int twoYearMembership = pastYearMembers.getSize() + newYearMembers.getSize() - renewedMembers.getSize();

    cout << "Old Member Dues: $" << oldMemberDues << endl;
    cout << "New Member Dues: $" << newMemberDues << endl;
    cout << "Total expected: $" << totalExpected << endl;
    cout << "Two-year membership: " << twoYearMembership << endl;
}

