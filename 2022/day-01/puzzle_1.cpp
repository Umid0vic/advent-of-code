#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int currentC = 0, maxC = 0, topElf;
    ifstream file("colories.txt");
    string line;
    vector<vector<int>> elfs;
    vector<int> colories;
    
    while(getline(file, line)) {
        if ( line == ""){
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
        if (currentC > maxC) {
            maxC = currentC;
            topElf = i+1;
        }
        currentC = 0;
    }
    
    file.close();
    cout << "Elf " << topElf << " has the most colories: " << maxC << endl;
    return 0;
}