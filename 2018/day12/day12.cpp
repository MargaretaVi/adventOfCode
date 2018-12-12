#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// the indexing starts on -3
int countPots(string potStr) {
    int sum = 0;
    for (string::iterator iter = potStr.begin(); iter != potStr.end(); iter++) {
        if (*iter == '#') {
            sum += (iter - potStr.begin()) - 3;
        }
    }   
    return sum;
}

using namespace std;
int main() {

    string _line;
    vector<string> dataLines;
    ifstream myfile ("init.txt");
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
    string initState (dataLines[0].begin() + 15, dataLines[0].end());
    vector<string> instructionsTmp (dataLines.begin() + 2, dataLines.end());

    // the int should indicate the generation
    vector<pair<int,string>> plantStates;
    // add the inititalize state
    plantStates.push_back(pair<int,string> (0,initState));

    vector<pair<string,string>> instructions;
    // should match string to string in the instructions
    for (auto ins : instructionsTmp) {
        string match, answer;
        size_t equal = ins.find("=>");
        match = ins.substr(0, 5);
        answer = ins.substr(equal + 3);
        instructions.push_back(pair<string,string> (match, answer));
    }

    // "UT"
    string testString = ".#....##....#####...#######....#.#..##.";
    int test = countPots(testString);
    if (test == 325) {
        cout << "success! \n";
    } 
    else {
        cout << test << endl;
        cout << "You did wrong \n";
    }

    for (auto g = 1; g< 21; g++) {
        string lastGen = plantStates.back().second;
        string::iterator it = lastGen.begin();
        vector<int> indices;
        string valueToFind = "#";
        size_t pos = lastGen.find(valueToFind);

        while( pos != string::npos) {
            indices.push_back(pos);
            pos = lastGen.find(valueToFind, pos + valueToFind.size());
        }

        for (auto ind : indices) {
            string tmp = "";
            // fix so that we update the generation with the instructions...
            //plantStates.push_back(pair<int, string> (ind, lastGen));
        }
    }


    /*for (auto state : plantStates) {
        cout << "Generation " << state.first << " : " << state.second << endl;
    }
    */

    return 0;
}