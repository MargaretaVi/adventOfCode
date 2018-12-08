#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <regex>
#include <typeinfo>

using namespace std;

struct defaultToZero{
    int i = 0;
};

int main() {
    
    string line;
    vector<string> infoList;
    ifstream infile("init.txt");

    int guardId, fallAsleep, wakeUp;
    // guard ID, current minute, how many times guard is asleep on this minute,
    map<int, map<int,int>> guardInfo;

    // guardId, total sleeping time;
    map<int,int> sleepiestGuard;

    while (getline(infile, line)) {
        infoList.push_back(line);
    }   
    sort(infoList.begin(), infoList.end());

    for (auto line: infoList) {
        size_t found = line.find("]");
        string timeStamp = line.substr(0,found); // timestamp date and time
        string str = line.substr((found+1)); // string message in each line

        // line has guard Id
        if (str.find("#") != string::npos) {
            regex  guardIdDel("\\d+");
            smatch guardIdMatch;
            // Get guard id
            regex_search(str, guardIdMatch, guardIdDel);
            guardId = stoi(guardIdMatch[0]);
        }

        else if (str.find("falls asleep") != string::npos ) {
            size_t found = timeStamp.find(":"); 
            fallAsleep = stoi(timeStamp.substr(found+1));
        }

        else if (str.find("wakes up") != string::npos ) {
            size_t found = timeStamp.find(":"); 
            wakeUp = stoi(timeStamp.substr(found+1));
            int diff = wakeUp - fallAsleep;
            sleepiestGuard[guardId] += diff;
            for (auto minu = fallAsleep; minu < wakeUp; minu++) {
                if (guardInfo.count(guardId)) {
                    guardInfo[guardId][minu] +=1;
                }
                else {
                    map<int,int> tmpMap;
                    tmpMap[minu] = 1;
                    guardInfo[guardId] = tmpMap;
                }
            }
        }

    }
    int tmpGuard = 0;
    int tmpSleep = 0;
    for (auto kv: sleepiestGuard) {
        if (kv.second > tmpSleep) {
            tmpSleep = kv.second;
            tmpGuard = kv.first;
        }
    }
    cout << "The sleepiest guard is: " << tmpGuard << "When the amount of sleep: " << tmpSleep << endl;

    int whichMinute = 0;
    int howManyTimes = 0;
    map<int,int> info = guardInfo[tmpGuard];
    for (auto kv: info) {
        if( kv.second > howManyTimes) {
            whichMinute = kv.first;
            howManyTimes = kv.second;
        }
    }
    cout << "He sleep the longest on : " << whichMinute << " with this many times: " << howManyTimes << endl;
    int res = tmpGuard* whichMinute;
    cout << "this took way to loong to get: " << res << endl;

    tmpGuard = 0;
    whichMinute = 0;
    howManyTimes = 0;
    for (auto kv : guardInfo) {
        for (auto innerkv : guardInfo[kv.first]) {
            int tmpTimes = innerkv.second;
            if(tmpTimes > howManyTimes) {
                tmpGuard = kv.first;
                whichMinute = innerkv.first;
                howManyTimes = tmpTimes;
            }
        }
    }
    res = tmpGuard * whichMinute;
    cout << "guard: " << tmpGuard << " minute " << whichMinute << " times " << howManyTimes << " result: " << res << endl;
    return 0;

}