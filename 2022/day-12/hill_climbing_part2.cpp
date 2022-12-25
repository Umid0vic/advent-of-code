// Puzzle from https://adventofcode.com/2022/day/12

#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

// Array to store the offsets for moving up, down, left, and right
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

// Node struct to store the distance and position of a cell
struct Node {
  int distance;
  pair<int, int> pos;
};

// Comparison function to prioritize nodes with lower distances
struct NodeComparator {
  bool operator()(const Node& a, const Node& b) const {
    return a.distance > b.distance;
  }
};

int main(){
  // Read the height map from the input file
  ifstream input("input.txt");
  vector<string> grid;
  string line;
  while (getline(input, line)) {
    grid.push_back(line);
  }

  int gridRows = grid.size(), gridColumns = grid[0].size();
  pair<int, int> startPos, endPos;
  // Find the start and end positions
  for (int i = 0; i < gridRows; ++i){
    for (int j = 0; j < gridColumns; ++j){
      if (grid[i][j] == 'S') 
        startPos = {i, j};
      else if (grid[i][j] == 'E') 
        endPos = {i, j};
    }
  }

  grid[startPos.first][startPos.second] = 'a';
  grid[endPos.first][endPos.second] = 'z';

  // These large values ensure that any cell that has been reached 
  // and has a valid distance will have a smaller value than the placeholder value, 
  // and will therefore be prioritized over unreachable cells in the priority queue.
  vector<vector<int>> dist(gridRows, vector<int>(gridColumns, 1e9));
  dist[startPos.first][startPos.second] = 0;
  priority_queue<Node, vector<Node>, NodeComparator> q;
  q.push({0, startPos});

  // Main loop to find the shortest path
  while (!q.empty()) {
    Node node = q.top(); 
    q.pop();

    for (int i = 0; i < 4; ++i) {
      int x = node.pos.first + dx[i];
      int y = node.pos.second + dy[i];

      if ((x >= 0 && x < gridRows && y >= 0 && y < gridColumns)) {
        if (grid[x][y] <= grid[node.pos.first][node.pos.second] + 1) {
          if (dist[x][y] > dist[node.pos.first][node.pos.second] + 1) {
            // If the cell is the start position, set the distance to 0
            if (grid[x][y] == 'a') {
              dist[x][y] = 0;
              q.push({0, {x, y}});
            } else {
              // Otherwise, set the distance to 1 more than the current distance
              dist[x][y] = dist[node.pos.first][node.pos.second] + 1;
              q.push({node.distance++, {x, y}});
            }
          }
        }
      }
    }
  }
  cout << "Shortest path : " << dist[endPos.first][endPos.second] << endl;
}