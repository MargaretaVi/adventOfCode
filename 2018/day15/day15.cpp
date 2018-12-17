#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class unit {
    public:
    pair<int,int> pos;
    vector<pair<int,int>> walkMoves;
    vector<pair<int,int>> attacksMoves;
    int type;
    int hp;
    int attackPower = 3; // might be useless
    bool dead;

    unit(pair<int,int> pos, int type, bool dead) : pos(pos), type(type), dead(false) {};

    void findPossibleWalkMoves();
    void findPossibleAttackMoves(vector<vector<int>> board);
    void hit();
};

void unit::hit() {
    hp -= attackPower;
    if (hp < 0) {
        dead = true;
    }
}

bool possibleMove(pair<int,int> myPos, pair<int,int> newpos) {
    return myPos == newpos;
}
void unit::findPossibleAttackMoves(vector<vector<int>> board) {
    // top, right, down, left
    walkMoves.clear();
    pair<int,int> tmp;
    pair<int,int> newUp = pair<int,int> (pos.first--, pos.second);
    pair<int,int> newRight = pair<int,int> (pos.first, pos.second++);
    pair<int,int> newDown = pair<int,int> (pos.first++, pos.second);
    pair<int,int> newLeft = pair<int,int> (pos.first, pos.second--);

    //up
    tmp = newUp;
    bool walkable = possibleMove(pos, newUp);
    if (walkable) {
        walkMoves.push_back(tmp);
    }

    //right
    tmp = newRight;
    walkable = possibleMove(pos, newRight);
    walkMoves.push_back(tmp);

    //down
    tmp = newDown;
    walkable = possibleMove(pos, newDown);
    walkMoves.push_back(tmp);

    //left
    tmp = newLeft;
    walkable = possibleMove(pos, newLeft);
    walkMoves.push_back(tmp);
    


}

void drawBoard(vector<vector<int>> board) {
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board.at(row).size(); col++) {
            cout << board[row][col];
        }
    cout << '\n';
}

}
int main() {
    vector<vector<int>> board(32, vector<int>(32, 0));
    vector<unit> goblinsVec;
    vector<unit> elvesVec;
    vector<unit> emptySpaceVec;

    // creating map
    string _line;
    ifstream myfile("init.txt");
    int row =0;
    int col;
    if (myfile.is_open()) {
        while (getline (myfile,_line) ) {
            col = 0;
            for (auto character : _line) {   
                switch (character) {
                    // unneccesary since the board is initalized with '#'
                    /*case '#':
                        unit(pair<int,int> (row,col), 0);
                        board[row][col] = '#';*/
                    case '.':
                        board[row][col] = 3;
                        emptySpaceVec.push_back(unit(pair<int,int> (row,col), 3));
                        break;
                    case 'G':
                        board[row][col] = 2;
                        goblinsVec.push_back(unit(pair<int,int> (row,col), 2));
                        break;
                    case 'E':
                        board[row][col] = 1;
                        elvesVec.push_back(unit(pair<int,int> (row,col), 1));
                        break;
                    default:    
                        break;
                }
                col++;
            }
            row++;
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file\n"; 
    }
    // drawing Board
    drawBoard(board);

    return 0;
}
