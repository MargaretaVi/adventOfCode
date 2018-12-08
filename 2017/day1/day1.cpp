#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int calculateSum(string dataLines, string ex) {
    int sum = 0;
    char lette;
    if (ex == "part1") {
        for (int i = 0; i < dataLines.size(); i++) {
            if (i == (dataLines.size() -1) && dataLines[0] == dataLines[i]) {
                sum += stoi(to_string(dataLines[i]-'0'));
            } 
            else if (dataLines[i] == dataLines[i+1]) {
                sum += stoi(to_string(dataLines[i]-'0'));
            }
        }
    return sum;
    }
    else if (ex == "part2") {
        string line;
        int halfLength = dataLines.size()/2;

        for (string::iterator it=dataLines.begin(); it+halfLength != dataLines.end(); it++) {
            cout << "fiorst itetrator " << *it << "\n";
            cout << "second iter ator " <<*(it+halfLength) << endl;
                if (*it == *(it+halfLength))
                {
                    cout << "inhere" << endl;
                    sum += stoi(to_string(*it-'0'));
                } 
            }
        }   
    return sum*2;


        /*
        string firstHalf = dataLines.substr(0,dataLines.size()/2);
        string secondHalf = dataLines.substr(dataLines.size()/2);
        cout << "fitst " << firstHalf << "sencod " << secondHalf << endl;
        int sum = 0;

        for (string::iterator it=firstHalf.begin(); it != firstHalf.end(); it++) {
            for (string::iterator it2=secondHalf.begin(); it2 != secondHalf.end(); it2++) {
                cout << "fiorst itetrator " << *it << "\n";
                cout << "second iter ator " <<*it2 << endl;
                if (*it == *it2){
 
                    cout << "inhere" << endl;
                    sum += stoi(to_string(*it-'0'));
                } 
                }
        } */      
}

int main () {
    string _line;
    string dataLines;
    ifstream myfile ("init.txt");

    if (myfile.is_open()) {
        while (getline (myfile,_line)) {
            dataLines.append(_line);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file\n"; 
    }

    cout << "Iterating\n" << "size :" << dataLines.size() << '\n';
    //int sum = calculateSum(dataLines, "part1");
    //cout << "The total sum is: " << sum << '\n';
    int sum2 = calculateSum(dataLines, "part2");
    cout << "The total sum is: " << sum2 << '\n';
    return 0;
}

