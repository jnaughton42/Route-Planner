#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath> // For rounding up days

using namespace std;

class Output {
public:
    void displayLongestRoute(const vector<vector<string>>& routes, 
                             const vector<vector<string>>& costs,
                             const vector<vector<string>>& connections);
private:
    double getAccommodationCost(const string& city, const vector<vector<string>>& costs);
    double getTravelTime(const string& fromCity, const string& toCity, 
                         const vector<vector<string>>& connections);
};
#endif