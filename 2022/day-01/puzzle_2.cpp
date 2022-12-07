#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int currentC = 0, firstElf = 0, secondElf = 0, thirdElf = 0, sum;
    ifstream file("colories.txt");
    string line;
    vector<vector<int>> elfs;
    vector<int> colories;
    
    while(getline(file, line)) {
        if (line == ""){
            elfs.push_back(colories);
            colories.clear();
        }
        else {
            colories.push_back(stoi(line));
        }
    }
    elfs.push_back(colories);
    
    for (int i = 0; i < elfs.size(); i++) {
        for (int j = 0; j < elfs[i].size(); j++) {
            currentC += elfs[i][j];
        }
        if (currentC > firstElf) {
          secondElf = firstElf;
          firstElf = currentC;
        }else if (currentC > secondElf) {
          thirdElf = secondElf;
          secondElf = currentC;
        }else if (currentC > thirdElf) {
          thirdElf = currentC;
        }
        currentC = 0;
    }

    file.close();
    sum = firstElf + secondElf + thirdElf;
    cout << "Sum of top three colories: " << sum << endl;

    return 0;
}