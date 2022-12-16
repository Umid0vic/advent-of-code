// problem: https://adventofcode.com/2022/day/5

#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <regex>
#include <stdexcept>

using namespace std;

// Moves the crates indivudually from the source stack to the destination stack.
// If the source stack does not contain enough crates, an error message is printed.
void moveElementsIndividually(int crateToMove, int sourceStack, int destinationStack, deque<deque<char>>& stacks) {
  // Check if the source and destination stacks exist
  if (sourceStack >= 0 && sourceStack < stacks.size() && destinationStack >= 0 && destinationStack < stacks.size()) {
    if (crateToMove <= stacks[sourceStack].size()) {
      // Move crates from source stack to destination stack
      cout << "moving crate from stack " << sourceStack+1 << " to stack " << destinationStack+1 << endl;
      for (int i = 0; i < crateToMove; i++) {
        stacks[destinationStack].push_front(stacks[sourceStack].front());
        if (!stacks[sourceStack].empty()) {
          stacks[sourceStack].pop_front();
        }
      }
    } else {
      cout << "Error: Cannot move " << crateToMove << " crates from stack " << sourceStack+1 << " because it only contains " << stacks[sourceStack].size() << " crates" << endl;
    }
  } else {
    cout << "Error: Invalid stack specified" << endl;
  }
}

// Moves multiple crates from the source stack at once to the destination stack.
void moveElementsAtOnce(int crateToMove, int sourceStack, int destinationStack, deque<deque<char>>& stacks) {
  // Check if the source and destination stacks exist
  if (sourceStack >= 0 && sourceStack < stacks.size() && destinationStack >= 0 && destinationStack < stacks.size()) {
    if (crateToMove <= stacks[sourceStack].size()) {
      deque<char> tempStack;
      for (int i = 0; i < crateToMove; i++) {
        tempStack.push_front(stacks[sourceStack].front());
        if (!stacks[sourceStack].empty()) {
          stacks[sourceStack].pop_front();
        }
      }
      // Move crates from source stack to destination stack
      cout << "moving crate from stack " << sourceStack+1 << " to stack " << destinationStack+1 << endl;
      for (int i = 0; i < crateToMove; i++) {
        stacks[destinationStack].push_front(tempStack.front());
        if (!tempStack.empty()) {
          tempStack.pop_front();
        }
      }
    } else {
      cout << "Error: Cannot move " << crateToMove << " crates from stack " << sourceStack+1 << " because it only contains " << stacks[sourceStack].size() << " crates" << endl;
    }
  } else {
    cout << "Error: Invalid stack specified" << endl;
  }
}

int main() {
  deque<deque<char>> stacks;
  string line;
  ifstream file("supply_stacks.txt");
  bool isFirstLine = true;
  regex regex("move (\\d+) from (\\d+) to (\\d+)");
  smatch match;
  int vIndex = 0;
  
  while (getline(file, line)) {
    if (regex_match(line, match, regex)) {
      try {
        int crateToMove = stoi(match[1]);
        int sourceStack = stoi(match[2]) -1;
        int destinationStack = stoi(match[3]) -1;
        // Test functions
        moveElementsIndividually(crateToMove, sourceStack, destinationStack, stacks);
      } catch (const invalid_argument& e){
        cout << "Error: Invalid argument" << endl;
      }
    } else {
      for (int i = 1; i <= line.length(); i+=4) {
        char c = line[i];
        if (isFirstLine) {
          deque<char> stack;
          stacks.push_back(stack);
        }
        if (!stacks.empty() && (c >= 'A' && c <= 'Z')) {
          stacks[vIndex].push_back(c);
          cout << "adding to stack " << vIndex+1 << " : " << c << endl;
        }
        vIndex++;
      }
      vIndex = 0;
      isFirstLine = false;
    }
  }

  cout << "Output the top crates of each stack." << endl;
  for (int i = 0; i < stacks.size(); i++) {
    cout << stacks[i].front() << endl;
  }

  return 0;
}
