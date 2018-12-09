#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

int main() {

    string _line;
    vector<int> gameInfo;
    ifstream myfile ("init.txt");

    if (myfile.is_open())
    {
        while (getline (myfile,_line) )
        {
            stringstream ss(_line);     

            /* Running loop till the end of the stream */
            string temp; 
            int found; 
            while (!ss.eof()) { 
                /* extracting word by word from stream */
                ss >> temp; 
                /* Checking the given word is long long 
        ger or not */
                if (stringstream(temp) >> found) 
                    gameInfo.push_back(found);
                /* To save from space at the end of string */
            } 
                myfile.close();
        }
    }
    else {
        cout << "Unable to open file\n"; 
    }


    int players = gameInfo[0];  
    map<int,uint64_t> scores;

    // init all values to 0 so that we can increment the score later
    for (int i = 1; i <= players; i++) {
        scores[i] = 0;
    }

    long rounds = gameInfo[1];
    int currentMarble;
    int pos = 0;
    int playerNr = 1;
    uint64_t score = 0;
    vector<int> circle = {0}; // playing board
    circle.reserve(rounds);

    for (auto r = 1; r <= rounds; r++) {
        cout << "this might be stupid buit... " << r << endl;
        currentMarble = r;

        if (currentMarble % 23 == 0) {
            score += currentMarble;
            //cout << "current pos is_ " << pos << endl;
            long newTmpPos = pos - 7;
            if (newTmpPos >= 0) {
                //cout << "nre tmp pos is : " << newTmpPos << endl;
                // we can go back 7 steps
                //cout << "this is the current pos_ "<< pos << endl;
                pos -= 7;
                //cout << "this is the new pos " << pos << endl;
            }
            else {
                // loop around 
                //cout << "looping\n";
                pos = circle.size() + newTmpPos;
            }
            //cout << "scoire: " << score << " adding this much to the score_ " << circle[pos] << " the new position is " << pos <<  endl;
            score += circle[pos];
            circle.erase(circle.begin() + pos );
            currentMarble = circle[pos];
        } 

        else {
            pos ++;
            if (pos == circle.size()) {
                pos = 0;
            }
            pos ++;
            circle.emplace(circle.begin() + pos, currentMarble);
        }

/*
         // Visualizsation
        cout << "[" << r << "] ";
        for (auto g : circle) {
            if (g == currentMarble) {
                cout << "(" << g << ")";
            } 
            else {
                cout << " " << g << " "; 
            }
        }
                cout << "\n";
*/

        scores[playerNr] += score;
        playerNr ++;
        if (playerNr > players) {
            playerNr = 1;
        }
        score = 0;   
    } 
    int tmpWinner = 0;
    uint64_t tmpScore = 0;
    for (auto score : scores) {
        cout << "Player: " << score.first << " had this score: " << score.second << endl; 
        if (score.second > tmpScore) {
            tmpScore = score.second;
            tmpWinner = score.first;
        }
    }
    cout << "The winning player is: " << tmpWinner << " With the score: " << tmpScore << endl;
    return 0;
}