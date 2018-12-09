#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    string _line;
    vector<string> preReq;
    vector<string> instruction;
    vector<string> instructionOrder;
    ifstream myfile("init.txt");

    if (myfile.is_open()) {
        while (getline (myfile,_line)) {
            preReq.push_back(string(1,_line[5]));
            instruction.push_back(string(1,_line[36]));
        }
        myfile.close();
        }
    else cout << "Unable to open file"; 

    vector<string> reserveInstructionList = instruction;

    //find all possible moves 
    vector<string> possibleMoves;
    vector<int> indexHolder;

    string lastInstruction;

    while (!preReq.empty()) {
        cout << "list has been pooped: current size: " << preReq.size() << endl; 
        possibleMoves.clear();

        for (auto index = 0; index < preReq.size(); index ++) {
            string possibleInstr = preReq[index];
            if (find(instruction.begin(), instruction.end(), possibleInstr) == instruction.end()) {
                possibleMoves.push_back(possibleInstr);
            }
        }

        // sorting the list to get the first possible move 
        sort(possibleMoves.begin(), possibleMoves.end());
        possibleMoves.erase(unique(possibleMoves.begin(), possibleMoves.end()), possibleMoves.end());

        string currentInstruction = possibleMoves[0];
        instructionOrder.push_back(currentInstruction);

        // finding all the indices of this move.
        indexHolder.clear(); 
        for (int i = 0; i < preReq.size(); i++) {
            if (preReq[i] == currentInstruction){
                indexHolder.push_back(i);
            }
        }
        for (auto i : indexHolder) { 
            instruction.erase(instruction.begin() + i);
        }
        preReq.erase(remove(preReq.begin(),preReq.end(), currentInstruction), preReq.end());
    }

    // adding the last instruction!
    for (vector<string>::iterator iter = reserveInstructionList.begin(); iter != reserveInstructionList.end(); iter++) {
        if (find(instructionOrder.begin(), instructionOrder.end(), *iter) == instructionOrder.end()) {
            instructionOrder.push_back(*iter);
        }
    }

    cout << "this is the order: \n";
    for (auto instr: instructionOrder) {
        cout << instr;
    }

    return 0;
}

