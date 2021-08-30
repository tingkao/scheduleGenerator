/*
File Name: skd.cpp
Purpose:   To generate a customized schedule
Coder:     Yu-Ting Kao
Date:      2021-08-21
*/

#include "func.hpp"
#include <map>
#include <deque>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    timeTable table;
    ifstream inFile("schedule.html");
    if (!inFile) {
        cout << "You do not have a schedule just yet. Let's create a new one!\n\n";
    }
    else {
        cout << "There is schedule.html. You want to adjust data from this file? " <<endl;
        cout << "[N]-Let's create a new one!" << endl;
        cout << "[Y]-Read the old data!" << endl;
        char task;
        cin >> task;
        while (true) {
            if (toupper(task) == 'N') {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            else if (toupper(task) == 'Y') {
                //read data from exist file
                table.hasOldHtml = true;
                break;
            }
            else {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Error: invalid input [" << task << "]" << endl;
                cout << "[N]-Let's create a new one!" << endl;
                cout << "[Y]-Read the old data!" << endl;
            }
            cin >> task;
        }
    }

    if (table.hasOldHtml) {
        readDataFromOldFile(table, inFile);
    }
    else {
        skdSettingFromUser(table);
        courseSectionGenerator(table);
        fillScheduleSection(table);
    }

    ofstream outFile;
    if (table.hasOldHtml) {
        if (table.type == 5) {
            cout << "++++++++++++++ CURRENT SCHEDULE ++++++++++++++\n\n";
        }
        else {
            cout << "+++++++++++++++++++++ CURRENT SCHEDULE +++++++++++++++++++++\n\n";
        }
        outputLayout(table);
        cout << "\n\nReady to rewrite your schedule? \n"
            "Enter [Y] to continue, or any key to end the program: ";
        char task;
        cin >> task;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (toupper(task) == 'Y') {
            outFile.open("schedule.html");
            if (!outFile) {
                cerr << "File failed to create";
                return EXIT_FAILURE;
            }
        }
        else {
            cout << "[" << task << "] End of the program\n";
            return EXIT_SUCCESS;
        }
    }
    else {
        outFile.open("schedule.html");
        if (!outFile) {
            cerr << "File failed to create";
            return EXIT_FAILURE;
        }
    }


    while (true) {
        outputLayout(table);
        cout << "Is the schedule complete? [Y/N] ";
        char temDone;
        char task;
        cin >> temDone;
        if (toupper(temDone) == 'Y') {
            table.isDone = true;
            htmlGenerator(outFile, table);
            return EXIT_SUCCESS;
        }
        else if (toupper(temDone) == 'N') {
            cout << "\nWhat do you want to adjust? [A]:add course/[B]:adjust course name/[C]adjust course section ";
            cin >> task;
            if (toupper(task) == 'A') {
                table.courseNum = 0;
                while (table.courseNum == 0){
                    cout << "\nHow many courses do you want to add: ";
                    cin >> table.courseNum;
                    if (!cin) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Error: [Input should be a number]" << endl;
                    }
                }
                fillScheduleSection(table);
                continue;
            }
            else if (toupper(task) == 'B') {
                string oriCourseName;
                string newCourseName;
                cout << "\nWhich course to rename: ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, oriCourseName);
                cout << "\nNew course name: ";
                while (newCourseName == "") {
                    getline(cin, newCourseName);
                }
                renameCourse(table, oriCourseName, newCourseName);
                continue;
            }
            else if (toupper(task) == 'C') {
                string sectionCode;
                char task;
                cout << "\nEnter section-code or Enter [V] to check the section-code from current schedule";
                cout << "\nWhich section to adjust: " ;
                cin >> sectionCode;
                if (sectionCode == "V" || sectionCode == "v") {
                    output(table);
                    cout << "\nWhich section to adjust: " ;
                    cin >> sectionCode;
                }

                //string to upper
                std::transform(sectionCode.begin(), sectionCode.end(), sectionCode.begin(), ::toupper);

                cout << "Do you want to [D]-Delete \"" << sectionCode << "\" or [R]-Reassign it to a new course? ";
                while (true) {
                    cin >> task;
                    cout << "\n\n";
                    auto it = std::find_if(table.coursesSectionVec.begin(), table.coursesSectionVec.end(),
                        [&sectionCode](pair<string, string> const& el) {return el.first == sectionCode; });
                    if (toupper(task) == 'D') {
                        if (it != table.coursesSectionVec.end()) {
                            it->second = "na";
                        }
                        break;
                    }
                    else if (toupper(task) == 'R') {
                        string course;
                        cout << "The course name for this section: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        getline(cin, course);
                        if (it != table.coursesSectionVec.end()) {
                            std::transform(course.begin(), course.end(), course.begin(), ::toupper);
                            it->second = course;
                        }
                        break;
                    }
                    else {
                        cout << "Enter [D] for Delete or [R] for Reassign" << endl;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                continue;
            }
            else {
                cout << "Bad input [" << task << "]" << endl;
            }
        }
        else {
            cout << "Bad input." << endl;
        }
    }
}
