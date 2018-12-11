#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>
#include <climits>

using namespace std;

void appendToVectors(vector<pair<int,int>> &positions, vector<pair<int,int>> &velocity, vector<string> dataTmp) {
    // split data into two vectors: pos and vel
    int cnt = 0;
    size_t tmp;
    string first,second;

    for (auto d: dataTmp) {
        tmp = d.find(",");
        first = d.substr(0, tmp);
        second = d.substr(tmp+1);
        if (cnt % 2 == 0) {
            // add to position vector
            positions.push_back(pair<int,int> (stoi(first),stoi(second)));
        }
        else {
            // add to velocity vector
            velocity.push_back(pair<int,int> (stoi(first),stoi(second)));
        }
        cnt ++;
    }
}

void calcNewPos(vector<pair<int,int>> &Pos, vector<pair<int,int>> &velocity) {
    // calculate the new positions
    for (vector<pair<int,int>>::iterator iter = Pos.begin(); iter != Pos.end(); iter++) {
        //cout << (*iter).first << " " << (*iter).second << " " << velocity[distance(Pos.begin(), iter)].first << " " << velocity[distance(Pos.begin(), iter)].second << endl;
        (*iter).first += velocity[distance(Pos.begin(), iter)].first;
        (*iter).second += velocity[distance(Pos.begin(), iter)].second;
        //cout <<   (*iter).first << " " <<  (*iter).second << endl;
    }
}

uint64_t calcArea(vector<pair<int,int>> newPos, vector<int> &limits) {
    // sort on x values first
    sort(newPos.begin(), newPos.end(), [](auto & left, auto & right){return left.first < right.first;});
    uint64_t area;
    limits.at(0) = newPos.at(0).first;
    limits.at(1) = newPos.at(newPos.size()-1).first;
    //n sort on y values
    sort(newPos.begin(), newPos.end(), [](auto & left, auto & right){return left.second < right.second;});
    limits.at(2) = newPos.at(0).second;
    limits.at(3) = newPos.at(newPos.size()-1).second;
    area = abs(limits[0]- limits[1]) * abs(limits[2]-limits[3]);
    return area;

}

void clearBoard(vector<vector<char>> &board) {
    for (auto y = 0; y < board.size(); y++) {
        for (auto x = 0; x < board[y].size(); x++) {
            board[y][x] = '.';
        }
    }
}

void drawing(vector<pair<int,int>> &positions, vector<int> limits) {
    sort(positions.begin(), positions.end(), [](auto & left, auto & right){return left.first < right.first;});
    int xMin = positions.at(0).first;
    int xMax = positions.at(positions.size()-1).first;
    //n sort on y values
    sort(positions.begin(), positions.end(), [](auto & left, auto & right){return left.second < right.second;});
    int yMin = positions.at(0).second;
    int yMax = positions.at(positions.size()-1).second;
    static vector<vector<char>> board ((yMax- yMin)+ 1, vector<char>(1+ (xMax- xMin), '.'));
    int sizeY = (yMax- yMin);
    int sizeX = (xMax- xMin);
    // needs to offset so that we dont work with negative values
    for (auto p : positions) {
        board[p.second - yMin][p.first - xMin] = '#';
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j];
        }
        cout << '\n';
    }
}

int main () {
    string _line;
    ifstream myfile ("init.txt");
    vector<string> data;
    vector<pair<int,int>> positions;
    vector<pair<int,int>> velocity;
    vector<int> limits (4,10); //xMin, xMax ,yMin, yMax

    if (myfile.is_open())
    {
        regex rg("(\\<(.*?)\\>)+");
        smatch sm;
        while (getline (myfile,_line) )
        {   
            while (regex_search(_line, sm, rg)) {
                for (int i = 2; i< sm.size(); i++ ) {
                    data.push_back(sm[i]);
                    _line = sm.suffix();
                }
            }
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file\n"; 
    }

    appendToVectors(positions, velocity, data);
    uint64_t originalArea = calcArea(positions, limits);
    

    uint64_t tmpArea = 0;
    uint64_t minArea = INT_MAX;
    vector<pair<int,int>> smallPos;
    int secks;
    for (int x = 0; x< 15000; x++) {
        tmpArea = calcArea(positions, limits);
        if (tmpArea < minArea) {
            minArea = tmpArea;
            smallPos = positions;
            secks = x;
        }
        calcNewPos(positions, velocity);

    }
    drawing(smallPos,limits);   
    cout << "time to wait: " << secks << endl; 
    return 0;
}