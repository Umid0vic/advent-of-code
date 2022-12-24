// Puzzle from https://adventofcode.com/2022/day/10

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Class representing a CRT screen
class CRT {
public:
  // Update the CRT screen with a '#' at the current cycle position
  void updateCRT() {
    // 240 = number of pixels on the screen
    const int pixelId = (this->cycle -1) % 240;
    const int pixelRaw = pixelId / 40;
    const int pixelCol = pixelId % 40;

    if (abs(pixelCol - this->x) <= 1) {
      this->screen[pixelRaw][pixelCol] = '#';
    }
  }

  // Increment the cycle and update the signal strength if necessary
  void updateCycle() {
    this->cycle++;
    this->updateCRT();
    if ((this->cycle - 20) % 40 == 0) {
      this->signalStrength += this->cycle * this->x;
    }
  }

  // Add the value to x and update the cycle and signal strength
  void addX(int value) {
    this->updateCycle();
    this->updateCycle();
    this->x += value;
  }

  // Return a copy of the screen vector
  vector<string> getScreen() const {
    return this->screen;
  }

  int getSignalStrength() const {
    return this->signalStrength;
  }


private:
  int cycle = 0;
  // Vector representing the CRT screen, with '.' representing an empty pixel
  vector<string> screen = vector<string>(6, string(40, '.'));
  int x = 1;
  int signalStrength = 0;
};

int main() {
  ifstream file("input.txt");
  string instruction;
  // Create a CRT object
  CRT crt;

  // Read each line of the input file and execute the corresponding instruction.
  while (getline(file, instruction)) {
    const int space = instruction.find(' ');
    const string ins = instruction.substr(0, space);

    if (ins == "noop") {
      crt.updateCycle();
    } else if (ins == "addx") {
      // Add the value to x and update the cycle and signal strength
      int value = stoi(instruction.substr(space + 1));
      crt.addX(value);
    }
  }
  // Get the screen vector and print it
  vector<string> screen = crt.getScreen();
  for (const auto& row : screen) {
    cout << row << endl;
  }
  
  cout << endl << "The total signal strength : " << crt.getSignalStrength() << endl;
  return 0;
}