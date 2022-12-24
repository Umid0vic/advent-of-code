// Puzzle from https://adventofcode.com/2022/day/12

#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Node struct to store the distance and position of a cell
struct Node {
  int distance;
  pair<int, int> pos;
};

int main(){

    ifstream input("input.txt");
    // read the height map from the input file
    vector<string> grid;
    string line;
    while (getline(input, line)) {
      grid.push_back(line);
    }

    int gRaw = grid.size(), gCol = grid[0].size();
    int startX, startY, endX, endY;
    // Find the start and end positions
    for (int i = 0; i < gRaw; ++i){
        for (int j = 0; j < gCol; ++j){
            if (grid[i][j] == 'S') 
              startX = i, startY = j;
            if (grid[i][j] == 'E') 
              endX = i, endY = j;
        }
    }

    grid[startX][startY] = 'a';
    grid[endX][endY] = 'z';

    vector<vector<int>> dist(gRaw, vector<int>(gCol, 1e9));

    dist[startX][startY] = 0;
    queue<Node> q;
    q.push({0, {startX, startY}});

    while (!q.empty()) {
      Node node = q.front(); 
      q.pop();
      for (int i = 0; i < 4; ++i) {
        int nx = node.pos.first + (i == 0 ? -1 : (i == 2 ? 1 : 0));
        int ny = node.pos.second + (i == 3 ? -1 : (i == 1 ? 1 : 0));

        if (!(nx >= 0 && nx < gRaw && ny >= 0 && ny < gCol)) continue;

        if (grid[nx][ny] <= grid[node.pos.first][node.pos.second] + 1) {
          if (dist[nx][ny] > dist[node.pos.first][node.pos.second] + 1) {
            dist[nx][ny] = dist[node.pos.first][node.pos.second] + 1;
            q.push({node.distance++, {nx, ny}});
          }
        }
      }
    }
    cout << dist[endX][endY] << '\n';
}