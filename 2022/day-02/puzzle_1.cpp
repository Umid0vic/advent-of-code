// Problem: part one of https://adventofcode.com/2022/day/2

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    const char r = 'A', p = 'B', s = 'C';
    const char R = 'X', P = 'Y', S = 'Z';
    int currentS = 0, maxS = 0;

    ifstream file("game.txt");
    string line;
    
    while(getline(file, line)) {
        switch (line[0]) {
          case r:
            if (line[2] == P)
              currentS += 2+6;
            else if(line[2] == R)
              currentS += 1+3;
            else if(line[2] == S)
              currentS += 3;
            break;

          case p:
            if (line[2] == S)
              currentS += 3+6;
            else if(line[2] == P)
              currentS += 2+3;
            else if(line[2] == R)
              currentS += 1;
            break;

          case s:
            if (line[2] == R)
              currentS += 1+6;
            else if(line[2] == S)
              currentS += 3+3;
            else if(line[2] == P)
              currentS += 2;
            break;

          default:
            break;
        }
        maxS += currentS;
        currentS = 0;
    }
    
    file.close();
    cout << "Max score: " << maxS << endl;
    return 0;
}