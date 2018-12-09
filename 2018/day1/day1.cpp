#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


int main() {
    /* Open File and add it to vector. */
    string _line;
    vector<int> dataLines;
    ifstream myfile ("test.txt");
    if (myfile.is_open())
    {
        while (getline (myfile,_line) )
        {
            dataLines.push_back(stoi(_line));
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file\n"; 
    }
    uint32_t result_freq = 0;
    map<uint32_t,uint32_t> result_map;
    while (true) {
        int loops = 0;
        for (auto freq : dataLines) {
            result_freq += freq;
            if (result_map.find(result_freq) != result_map.end()) {
                cout << "Part 2: Frequency is " << result_freq << " this many loops: " << loops << '\n'; 
                return 0;
            }
            else {
                result_map[result_freq];
            }
            loops ++;
        }
    }
    cout << "Part 1: " << result_freq << '\n';
    return 0;
}