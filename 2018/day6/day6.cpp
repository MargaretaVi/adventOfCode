#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <map>
#include <typeinfo>

using namespace std;

//Split line on blankspace " "
void splitLine(string s, vector<int> &xValues, vector<int> &yValues, vector<pair<int,int>> &inputCoordinates) {
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
    inputCoordinates.push_back(make_pair(stoi(x),stoi(y)));
}

int calculateMHDist(int myX, int myY, int boardX, int boardY) {
    return abs(myX - boardX) + abs(myY - boardY);
}

int main () {
    
    string _line;
    vector<pair<int,int>> inputCoordinates;
    vector<int> xValues, yValues;

    // first pair is the coordinate on the board
    // second pair: ID for each point in input file, manhatan distance to the coordinate on the board
    map<pair<int,int>, pair<int,int>> board;
    
    ifstream myfile("test.txt");

     if (myfile.is_open()) {
        while (getline (myfile,_line)) {
            //remove ","
            _line.erase(remove(_line.begin(), _line.end(), ','), _line.end());
            splitLine(_line, xValues, yValues, inputCoordinates);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    // finding the max of x and y
    vector<int>::iterator tmp;
    tmp = max_element(xValues.begin(), xValues.end());
    int xMax = xValues[distance(xValues.begin(), tmp)];

    tmp = max_element(yValues.begin(), yValues.end());
    int yMax = yValues[distance(yValues.begin(), tmp)];
    
    for (auto x = 0; x < xMax; x++) {
        for (auto y = 0; y < yMax; y++) {
            int pointId = 0;
            for (auto p: inputCoordinates) {
                if ()
                int mHDist = calculateMHDist(p.first, p.second, x, y);
                board[pair<int,int> (x,y)] = pair<int,int> (pointId, mHDist);
                pointId++;
            }
        }
    }
    

    return 0;
}