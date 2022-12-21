// Puzzle from https://adventofcode.com/2022/day/9

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Struct to represent a position on the grid
struct position {
  int x, y;
  position(int xx, int yy) : x(xx), y(yy) {}
};

vector<position> makeMove(const vector<pair<char, int>>& moves, position& head, position& tail) {
  int stepsCount = 0;
  vector<position> visitedPositions;
  for (const auto& [dir, steps] : moves) {
    for (int i = 0; i < steps; i++) {
      cout << dir << " " << steps << endl;

      if (dir == 'U') {
        head.y++;
      } else if (dir == 'D') {
        head.y--;
      } else if (dir == 'L') {
        head.x--;
      } else if (dir == 'R') {
        head.x++;
      }
       // Check if the head and tail are diagonally one step away
      bool isDiagonallyAdjacent = abs(head.x - tail.x) == 1 && abs(head.y - tail.y) == 1;

      if (!isDiagonallyAdjacent) {
        if (head.x != tail.x && head.y != tail.y) {
          // Head and tail are not in the same row or column and are not touching, so move tail one step diagonally
          if (head.x > tail.x) {
            if (head.y > tail.y) {
              tail.x++;
              tail.y++;
            } else {
              tail.x++;
              tail.y--;
            }
          } else {
            if (head.y > tail.y) {
              tail.x--;
              tail.y++;
            } else {
              tail.x--;
              tail.y--;
            }
          }
        } else if (abs(head.x - tail.x) > 1 || abs(head.y - tail.y) > 1) {
          // Head is more than one step away from tail, so move tail one step in the same direction as head
          if (head.x > tail.x) {
            tail.x++;
          } else if (head.x < tail.x) {
            tail.x--;
          } else if (head.y > tail.y) {
            tail.y++;
          } else if (head.y < tail.y) {
            tail.y--;
          }
        }
      } else {
        cout << "digonallyAdjacent " << endl;
      }
      // Check if the current position of the tail is already in the visitedPositions vector
      bool isUnique = true;
      for (const auto& pos : visitedPositions) {
        if (pos.x == tail.x && pos.y == tail.y) {
          isUnique = false;
          break;
        }
      }
      // If the current position is unique, add it to the visitedPositions vector
      if (isUnique) {
        visitedPositions.push_back(tail);
      }
      cout << "head {" << head.x << " , " << head.y << "}" << endl;
      cout << "tail {" << tail.x << " , " << tail.y << "}" << endl;
    }
  }
  return visitedPositions;
}


int main() {

  ifstream file("file.txt");
  string line;
  vector<pair<char, int>> moves;
  // Initialize the head and tail positions to be the same
  position tail(0, 0);
  position head(0, 0);

  while (getline(file, line)) {
    pair<char, int> move;

    move.first = line[0];
    move.second = stoi(line.substr(2));
    moves.push_back(move);
  }

  vector<position> visitedPositions = makeMove(moves, head, tail);

  cout << visitedPositions.size();

  return 0;
}
