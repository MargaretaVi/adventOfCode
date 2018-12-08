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
    map<pair<int,int>, map<int,int>> board;
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
    int counter = 1;
    int x,y;
    cout << "max values: " << xMax << " " << yMax << endl; 
    // set up all the values for the board.
        for (x = 0; x <= xMax ; x++) {
            for (y = 0; y <= yMax ; y++) {
                counter = 1;
                for (auto p: inputCoordinates) {
                    int tmpXValue = p.first;
                    int tmpYValue = p.second;
                    int dist = INT_MAX; 
                    // not on the boarder
                    if (!(x == 0 || y == 0 || x == xMax || y == yMax ||tmpXValue == xMax || tmpYValue == yMax)) 
                    {
                        dist = calculateMHDist(tmpXValue, tmpYValue, x, y);
                      /*  if (tmpXValue == 1) {
                            cout << " cords " << x << "," << y << "   the distance: " << dist << "   my values " << tmpXValue << "," << tmpYValue <<'\n';
                        }

                        if (dist == 0) {
                            cout << " cords " << x << "," << y << "  mmy input" << tmpXValue << "," << tmpYValue << '\n';
                        }*/
                    }
                    board[pair<int, int> (x,y)][counter] = dist;
                    counter ++;
                }
            }
        }
       
    map<int,int> scoreHolder; 
    // for each coordinate on the board

    for (auto kv : board) {
        int tempWinner = INT_MAX;
        int distanceToMe = INT_MAX;
        // for each input coordiante
        for (auto innerKv : kv.second) {
            if (innerKv.second < distanceToMe) {
                distanceToMe = innerKv.second;
                tempWinner = innerKv.first;
            }
            //cout << " coodinate : " << kv.first.first << "," << kv.first.second << " current " << innerKv.second << "  who am i_ " << innerKv.first << endl; // " challenger" << innerKv.second << endl;

            if (innerKv.second == distanceToMe) {
                continue;
                //tempWinner = INT_MAX;
            }
        }
        if (tempWinner != INT_MAX && distanceToMe !=INT_MAX) {
            if (scoreHolder.count(tempWinner)) {
                cout << " coodinate : " << kv.first.first << "," << kv.first.second << "   winner " << tempWinner << " ditnace " << distanceToMe << endl;
                scoreHolder.at(tempWinner) += 1;
            }
            else {
                scoreHolder[tempWinner] = 1;
            }
        }    
    }

    int area = 0;
    int winner = INT_MAX; 
    cout << "the size of score holder is " << scoreHolder.size() << endl;
    for (auto coord : scoreHolder) {
        if (coord.second > area) {
            area = coord.second;
            winner = coord.first;
        }
    }

    cout << "The alrgest area is : " << area << " and the coodinate winner is: " << winner << endl;
    return 0;
}