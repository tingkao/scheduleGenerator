/*
 File Name:  func.cpp
 Purpose:    File contains functions used in skd.cpp
 Coder:      Yu-Ting Kao
 Date:       2021-08-21
 */

#include "func.hpp"
using namespace std;

void htmlGenerator(ofstream& outFile, timeTable const& table) {
    outFile <<
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <meta http-equiv=\"refresh\" content=\"3600\">\n"
        "    <title>Weekly Schedule</title>\n"
        "    <!-- google-font: Anton -->\n"
        "    <link href = \"https://fonts.googleapis.com/css2?family=Didact+Gothic&family=Francois+One&family=Rampart+One&display=swap\" rel = \"stylesheet\" >\n";

    outFile << cssGenerator();
    outFile <<
        "</head>\n"
        "<body>\n";

    outFile <<
        "    <header>\n"
        "<h1>" << table.name << "'s SCHEDULE</h1>\n"
        "    </header>\n";

    outFile << "    <div class=\"wrap\">\n"
        << timeColGenerator(table.startTime, table.endTime);

    //Schedule Columns From Monday to Friday
    for (size_t i = 0; i < 5; i++) {
        outFile << columnGenerator(i, table);
    }

    //Schedule Columns for Saturday and Sunday
    if (table.type == 7) {
        outFile << columnGenerator(5, table);
        outFile << columnGenerator(6, table);
    }
    outFile <<
        "    </div>\n"
        "    <a class=\"weekly\" href=\"##\">check weekly schedule</a>\n"
        << JsGenerator()
        << scheduleData(table) <<
        "</body>\n"
        "</html>\n";
}

string cssGenerator() {
    string style =
        "    <style>\n"
        "    * {\n"
        "    margin: 0;\n"
        "    padding: 0;\n"
        "    }\n"
        "    body {\n"
        "        text-align: center;\n"
        "        font-family: \"Didact Gothic\";\n"
        "        padding-bottom: 40px;\n"
        "    }\n"
        "    .wrap {\n"
        "        max-width: 960px;\n"
        "        margin: auto;\n"
        "        display: flex;\n"
        "        justify-content: center;\n"
        "    }\n"

        "    .tt div, .col div {\n"
        "        border: solid 1px black;\n"
        "        width: 120px;\n"
        "        height: 42px;\n"
        "        margin-bottom: 5px;\n"
        "        box-sizing: border-box;\n"
        "        display: flex;\n"
        "        align-items: center;\n"
        "        justify-content: center;\n"
        "        margin-bottom: 14px;\n"
        "        border-radius: 4px;\n"
        "    }\n"
        "    .col {\n"
        "        margin-left: 24px;\n"
        "    }\n"
        "    header{\n"
        "        margin-bottom: 20px;\n"
        "    }\n"
        "    h1{\n"
        "        margin-top: 20px;\n"
        "        margin-bottom: 30px;\n"
        "        font-family: \"Rampart One\";\n"
        "    }\n"
        "    .col div:first-of-type{\n"
        "        color: #666;\n"  
        "        font-family: \"Francois One\";\n"
        "    }\n"

        "    div.now {\n"
        "        animation:brath 8s  linear infinite;\n"
        "        color: rgb(255, 255, 255);\n"
        "        font-weight: 900;\n"
        "        background-color: rgb(71, 144, 255);\n"
        "        border: hidden;\n"
        "        box-shadow: 1px 1px 4px rgb(20, 65, 133);\n"
        "     }\n"
        "     div.now.empty{\n"
        "        background-color: white;\n"
        "        border: solid 2px rgb(71, 144, 255);\n"
        "        box-shadow: none;\n"
        "      }\n"

        "    @keyframes brath{\n"
        "        0% {transform: scale(.9); }\n"
        "        25% {transform: scale(1); }\n"
        "        50% {transform: scale(.9); }\n"
        "        75% {transform: scale(1); }\n"
        "        100% {transform: scale(.9); }\n"
        "     }\n\n"

        "@media screen and (max-width: 720px) {\n"
        "   div.rwd_disable{\n"
        "       display: none;\n"
        "   }\n"
        "   .wrap {\n"
        "       margin-bottom: 20px;\n"
        "   }\n"
        "}\n"
        "@media screen and (min-width: 721px) {\n"
        "   div.larger{\n"
        "     width: 240px;\n"
        "   }\n"
        "   .weekly {\n"
        "       display: none;\n"
        "   }\n"
        "}\n"

        "    </style>\n";

    return style;
}

