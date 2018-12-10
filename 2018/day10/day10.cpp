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

int calcArea(vector<pair<int,int>> newPos, vector<int> &limits) {
    // sort on x values first
    sort(newPos.begin(), newPos.end(), [](auto & left, auto & right){return left.first < right.first;});
    int area;
    limits.at(0) = newPos.at(0).first;
    limits.at(1) = newPos.at(newPos.size()-1).first;
    //n sort on y values
    sort(newPos.begin(), newPos.end(), [](auto & left, auto & right){return left.second < right.second;});
    limits.at(2) = newPos.at(0).second;
    limits.at(3) = newPos.at(newPos.size()-1).second;
    return abs(limits[0]- limits[1]) * abs(limits[2]-limits[3]);

}

void clearBoard(vector<vector<char>> &board) {
    for (auto y = 0; y < board.size(); y++) {
        for (auto x = 0; x < board[y].size(); x++) {
            board[y][x] = '.';
        }
    }
}

void drawing(vector<pair<int,int>> &positions, vector<int> limits, vector<vector<char>> &board) {
    int xMin = limits[0];
    int xMax = limits[1];

    int yMin = limits[2];
    int yMax = limits[3];

    // needs to offset so that we dont work with negative values
    for (auto p : positions) {;
        board[p.second + abs(yMin)][p.first + abs(xMin)] = '#';
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j];
        }
        cout << '\n';
    }
    cout << "this is the final size of the coordiantes. " << positions.size() << endl;
}

int main () {
    string _line;
    ifstream myfile ("test.txt");
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
    auto originalArea = calcArea(positions, limits);
    static vector<vector<char>> board ((limits[3]- limits[2]) + 10 , vector<char>( 10 +(limits[1] - limits[0]), '.'));

    drawing(positions,limits, board); 
    clearBoard(board);

   
   for(auto i = 0; i< 5 ; i++) {
        calcNewPos(positions, velocity);
        drawing(positions,limits,board);  
        clearBoard(board);
    }

    //drawing(positions,limits);   

    return 0;
}