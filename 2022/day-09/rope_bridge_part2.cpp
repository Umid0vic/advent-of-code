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
  position(int xx = 0, int yy = 0) : x(xx), y(yy) {}  // Default constructor
};

map<pair<int, int>, char> makeMove(const vector<pair<char, int>>& moves, position& head, vector<position>& tail) {
  map<pair<int, int>, char> visitedPositions;

  // Initialize the tail with 9 parts
  tail.resize(9);
  for (int i = 0; i < 9; i++) {
    tail[i] = {0, 0};
  }

  for (const auto& [dir, steps] : moves) {
    cout << dir << " " << steps << endl;
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
      bool isDiagonallyAdjacent = abs(head.x - tail[0].x) == 1 && abs(head.y - tail[0].y) == 1;

      if (!isDiagonallyAdjacent) {
        if (head.x != tail[0].x && head.y != tail[0].y) {
          // Head and tail are not in the same row or column and are not touching, so move tail one step diagonally
          if (head.x > tail[0].x) {
            if (head.y > tail[0].y) {
              tail[0].x++;
              tail[0].y++;
            } else {
              tail[0].x++;
              tail[0].y--;
            }
          } else {
            if (head.y > tail[0].y) {
              tail[0].x--;
              tail[0].y++;
            } else {
              tail[0].x--;
              tail[0].y--;
            }
          }
        } else if (abs(head.x - tail[0].x) > 1 || abs(head.y - tail[0].y) > 1) {
          // Head is more than one step away from tail, so move tail one step in the same direction as head
          if (head.x > tail[0].x) {
            tail[0].x++;
          } else if (head.x < tail[0].x) {
            tail[0].x--;
          } else if (head.y > tail[0].y) {
            tail[0].y++;
          } else if (head.y < tail[0].y) {
            tail[0].y--;
          }
        }
        
        for (int j = 0; j < 8; j++) {
          
          bool isDiagonallyAdj = abs(tail[j].x - tail[j+1].x) == 1 && abs(tail[j].y - tail[j+1].y) == 1;
          
          if(!isDiagonallyAdj) {
            if (tail[j].x != tail[j+1].x && tail[j].y != tail[j+1].y) {
              // tail[j] and tail[j+1] are not in the same row or column and are not touching, so move tail one step diagonally
              if (tail[j].x > tail[j+1].x) {
                if (tail[j].y > tail[j+1].y) {
                  tail[j+1].x++;
                  tail[j+1].y++;
                } else {
                  tail[j+1].x++;
                  tail[j+1].y--;
                }
              } else {
                if (tail[j].y > tail[j+1].y) {
                  tail[j+1].x--;
                  tail[j+1].y++;
                } else {
                  tail[j+1].x--;
                  tail[j+1].y--;
                }
              }
            } else if (abs(tail[j].x - tail[j+1].x) > 1 || abs(tail[j].y - tail[j+1].y) > 1) {
              // tail[j] is more than one step away from tail, so move tail one step in the same direction as tail[j]
              if (tail[j].x > tail[j+1].x) {
                tail[j+1].x++;
              } else if (tail[j].x < tail[j+1].x) {
                tail[j+1].x--;
              } else if (tail[j].y > tail[j+1].y) {
                tail[j+1].y++;
              } else if (tail[j].y < tail[j+1].y) {
                tail[j+1].y--;
              }
            }
          }

          visitedPositions[{tail[8].x, tail[8].y}] = '#';
        }
          cout << "H  " << head.x << ' ' << head.y << endl;
          cout << "1  " << tail[0].x << ' ' << tail[0].y << endl;
          cout << "2  " << tail[1].x << ' ' << tail[1].y << endl;
          cout << "3  " << tail[2].x << ' ' << tail[2].y << endl;
          cout << "4  " << tail[3].x << ' ' << tail[3].y << endl << endl;
      }
    }
  }
  visitedPositions[{0, 0}] = 's';
  return visitedPositions;
}


int main() {

  ifstream file("file.txt");
  string line;
  vector<pair<char, int>> moves;
  vector<position> tails;
  // Initialize the head and tail positions to be the same
  position tail(0, 0);
  position head(0, 0);
  tails.push_back(tail);

  while (getline(file, line)) {
    pair<char, int> move;

    move.first = line[0];
    move.second = stoi(line.substr(2));
    moves.push_back(move);
  }
  
  // Calculate the visited positions
  map<pair<int, int>, char> visitedPositions = makeMove(moves, head, tails);

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

  cout << visitedPositions.size();
  return 0;
}