string JsGenerator() {
    string script =
    "<script>\n"
    "var currentdate = new Date();\n"
    "var itNum = document.querySelector('.tt').childElementCount - 1 + 2;\n"
    "for (var i = 2; i < itNum; i++) {\n"
    "   if (document.querySelector(`.tt div:nth-child(${i})`).innerHTML.split(\":\")[0] == (currentdate.getHours())) {\n"
    "       document.querySelector(`.tt div:nth-child(${i})`).style.border = \"solid 2px rgb(71, 144, 255)\";\n"
    "       document.querySelector(`.tt div:nth-child(${i})`).style.color = \"rgb(71, 144, 255)\";\n"
    "       document.querySelector(`.tt div:nth-child(${i})`).style.fontWeight = \"900\";\n"
    "       document.querySelector(`.wrap div:nth-child(${currentdate.getDay() + 1 }) div:nth-child(${1})`).style.border = \"solid 2px rgb(71, 144, 255)\";\n"
    "       document.querySelector(`.wrap div:nth-child(${currentdate.getDay() + 1 }) div:nth-child(${1})`).style.color = \"rgb(71, 144, 255)\";\n"

    "       var section = document.querySelector(`.wrap div:nth-child(${currentdate.getDay() + 1 }) div:nth-child(${i})`);\n"
    "       section.classList.add(\"now\");\n"

    "       if(section.innerHTML == \"\"){\n"
    "           section.classList.add(\"empty\");\n"
    "       }\n"

    "    }\n"
    "}\n"

    "document.querySelectorAll(`.col`).forEach(element => {\n"
    "    element.classList.add(\"rwd_disable\");\n"
    "});\n"
    "document.querySelectorAll(`.wrap div:nth-child(${currentdate.getDay() + 1 })`).forEach(element => {\n"
    "    element.classList.remove(\"rwd_disable\");\n"
    "});\n"
    "document.querySelectorAll(`.wrap div:nth-child(${currentdate.getDay() + 1 }) div`).forEach(element => {\n"
    "    element.classList.add(\"larger\");\n"
    "});\n"

    "if(60 - currentdate.getMinutes() != 60){\n"
    "    window.setTimeout(function() {\n"
    "       window.location.href = './schedule.html';\n"
    "    }, (60 - currentdate.getMinutes()) * 60 * 1000);\n"
    "}\n"
    "</script>\n";

    return script;
}

string columnGenerator(unsigned index , timeTable const& table) {

    //Table header
    string column =
        "        <div class=\"col col_" + table.days[index] + "\">\n"
        "            <div>" + table.days[index] + "</div>\n";

    unsigned gap = table.endTime - table.startTime;
    unsigned columnIndex = 0;
    for (size_t i = table.startTime; i < table.endTime; i++) {
        string second = table.coursesSectionVec[index*gap + columnIndex].second;
        string temStr = (second != "na") ? second : "";
        std::transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);

        column += "            <div>" + temStr + "</div>\n";
        columnIndex++;
    }
    column += "        </div>\n";

    return column;
}

string timeColGenerator(unsigned start, unsigned end) {
    string timeCol =
        "        <div class=\"tt\">\n"
        "            <div class=\"time_sec0 disable\">TimeZone[EDT]</div>\n";
    for (size_t i = start; i < end; i++) {
        timeCol = timeCol + "            <div>" + to_string(i)
            + ":00 - " + to_string(i + 1) + ":00</div>\n";
    }

    timeCol = timeCol + "        </div>\n";
    return timeCol;
}

