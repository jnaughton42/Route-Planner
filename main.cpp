#include <iostream>
#include <vector>
#include <string>
#include "routeFinder.h"
#include "Output.h"
#include "FileReader.h"

using namespace std;

int main()
{
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    FileReader input;
    input.readFile(fileName);
    input.printData();
    routeFinder route;
    route.organizeData(input.getTimeLimit(), input.getBudget(), input.getStartLocation(), input.getCityCosts(), input.getConnections());
    route.findRoute(route.getBudget(), route.getDays(), route.getRoute1());
    Output out;
    out.displayLongestRoute(route.getRoutes(), input.getCityCosts(), input.getConnections());

    return 0;
}