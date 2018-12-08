#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

string removeLetter(char c, string str) {
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
    str.erase(std::remove(str.begin(), str.end(), toupper(c)), str.end());
    return str;
}

void doStuff(string &list) {
    string::iterator myIterator;
    bool ListClean = false;
    while(!ListClean)
    {
        ListClean = true;
        myIterator = list.begin();
        while(myIterator != list.end())
        {
            // same letter & different cases
            if(tolower(*(myIterator+1)) == tolower(*myIterator) && (*(myIterator + 1) != *myIterator))
            {
                /* remove items! */
                list.erase(myIterator,myIterator+2);
                ListClean = false;
                }
            else 
            {
                myIterator++;
            }

        }
    }
}
int main() {
    cout << "starting with day 5 \n";
    string _line;
    string dataLines;
    ifstream myfile("init.txt");

    // file only contains one LOOONG line
    if (myfile.is_open()) {
        while (getline (myfile,_line)) {
            dataLines = _line;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    uint32_t polymerLenght = dataLines.size();
    for (auto letter : alphabet) {
        string modi = removeLetter(letter, dataLines);
        doStuff(modi);
        if (modi.size() < polymerLenght) {
            polymerLenght = modi.size();
        }

    }

    cout << dataLines.size() << '\n';
    doStuff(dataLines);
    cout << dataLines << '\n';
    cout << dataLines.size() << '\n';
    cout << polymerLenght << '\n';

    return 0;
}