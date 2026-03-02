#include "Output.h"
#include <iostream>

using namespace std; 

void Output::displayLongestRoute(const vector<vector<string>>& routes, 
                                 const vector<vector<string>>& costs,
                                 const vector<vector<string>>& connections) {

    // Check if routes are available
    if (routes.empty()) {
        cout << "No routes available.\n";
        return;
    }

    // Step 1: Find the longest route
    size_t longestIndex = 0;
    size_t maxLength = 0;
    for (size_t i = 0; i < routes.size(); i++) {
        if (routes[i].size() > maxLength) {
            maxLength = routes[i].size();
            longestIndex = i;
        }
    }

    // Extract the longest route
    vector<string> longestRoute = routes[longestIndex];

    // Step 2: Display the route
    cout << "\n=========== Longest Route ===========\n";
    cout << "Total Stops: " << longestRoute.size() << "\n";
    double totalCost = 0;
    double totalTime = 0;
    int totalDays = 0;

    // Step 3: Process each leg of the journey
    for (size_t i = 0; i < longestRoute.size(); i++) {
        string currentCity = longestRoute[i];
        if (i > 0) {
            string previousCity = longestRoute[i - 1];
            double travelTime = getTravelTime(previousCity, currentCity, connections);
            int roadStops = 0;

            // Check if travel exceeds daily limit
            if (travelTime > 8.0) {
                int extraDays = ceil(travelTime / 8.0);
                totalDays += (extraDays - 1);
                totalCost += (extraDays - 1) * 100; // Extra overnight stays
                roadStops = extraDays - 1;
            } 
            cout << "Travel from " << previousCity << " to " << currentCity
                << " - Time: " << travelTime << " hours, Cost: " << roadStops * 100 << endl;
            totalTime += travelTime;
        }
        totalDays++;

        // Retrieve accommodation cost dynamically
        double stayCost = getAccommodationCost(currentCity, costs);
        cout << "Stay in " << currentCity << " - Accommodation Cost: $" << stayCost << "\n";
        totalCost += stayCost;
    }

    totalDays--;
    cout << "Full Longest Route: ";
    for (int i = 0; i < longestRoute.size(); i++) {
        if (i != longestRoute.size() - 1) {
            cout << longestRoute[i] << " -> ";
        }
        else { cout << longestRoute[i]; }
    }

    // Step 4: Display total cost and time
    cout << "\n=========== Route Summary ===========\n";
    cout << "Total Travel Time: " << totalTime << " hours\n";
    cout << "Total Accommodation Cost: $" << totalCost << "\n";
    cout << "Total Days (rounded up): " << totalDays << " days\n";
    cout << "=====================================\n";
}

// Helper function to get accommodation cost from the costs vector
double Output::getAccommodationCost(const string& city, const vector<vector<string>>& costs) {
    for (const auto& costEntry : costs) {
        if (costEntry.size() == 2 && costEntry[0] == city) {
            return stod(costEntry[1]); // Convert cost from string to double
        }
    }
    return 0.0; // Default if city not found
}

// Helper function to get travel time between two cities from the connections vector
double Output::getTravelTime(const string& fromCity, const string& toCity, 
                             const vector<vector<string>>& connections) {
    for (const auto& connection : connections) {
        if (connection.size() == 3 && 
            ((connection[0] == fromCity && connection[1] == toCity))) {
            return stod(connection[2]); // Convert travel time from string to double
        }
    }
    return 0.0; // Default if no connection found
}