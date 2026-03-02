#include <iostream>
#include <string>
#include <vector>
#include "routeFinder.h"

using namespace std;

class routeFinder;

//Takes data from the fileReader class, populates parallel values in this class and builds any new structure needed given existing data
void routeFinder::organizeData(int d, double b, string s, vector<vector<string>> cost, vector<vector<string>> connection){
    setStartLoc(s);
    setDays(d);
    setBudget(b);
    //initializes the the route1 vector for storing individual viable routes with the starting city
    route1.emplace_back(getStartLoc()); 
    for (int i = 0; i < cost.size(); i++){
        costs.push_back({cost[i][0], cost[i][1]});
    }
    //calls a function to build data from connections vector
    buildConnections(connection); 
    return;
}

//Takes connections vector and puts its data into two seperate parallel vectors of connections and corrosponding travel times
void routeFinder::buildConnections(vector<vector<string>> connection){
    //Preemptively creates new rows for new data
    connections.push_back({});
    travelTime.push_back({}); 
    //Populates 0th vector with cities connected to start location and corrosponding travel times
    for (int i = 0; i < connection.size(); i++){ 
        if (connection[i][0] == startLoc){
            connections[0].emplace_back(connection[i][1]);
            travelTime[0].emplace_back(stod(connection[i][2]));
        }
    }
    //Does the same for remaining cities, using the order they exist in the costs vector
    for (int i = 0; i < costs.size(); i++){ 
        connections.push_back({});
        travelTime.push_back({});
        for (int j = 0; j < connection.size(); j++){
            if (connection[j][0] == costs[i][0]){
                connections[i + 1].emplace_back(connection[j][1]);
                travelTime[i + 1].emplace_back(stod(connection[j][2]));
            }
        }
    }
    return;
}

//Slightly modified version of Dr. Figueroa's recursive algorithm for pathfinding using the data structures unique to this implementation
void routeFinder::findRoute(double remainingBudget, int remainingDays, vector<string> route, int routeLength){
    int fromIndex = findIndex(route[routeLength - 1]);
    if (fromIndex == -1) { return; }
    bool addedToRoute = false;
    //Due to using the vector type, storing data such as number of connections is no longer necessary
    for (int i = 0; i < connections[fromIndex].size(); i++){ 
        string to = connections[fromIndex][i];
        int toIndex = findIndex(to);
        if (toIndex == -1) { return; }
        //Ignores connection if it goes back to the starting city
        if (toIndex == 0) { continue; } 
        int extraDays = travelTime[fromIndex][i] / 8;
        int days = remainingDays - extraDays;
        double budget = remainingBudget - stod(costs[toIndex - 1][1]) - extraDays * 100;
        if (travelTime[fromIndex][i] > extraDays * 8) {
            days--;
        }
        else { budget += 100; }
        if (budget >= 0 && days >= 0 && inRoute(to, route) == false) {
            //routeTemp ensures original route up until this point is preserved for when the recursive call returns to this stack frame
            vector<string> routeTemp = route; 
            routeTemp.emplace_back(to);
            int routeLengthTemp = routeLength;
            routeLengthTemp++;
            findRoute(budget, days, routeTemp, routeLengthTemp);
            addedToRoute = true;
        }
    }
    if (!addedToRoute && routeLength > 1) {
        //Outputs all routes that exhaust the given resources as they are all candidates for the longest route
        cout << "Route " << routes.size() + 1 << ": "; 
        for (int i = 0; i < route.size(); i++) {
            cout << route[i] << " ";
        }
        cout << endl;
        //Adds valid routes to the routes vector to send to the Output class
        routes.push_back(route); 
    }
    return;
}    
 
//Finds the index of a city in the costs vector as it is the standard of organization
int routeFinder::findIndex(string name){ 
    for (int i = 0; i < costs.size(); i++){
        if (name == costs[i][0]){return i + 1;}
        if (name == startLoc) { return 0; }
    }
    cout << "Error, city " << name << " does not have cost data in file\n\n";
    return -1;
}

//Checks whether city is already in existing route
bool routeFinder::inRoute(string name, vector<string> route){ 
    for (int i = 0; i < route.size(); i++){
        if (name == route[i]){
            return true;
        }
    }
    return false;
}