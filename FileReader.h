#ifndef FILEREADER_H
#define FILEREADER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


using namespace std;


class FileReader {
private:
	int timeLimit;
	double budget;
	string startLocation;
	vector<vector<string>> connections;
	vector<vector<string>> cityCosts;


public:
	int getTimeLimit();
	double getBudget();
	string getStartLocation();
	vector<vector<string>> getConnections();
	vector<vector<string>> getCityCosts();
	void readFile(const string& filename);
	void printData() const;
	vector<string> splitAndTrim(const string& str, char delimiter);
	string trim(const string& str);
	bool isLetters(const string& str);
	bool isNumber(const string& str);
};


#endif // FILEREADER_H