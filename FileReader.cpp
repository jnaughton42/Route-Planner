#include "FileReader.h"


int FileReader::getTimeLimit() { return timeLimit; }
double FileReader::getBudget() { return budget; }
string FileReader::getStartLocation() { return startLocation; }
vector<vector<string>> FileReader::getConnections() { return connections; }
vector<vector<string>> FileReader::getCityCosts() { return cityCosts; }

// Stores city-to-city connections
void FileReader::readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    bool firstLine = true; // To handle the first line separately

    while (getline(file, line)) {
        vector<string> tokens = splitAndTrim(line, ',');

        // Handle first line (Time Limit, Budget, Starting Location)
        if (firstLine) {
            if (tokens.size() == 3 && isNumber(tokens[0]) && isNumber(tokens[1]) && isLetters(tokens[2])) {
                timeLimit = stoi(tokens[0]);
                budget = stod(tokens[1]);
                startLocation = tokens[2];
            }
            else {
                cerr << "Invalid first line format!" << endl;
                return;
            }
            firstLine = false;
            continue;
        }

        // If the line contains two values -> City and Cost of Stay
        if (tokens.size() == 2 && isLetters(tokens[0]) && isNumber(tokens[1])) {
            cityCosts.emplace_back(tokens);
        }
        // If the line contains three values -> City-to-City Connection
        else if (tokens.size() == 3) {
            string cityA, cityB, travelTime;

            // Identify which tokens are cities and which one is a number
            if (isNumber(tokens[0]) && isLetters(tokens[1]) && isLetters(tokens[2])) {
                travelTime = tokens[0];
                cityA = tokens[1];
                cityB = tokens[2];
            }
            else if (isLetters(tokens[0]) && isNumber(tokens[1]) && isLetters(tokens[2])) {
                cityA = tokens[0];
                travelTime = tokens[1];
                cityB = tokens[2];
            }
            else if (isLetters(tokens[0]) && isLetters(tokens[1]) && isNumber(tokens[2])) {
                cityA = tokens[0];
                cityB = tokens[1];
                travelTime = tokens[2];
            }
            else {
                continue; // Skip invalid lines
            }
            connections.push_back({ cityA, cityB, travelTime });
        }
    }
    file.close();
}

// Function to display the extracted data
void FileReader::printData() const {
    cout << "Starting Location: " << startLocation << endl;
    cout << "Budget: $" << budget << endl;
    cout << "Time Limit: " << timeLimit << " days" << endl;

    cout << "\nCity Costs (Per Night):\n";
    for (const auto& cityCost : cityCosts) {
        cout << cityCost[0] << ": $" << cityCost[1] << endl;
    }

    cout << "\nConnections extracted from file:\n";
    for (const auto& conn : connections) {
        cout << "{" << conn[0] << ", " << conn[1] << ", " << conn[2] << "}\n";
    }
}

// Helper function to split a string by a delimiter and trim spaces
vector<string> FileReader::splitAndTrim(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token)); // Trim spaces before storing
    }
    return tokens;
}

// Function to trim leading and trailing spaces from a string
string FileReader::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to check if a string contains only letters
bool FileReader::isLetters(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) return false;
    }
    return true;
}

// Function to check if a string is a valid number (allows decimals)
bool FileReader::isNumber(const string& str) {
    bool hasDecimal = false;
    for (char c : str) {
        if (!isdigit(c)) {
            if (c == '.' && !hasDecimal) { // Allow only one decimal point
                hasDecimal = true;
            }
            else {
                return false;
            }
        }
    }
    return true;
}