#include <vector>
#include <iostream>
using namespace std;

void drawVector(vector<int> recepieList, uint64_t elf1, uint64_t elf2) {
   for (uint64_t index = 0; index < recepieList.size(); index++){
        if (index == elf1) {
           cout << "(" << recepieList.at(elf1) << ") ";
       }
        else if (index == elf2) {
           cout << "[" << recepieList.at(elf2) << "] ";
       }
       else {
           cout << recepieList.at(index)  << " ";
       }
   }
    cout << '\n';
}


void addToList(vector<int> &recepieList, int sum, uint64_t &elf1, uint64_t &elf2) {

    if (sum < 10) {
        recepieList.push_back(sum);
        //drawVector(recepieList, elf1, elf2);
    } 
    else {
        int firstValue = sum/10;
        int secondValue = sum % 10;
        recepieList.push_back(firstValue);
        recepieList.push_back(secondValue);
    }

    int step1 = recepieList.at(elf1) + 1;
    int step2 = recepieList.at(elf2) + 1;

    //cout << " sum: " << sum << " Steps: " << step1 << " " << step2 << '\n';
    // do check if looping zaroun

    while (step1 > 0) {
        elf1 += 1;
        if (elf1 == recepieList.size()) {
            elf1 = 0;
        }
        --step1;
    }

    // elf2
    while (step2 > 0) {
        elf2 += 1;
        if (elf2 == recepieList.size()) {
            elf2 = 0;
        }
        step2--;
    }
  
}

int main() {    
    int numRecepiesStart = 607331;
    int iteration = numRecepiesStart + 10;

    //int numRecepiesStart = 18;
    //int iteration = numRecepiesStart + 10;

    vector<int> recepieList;
    recepieList.push_back(3);
    recepieList.push_back(7);
    uint64_t elf1 = 0;
    uint64_t elf2 = 1;

    int sum;

    // part1
    /*
    for(int it = 1; it <= iteration; it++) {
        //cout << "Iteration: " << it << endl;;
        sum = recepieList.at(elf1) + recepieList.at(elf2);
        addToList(recepieList, sum, elf1, elf2);
        //drawVector(recepieList, elf1, elf2);
    }

    for (int i = numRecepiesStart; i < iteration; i++) {
        cout << recepieList[i];
    }*/

    //part2
    vector<int> match = {6,0,7,3,3,1};
    //vector<int> match = {5,1,5,8,9};
    //vector<int> match = {0,1,2,4,5};
    //vector<int> match = {9,2,5,1,0};
    bool mat = false;
    int index = 0;
    while(!mat) {
        //cout << "interation numner : " << index << endl;
        sum = recepieList.at(elf1) + recepieList.at(elf2);
        addToList(recepieList, sum, elf1, elf2);
        if (recepieList.size() < match.size()) {
            index++;
            continue;
        } 
        else {
            //cout << "comparing!" << endl;
            for (auto i = 0; i < match.size(); i++) {
                mat = false;
                if (match.at(i) == recepieList.at(index + i)) {
                    mat = true;
                }
                else {
                    break;
                }
            }
            index++;
        }
    }
    cout << "The index is: " << index << endl;
}