void fillScheduleSection(timeTable& table) {
    unsigned index = 1;
    while (index <= table.courseNum) {
        string temCourse;
        string inputCourse;

        if (index == 1) {
            //Clear cin buffer, for first iteration
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        while (temCourse == "") {
            cout << "What's your #" << index << " course: ";
            getline(cin, temCourse);
            if (temCourse.find('$') != string::npos) {
                cout << "Course name can not contant symbol: \"$\"\n";
                temCourse = "";
            }
        }
        index++;
        output(table);
        cout << "\nChoose sections for [" << temCourse << "]" << endl;
        cout << "Section Example: M10/M11/M12/H12/H13\n";
        cout << "Sections: ";
        getline(cin, inputCourse);

        stringstream ss(inputCourse);
        string temKey;
        while (getline(ss, temKey, '/')) {
            //trim spaces from both sides
            stringstream spcClear(temKey);
            spcClear >> table.vecKey;

            //string to upper
            std::transform(table.vecKey.begin(), table.vecKey.end(), table.vecKey.begin(), ::toupper);

            //find if the pair.first has matched-key
            auto it = std::find_if(table.coursesSectionVec.begin(), table.coursesSectionVec.end(),
                [&table](pair<string, string> const& el) {return el.first == table.vecKey; });
            if (it != table.coursesSectionVec.end()) {
                std::transform(temCourse.begin(), temCourse.end(), temCourse.begin(), ::toupper);
                it->second = temCourse;
            }
            else {
                cout << "-------------------------------------" << endl;
                cout << "Error: " <<table.vecKey << " is not a valid section." << endl;
            }
        }
        cout << "\n\n";
    }//end while-loop
}

void outputLayout(timeTable const& table) {
    if (table.type == 5) {
        cout << "+++++++++++ YOUR SCHEDULE COMPLETE +++++++++++\n\n";
    }
    else {
        cout << "++++++++++++++++++ YOUR SCHEDULE COMPLETE ++++++++++++++++++\n\n";
    }

    if (table.type == 5) {
        unsigned spaceCount = (46 - (table.name.size() + 11))/2;
        cout << left << setw(spaceCount) << "" << table.name << "'s Schedule\n";
        cout << "----------------------------------------------\n";
    }
    else {
        unsigned spaceCount = (60 - (table.name.size() + 11)) / 2;
        cout << right << setw(spaceCount) << "" << table.name << "'s Schedule\n";
        cout << "------------------------------------------------------------\n";
    }

    unsigned gap = table.endTime - table.startTime;
    for (size_t i = table.startTime; i < table.endTime; i++) {
        unsigned num = i - table.startTime;
        string lhs = (to_string(i).size() > 1)? to_string(i):"0" + to_string(i);
        string rhs = (to_string(i+1).size() > 1) ? to_string(i+1) : "0" + to_string(i+1);
        cout << "| " << left << setw(3) << lhs << "-" << right << setw(3) << rhs << " ";

        for (size_t j = 0; j < 5; j++) {
            string second = table.coursesSectionVec[num].second;
            string temStr = (second != "na") ? second.substr(0, 3) + "*" : "";
            std::transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);
            cout << "|  " << left << setw(4) << temStr;
            num += gap;
        }
        if (table.type == 5) {
            cout << "|\n";
            cout << "----------------------------------------------\n";
        }
        else {
            for (size_t j = 5; j < 7; j++) {
                string second = table.coursesSectionVec[num].second;
                string temStr = (second != "na") ? second.substr(0, 3) + "*" : "";
                std::transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);
                cout << "|  " << left << setw(4) << temStr;
                num += gap;
            }
            cout << "|\n";
            cout << "------------------------------------------------------------\n";
        }
    }
}

void output(timeTable const& table) {
    if (table.type == 5) {
        cout << "----------------------------------------------\n";
        cout << "|    CHOOSE TIME SECTIONS FOR YOUR COURSE    |\n";
        cout << "----------------------------------------------\n";
    }
    else {
        cout << "------------------------------------------------------------\n";
        cout << "|          CHOOSE TIME SECTIONS FOR YOUR COURSE            |\n";
        cout << "------------------------------------------------------------\n";
    }

    unsigned gap = table.endTime - table.startTime;
    for (size_t i = table.startTime; i < table.endTime; i++) {
        unsigned num = i - table.startTime;
        string lhs = (to_string(i).size() > 1) ? to_string(i) : "0" + to_string(i);
        string rhs = (to_string(i + 1).size() > 1) ? to_string(i + 1) : "0" + to_string(i + 1);
        cout << "| " << left << setw(3) << lhs << "-" << right << setw(3) << rhs << " ";

        for (size_t j = 0; j < 5; j++) {
            string first = table.coursesSectionVec[num].first;
            string second = table.coursesSectionVec[num].second;
            string temStr = (second != "na") ? second.substr(0, 3) + "*" : first;
            std::transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);
            cout << "|  " << left << setw(4) << temStr;
            num += gap;
        }
        if (table.type == 5) {
            cout << "|\n";
            cout << "----------------------------------------------\n";
        }
        else {
            for (size_t j = 5; j < 7; j++) {
                string first = table.coursesSectionVec[num].first;
                string second = table.coursesSectionVec[num].second;
                string temStr = (second != "na") ? second.substr(0, 3) + "*" : first;
                std::transform(temStr.begin(), temStr.end(), temStr.begin(), ::toupper);
                cout << "|  " << left << setw(4) << temStr;
                num += gap;
            }
            cout << "|\n";
            cout << "------------------------------------------------------------\n";
        }
    }
}

