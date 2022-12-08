// Problem: part one of https://adventofcode.com/2022/day/2

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    const char R = 'A', P = 'B', S = 'C';
    const char X = 'X', Y = 'Y', Z = 'Z';
    int currentS = 0, maxS = 0;

    ifstream file("game.txt");
    string line;
    
    while(getline(file, line)) {
        switch (line[2]) {
          case X:
            if (line[0] == R)
              currentS += 3;
            else if(line[0] == P)
              currentS += 1;
            else if(line[0] == S)
              currentS += 2;
            break;

          case Y:
            if (line[0] == R)
              currentS += 1+3;
            else if(line[0] == P)
              currentS += 2+3;
            else if(line[0] == S)
              currentS += 3+3;
            break;

          case Z:
            if (line[0] == R)
              currentS += 2+6;
            else if(line[0] == P)
              currentS += 3+6;
            else if(line[0] == S)
              currentS += 1+6;
            break;

          default:
            break;
        }
        maxS += currentS;
        currentS = 0;
    }
    
    file.close();
    cout << "max score :" << maxS << endl;
    return 0;
}