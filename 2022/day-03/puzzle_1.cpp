// Problem: https://adventofcode.com/2022/day/3#part2

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {

  int sumP = 0;

  ifstream file("game.txt");
  string line;
  int ifs = 0;

  while (getline(file, line)) {
    int len = line.length();
    string word1 = line.substr(0, len/2 );
    string word2 = line.substr(len/2);

    // Find the shared item
    for (auto c : word1) {
      if (word2.find(c) != string::npos) {
        int(c) <= 'Z' ? sumP += int(c)-'A'+27 : sumP += int(c)-'a'+1;
        break;
      }
    }
  }
 
  cout << "Sum of the priorities: " << sumP << endl;
  return 0;
}