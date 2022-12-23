// Puzzle from https://adventofcode.com/2022/day/10

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Function to execute a single instruction and update the cycle, X register, and signal strength
void executeInstruction(string instruction, int& cycle, int& x, int& signalStrength) {
  // If the instruction is "noop", increment the cycle and update the signal strength if necessary
  if (instruction == "noop") {
    cycle++;
    if (cycle % 40 == 20) {
      signalStrength += (cycle * x);
      cout << "cycle: " << cycle << " signalS: " << cycle * x << endl;
    }
  // If the instruction is "addx V", increment the cycle twice and update the X register and signal
  // strength as necessary
  } else {
    size_t pos = instruction.find(' ');
    int v = stoi(instruction.substr(pos + 1));
    cycle++;
    if (cycle % 40 == 20) {
      signalStrength += cycle * x;
      cout << "cycle: " << cycle << " signalS: " << cycle * x<< endl;
    }
    cycle++;
    if (cycle % 40 == 20) {
      signalStrength += (cycle * x);
      cout << "cycle: " << cycle << " signalS: " << cycle * x << endl;
    }
    x += v;
  }
}

int main() {

  ifstream file("input.txt");
  string instruction;
  vector<string> lines;
  int x = 1, cycle = 0, signalStrength = 0;
  // Read the instructions from the input file one line at a time
  while (getline(file, instruction)) {
    executeInstruction(instruction, cycle, x, signalStrength);
  }
  
  cout << "the total signal strength : " << signalStrength << endl;
  return 0;
}
