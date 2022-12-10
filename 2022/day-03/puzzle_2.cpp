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
  vector<string> lines;

  while(getline(file, line)) {
    lines.push_back(line);
  }

  for (int i = 0; i <= lines.size(); i+=3) {
    string word0 = lines[i];
    string word1 = lines[i+1];
    string word2 = lines[i+2];

    // Find the common letter in the group of three strings
    for (auto c : word0) {
      if (word1.find(c) != string::npos && word2.find(c) != string::npos) {
        sumP += (isupper(c) ? c - 'A' + 27 : c - 'a' + 1);
        break;
      }
    }
  }
 
  cout << "Sum of the priorities: " << sumP << endl;
  return 0;
}