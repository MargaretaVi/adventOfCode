#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

// the indexing starts on -3
uint64_t countPots(string potStr, uint64_t offSet) {
    uint64_t sum = 0;
    for (string::iterator iter = potStr.begin(); iter != potStr.end(); iter++) {
        if (*iter == '#') {
            sum += (iter - potStr.begin()) + offSet;
        }
    }   
    return sum;
}

using namespace std;
int main() {

    string _line;
    vector<string> dataLines;
    ifstream myfile("init.txt");
    if (myfile.is_open()) {
        while (getline (myfile,_line) ) {
            dataLines.push_back(_line);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file\n"; 
    }

    //split the data into init state and "instructions";
    string initState = "#.#.#...#..##..###.##.#...#.##.#....#..#.#....##.#.##...###.#...#######.....##.###.####.#....#.#..##";
    //initState = string(dataLines[0].begin() + 15, dataLines[0].end()); // cannot add padding to the end of this string
    vector<string> instructionsTmp (dataLines.begin() + 2, dataLines.end());


    vector<pair<string,string>> instructions;
    // should match string to string in the instructions
    for (auto ins : instructionsTmp) {
        string match, answer;
        size_t equal = ins.find("=>");
        match = ins.substr(0, 5);
        answer = ins.substr(equal + 3);
        instructions.push_back(pair<string,string> (match, answer));
    }
    string tmpSmallString, newStateString;
    string newString = initState;
    uint64_t offSet = 0;
    string tmp = "...." + newString + "....";
    cout << 0 << "    " << tmp << endl;
    for (auto gen= 1; gen <=3000; gen++) {
        auto firstSharp = newString.find('#');
        while (firstSharp < 4) {
            newString.insert(0, ".");
            offSet--;
            firstSharp = newString.find('#');
        }

        auto lastSharp = newString.find_last_of('#');
        while ((newString.size() - lastSharp) < 5) {
            newString.insert(newString.end(), '.');
            lastSharp = newString.find_last_of('#');
        }

        // new state string every loop
        newStateString = string(newString.size(), '.');
        string::iterator modifyIter = newStateString.begin();
        for (string::iterator start = newString.begin(); start != newString.end()-5; start++) {
            tmpSmallString = string(start, start + 5);
            for (auto ins : instructions) {
                if (tmpSmallString == ins.first) {
                    const char tmp = *ins.second.c_str();
                    *(modifyIter+2) = tmp;
                }
            }
            modifyIter++;
        }
        newString = newStateString;
        //cout << gen << ":   " << newStateString << endl; 
    }
    
    // "UT"
    //string testString = ".#....##....#####...#######....#.#..##.";
    uint64_t test = countPots(newStateString, offSet);
    /*if (test == 325) {
        cout << "success! \n";
    } 
    else {
        cout << test << endl;
        cout << "You did wrong \n";
    }*/
    cout << "this is the answer: " << test << endl;

   return 0;
}