void courseSectionGenerator(timeTable& table) {
    unsigned itNum = table.type;
    for (size_t j = 0; j < itNum; j++) {
        for (size_t i = table.startTime; i < table.endTime; i++) {
            table.coursesSectionVec.push_back({ (table.dayStr[j] + to_string(i)) , "na" });
        }
    }
}

void renameCourse(timeTable& table, string oriName, string newName) {

    //string to upper
    std::transform(oriName.begin(), oriName.end(), oriName.begin(), ::toupper);
    std::transform(newName.begin(), newName.end(), newName.begin(), ::toupper);

    bool isFound = false;
    bool isDoneSearching = false;
    //find if the pair.second has matched-key
    while (!isDoneSearching) {
        isDoneSearching = true;
        auto it = std::find_if(table.coursesSectionVec.begin(), table.coursesSectionVec.end(),
            [&oriName](pair<string, string> const& el) {return el.second == oriName; });
        if (it != table.coursesSectionVec.end()) {
            it->second = newName;
            isDoneSearching = false;
            isFound = true;
        }
    }

    if (!isFound) {
        cout << "Can not find course  [" << oriName << "]" << endl;

        cout << "Current course data: ";
        for (auto v : table.coursesSectionVec) {
            if (v.second != "na") {
                table.courseData.insert(v.second);
            }
        }
        for (auto s : table.courseData) {
            cout << "[" << s << "] ";
        }
        cout << "\n\n" << endl;
    }
}

void readDataFromOldFile(timeTable& table, ifstream& inFile) {
    string temLine;
    while (getline(inFile, temLine)) {
        if (temLine.substr(0, 4) == "<h1>") {
            table.name = temLine.substr(4, temLine.size() - 20);
        }
        if (temLine == "<!--data_key") {
            getline(inFile, temLine);
            stringstream ss(temLine);
            string temSection;
            while (getline(ss, temSection, '$')) {
                table.coursesSectionVec.push_back({ temSection, "" });
            }
        }
        if (temLine == "<!--data_value") {
            getline(inFile, temLine);
            stringstream ss(temLine);
            string temCourse;
            unsigned index = 0;
            while (getline(ss, temCourse, '$')) {
                table.coursesSectionVec[index].second = temCourse;
                index++;
            }
            break;
        }
    }

    table.startTime = stoul(table.coursesSectionVec.front().first.substr(1));
    table.endTime = stoul(table.coursesSectionVec.back().first.substr(1)) + 1;
    if (table.coursesSectionVec.back().first[0] == 'F') {
        table.type = 5;
    }
    else {
        table.type = 7;
    }
}
void skdSettingFromUser(timeTable& table) {
    cout << "What's your name: ";
    getline(cin, table.name);
    cout << "\nWhich kind of schedule do you need? \n";

    while (true) {
        cout << "[WD]-5 days from Monday to Friday\n"
            << "[WKD]-7 days from Monday to Sunday ";

        string tem;
        getline(cin, tem);
        for (auto& c : tem) c = toupper(c);

        if (tem == "WD") {
            table.type = 5;
            break;
        }
        else if (tem == "WKD") {
            table.type = 7;
            break;
        }
        else {
            cout << "\nBad switch, enter again \n";
        }
    }
    while (true) {
        cout << "\nSet the start time for your schedule[0-23]: ";
        cin >> table.startTime;
        if (!cin) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Error: Input should be a number between 0 and 23" << endl;
        }
        else if (table.startTime > 23) {
            cout << "Error: Input should be a number between 0 and 23" << endl;
            continue;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Set the end time for your schedule[0-24]: ";
        cin >> table.endTime;
        if (!cin) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Error: Input should be a number between 0 and 24" << endl;
        }
        else if (table.endTime > 24) {
            cout << "Error: Input should be a number between 0 and 24" << endl;
            continue;
        }
        else if (table.endTime <= table.startTime) {
            cout << "Error: the end time should be larger than the start time\n" << endl;
        }
        else {
            break;
        }
    }
    while (table.courseNum == 0) {
        cout << "\nHow many courses do you have: ";
        cin >> table.courseNum;
        if (!cin) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Error: [Input should be a number]" << endl;
        }
    }
    cout << "\n===============================\n";
}
string scheduleData(timeTable const& table) {
    string command = "\n<!--data_key\n";
    for (auto v : table.coursesSectionVec) {
        command += v.first + "$";
    }
    command += "\n-->\n";

    command += "\n<!--data_value\n";
    for (auto v : table.coursesSectionVec) {
        if (v.second == "") {
            command += "na/";
        }
        else {
            command += v.second + "$";
        }
        
    }
    command += "\n-->\n";

    command = "<script>/*" + command + "*/</script>\n";

    return command;
}
