// Puzzle from https://adventofcode.com/2022/day/8

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Returns true if the tree at position (row, col) is visible from any direction.
bool isVisible(const std::vector<std::vector<int>>& grid, int row, int col) {
  int height = grid[row][col];
  bool isVisibleAbove = true;
  bool isVisibleBelow = true;
  bool isVisibleRight = true;
  bool isVisibleLeft  = true;

  // Check the trees on abow
  for (int i = row - 1; i >= 0; i--) {
    if (grid[i][col] >= height) {
      isVisibleAbove = false;
      break;
    }
  }
  if (isVisibleAbove) return true;
  // Check the trees on below
  for (int i = row + 1; i < grid.size(); i++) {
    if (grid[i][col] >= height) {
      isVisibleBelow = false;
      break;
    }
  }
  if (isVisibleBelow) return true;

  // Check the trees on right
  for (int j = col + 1; j < grid[0].size(); j++) {
    if (grid[row][j] >= height) {
      isVisibleRight = false;
      break;
    }
  }
  if (isVisibleRight) return true;

  // Check the trees on left
  for (int j = col - 1; j >= 0; j--) {
    if (grid[row][j] >= height) {
      isVisibleLeft = false;
      break;
    }
  }
  if (isVisibleLeft) return true;

  // Return false if the tree is not visible from any direction.
  return false;
}

int main() {

  vector<vector<int>> grid;
  ifstream file("file.txt");
  string line;
  int visibleTrees = 0;

  while (getline(file, line)) {
    vector<int> row;

    for (char c : line) {
        int n = stoi(string(1, c));
        row.push_back(n);
    }
    grid.push_back(row);
  }

  // Get the number of trees on the edge
  visibleTrees += (grid.size()*2 + grid[0].size()*2) - 4;

  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      if (isVisible(grid, i, j)) {
        visibleTrees++;
      }
    }
  }

  cout << "The number of visible trees: " << visibleTrees << endl;

  return 0;
}
