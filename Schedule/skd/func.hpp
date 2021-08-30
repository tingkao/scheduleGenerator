#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>
#include <filesystem> //edu: avaliable in C++ 17 version

using namespace std;
using namespace std::filesystem;

struct timeTable {
	string name;
	unsigned type = 5;
	unsigned startTime = 0;
	unsigned endTime = 0;
	unsigned courseNum = 0;
	bool hasOldHtml = false;
	bool hasFileName = false;
	bool isDone = false;
	string vecKey;
	vector<string> days {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
	vector<string> dayStr{ "M","T","W","H","F","S","U" };
	set<string> courseData;
	vector<pair<string, string>> coursesSectionVec;
};

string cssGenerator();
string JsGenerator();
string timeColGenerator(unsigned start, unsigned end);
string columnGenerator(unsigned index, timeTable const& table);
string scheduleData(timeTable const& table);

void courseSectionGenerator(timeTable& table);
void fillScheduleSection(timeTable& table);
void htmlGenerator(ofstream& outFile, timeTable const& table);

void output(timeTable const& table);
void outputLayout(timeTable const& table);

void readDataFromOldFile(timeTable& table, ifstream& inFile);
void skdSettingFromUser(timeTable& table);
void renameCourse(timeTable& table, string oriName, string newName);