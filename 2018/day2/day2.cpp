#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

bool twice(string line) {
    for (auto c : line) {
        if (std::count(line.begin(), line.end(), c) == 2)
        {
            return true;
        }
    }
    return false;
}

bool trice(string line) {
    for (auto c : line) {
        if (std::count(line.begin(), line.end(), c) == 3)
        {
            return true;
        }
    }
    return false;
}

uint32_t part1(vector<string> dataLines) {
    uint32_t twiceInLine = 0;
    uint32_t triceInLine = 0;
    for (auto line : dataLines) {
            
        if (twice(line)) {
            twiceInLine ++;
        }
        if (trice(line)) {
            triceInLine ++;
        }
    }
    uint32_t checksum = twiceInLine * triceInLine;
    cout << "The check sum is: " << checksum << '\n';
}

int main() {

    /* Open File and add it to vector. */
    string _line;
    vector<string> dataLines;
    ifstream myfile ("init.txt");
    if (myfile.is_open())
    {
        while (getline (myfile,_line) )
        {
            dataLines.push_back(_line);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file\n"; 
    }
    //part1(dataLines);
    for (auto l : dataLines) {
        for (auto m : dataLines) {
            // count differing letters
            auto d = 0;
            auto it1 = begin(l);
            auto it2 = begin(m);
            for (;it1!=end(l);++it1,++it2) {
                if (*it1!=*it2) d++;
            }
            if (d==1) {
                cout << "Words: " << l << "\n";
                exit(0);
            }
        }
    }

    return 0;
}

//kbqwtcvzhmhpoelrnaxydifyb
//kbqwtcvzhsmhpoelrnaxydifyb
//kbqwtcvzhsmhpoelrnaxydifybxydifyb