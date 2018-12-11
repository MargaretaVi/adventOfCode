#include <iostream>
#include <vector>
#include <string> 
#include <typeinfo>

using namespace std;

int hundredValue(int powerLevel) {
    return  ((powerLevel % 1000) / 100);
}

int calcPowerLevel(int xCoord, int yCoord, int gridSerialNumber) {
    int rackId, powerLevelStart, finalValue;
    rackId = xCoord + 10;
    //cout << "this is the rack ID " << rackId << endl;
    powerLevelStart = rackId * yCoord;
    //cout <<" Power level starts at: " << powerLevelStart << endl;
    powerLevelStart += gridSerialNumber;
    //cout << "adding the serial number " << powerLevelStart << endl;
    powerLevelStart *= rackId;
    finalValue = hundredValue(powerLevelStart);
    return finalValue - 5;

}

int calcAreaPowerLevel(int xCoord, int yCoord, vector<vector<int>> board) {
    int totPowerLevel = 0;
    // input x and y is the top left corner of the square
    for (auto x = xCoord; x < xCoord + 2; x++) {
        for(auto y = yCoord; y < yCoord + 2; y++) {
            totPowerLevel += board[x][y];
        }
    }
    return totPowerLevel;
}

int main() {
    cout << "starting day 11" << endl;
    int gridSerialNumber = 42;
    // y, x (row by col)
    vector<vector<int>> board(298, vector<int>(298,0));
    //int test = calcPowerLevel(101, 153, 71);
    //int test = hundredValue(463278);
   //cout << "this is the power level: " << test << endl;
    for (auto x = 1; x < board.size()-1; x++) {
        for (auto y = 1; y < board[y].size()-1; y++) {
            board[x][y] = calcPowerLevel(x,y,gridSerialNumber);
        }
    }

    int area = calcAreaPowerLevel(21,61, board); // should be 30

    cout << "this is the total area: " << area << endl;
    return 0;
}