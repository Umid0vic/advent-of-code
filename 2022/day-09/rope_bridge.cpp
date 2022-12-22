// Puzzle from https://adventofcode.com/2022/day/9

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

// Struct to represent a position on the grid
struct position {
  int x, y;
  position(int xx, int yy) : x(xx), y(yy) {}
};

/**
 * Calculates the positions that the tail visits while moving based on the provided moves of the head.
 * @param moves A vector of pairs representing the moves of the head. 
 * Each pair consists of a character representing the direction (U, D, L, or R) 
 * and an integer representing the number of steps in that direction.
 * @param head A reference to the position of the head.
 * @param tail A reference to the position of the tail.
 * @return A map of pairs of integers representing the positions that the tail visited, 
 * with the characters '#' and 's' indicating the positions visited by the tail and the starting position, respectively.
 */

map<pair<int, int>, char> makeMove(const vector<pair<char, int>>& moves, position& head, position& tail) {

  map<pair<int, int>, char> visitedPositions;
  for (const auto& [dir, steps] : moves) {
    for (int i = 0; i < steps; i++) {
      // Update the head position based on the direction of the move
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
      }
      // Add the current tail position to the map of visited positions
      visitedPositions[{tail.x, tail.y}] = '#';
    }
  }
  visitedPositions[{0, 0}] = 's';
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

  // Calculate the visited positions
  map<pair<int, int>, char> visitedPositions = makeMove(moves, head, tail);

  // Determine the minimum and maximum x and y coordinates of the visited positions
  int minX = 0, maxX = 0, minY = 0, maxY = 0;
  for (const auto& [pos, c] : visitedPositions) {
    minX = min(minX, pos.first);
    maxX = max(maxX, pos.first);
    minY = min(minY, pos.second);
    maxY = max(maxY, pos.second);
  }

  // Print the grid to the console
  for (int y = maxY; y >= minY; y--) {
    for (int x = minX; x <= maxX; x++) {
      if (visitedPositions.count({x, y}) == 0) {
        cout << '.';
      } else {
        cout << visitedPositions[{x, y}];
      }
    }
    cout << endl;
  }
  return 0;
}