// problem: https://adventofcode.com/2022/day/6

#include <iostream>
#include <set>
#include <fstream>
using namespace std;

// Returns the position of the first start-of-packet marker in the given buffer
int findStartOfPacket(string buffer) {
  for (int i = 0; i < buffer.length() - 3; i++) {
    string substr = buffer.substr(i, 4);
    // If the last 4 characters are all different, return the position of the fourth character
    if (set<char>(substr.begin(), substr.end()).size() == 4) {
      return i+4;
    }
  }
  // If the loop completes and no marker was found
  return -1;
}

// Returns the position of the first start-of-message marker in the given buffer
int findStartOfMessage(string buffer) {
  for (int i = 0; i < buffer.length() - 13; i++) {
    string substr = buffer.substr(i, 14);
    // If the last 14 characters are all different, return the position of the fourteenth character
    if (set<char>(substr.begin(), substr.end()).size() == 14) {
      return i+14;
    }
  }
  return -1;
}

int main() {
  string line;
  ifstream file("datastream.txt");
  getline(file, line);
  // Get the start-of-packet
  cout << "The start-of-packet marker is detected at position : " << findStartOfPacket(line) << std::endl;
  // Get the start-of-message
  cout << "The start-of-message marker is detected at position : " << findStartOfMessage(line) << std::endl;
  
  return 0;
}
