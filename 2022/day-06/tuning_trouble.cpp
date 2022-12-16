// problem: https://adventofcode.com/2022/day/6

#include <iostream>
#include <set>
#include <fstream>
using namespace std;

// Returns the position of the first start-of-packet marker in the given buffer
int findMarker(std::string buffer) {
  string lastFour;
  for (int i = 0; i < buffer.length(); i++) {
    lastFour += buffer[i];
    if (lastFour.length() > 4) {
      lastFour.erase(0, 1);
    }
    // If lastFour has 4 characters and they are all different, return the current position
    if (lastFour.length() == 4 && set<char>(lastFour.begin(), lastFour.end()).size() == 4) {
      return i+1;
    }
  }
  // If the loop completes and no marker was found
  return -1;
}

int main() {
  string line;
  ifstream file("datastream.txt");

  getline(file, line);
  cout << findMarker(line) << std::endl;
  
  return 0;
}
