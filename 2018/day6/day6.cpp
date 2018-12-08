#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <set>


using namespace std;

//Split line on blankspace " "
void splitLine(string s, vector<int> &xValues, vector<int> &yValues) {
    size_t pos = 0;
    std::string x;
    std::string y;
    string delimiter = " ";

    while ((pos = s.find(delimiter)) != std::string::npos) {
        x = s.substr(0, pos);
        y = s.substr(x.size(), pos + 1);
        xValues.push_back(stoi(x));
        yValues.push_back(stoi(y));

        s.erase(0, pos + delimiter.length());
    }
}

int calculateMHDist(int myX, int myY, int boardX, int boardY) {
    return abs(myX - boardX) + abs(myY - boardY);
}

int main () {
    
    string _line;
    vector<pair<int,int>> dataLines;
    vector<int> xValues, yValues;

    ifstream myfile("init.txt");

    if (myfile.is_open()) {
        while (getline (myfile,_line)) {
            //remove ","
            _line.erase(remove(_line.begin(), _line.end(), ','), _line.end());
            splitLine(_line, xValues, yValues);
        }
        myfile.close();
    }
    else cout << "Unable to open file";


}