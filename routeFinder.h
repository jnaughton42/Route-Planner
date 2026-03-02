#include <iostream>
#include <string>
#include <vector>

#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

using namespace std;

class routeFinder{
  public:
  vector<vector<string>> getConnections(){return connections;}
  vector<vector<double>> getTravelTime(){return travelTime;}
  vector<vector<string>> getRoutes() { return routes; }
  vector<vector<string>> getCosts(){return costs;}
  string getStartLoc(){return startLoc;}
  int getDays(){return days;}
  double getBudget(){return budget;}
  vector<string> getRoute1() { return route1; }
  void setStartLoc(string s){startLoc = s; return;}
  void setDays(int d){days = d; return;}
  void setBudget(double b){budget = b; return;}
  void organizeData(int, double, string, vector<vector<string>>, vector<vector<string>>);
  void findRoute(double, int, vector<string>, int routeLength = 1);
  int findIndex(string);
  bool inRoute(string, vector<string>);
  
  private:
  string startLoc;
  int days;
  double budget;
  vector<string> route1;
  vector<vector<string>> routes;
  vector<vector<string>> costs;
  vector<vector<string>> connections;
  vector<vector<double>> travelTime;
  
  void buildConnections(vector<vector<string>>);
};

#endif