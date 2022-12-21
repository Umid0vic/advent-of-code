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

// Function to calculate the highest scenic score possible for a given tree at pos(row, col).
// A tree's scenic score is found by multiplying together its viewing distance in each of the four directions.
int visibleArea(const std::vector<std::vector<int>>& grid, int row, int col) {
  int height = grid[row][col];
  int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

  // Check the trees on abow
  for (int i = row - 1; i >= 0; i--) {
    if (grid[i][col] >= height) {
      y1++;
      break;
    } else {
      y1++;
    }
  }
  // Check the trees on below
  for (int i = row + 1; i < grid.size(); i++) {
    if (grid[i][col] >= height) {
      y2++;
      break;
    } else {
      y2++;
    }
  }

  // Check the trees on right
  for (int j = col + 1; j < grid[0].size(); j++) {
    if (grid[row][j] >= height) {
      x1++;
      break;
    } else {
      x1++;
    }
  }

  // Check the trees on left
  for (int j = col - 1; j >= 0; j--) {
    if (grid[row][j] >= height) {
      x2++;
      break;
    } else {
      x2++;
    }
  }
  // Return the the scenic score
  return (x1*x2*y1*y2);
}


int main() {

  vector<vector<int>> grid;
  ifstream file("file.txt");
  string line;
  int visibleTrees = 0;
  int scenicScore = 0;

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

  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      int tempScenicScore = visibleArea(grid, i, j);
      if (tempScenicScore > scenicScore) {
        cout << "temp score : " << tempScenicScore;
        scenicScore = tempScenicScore;
        cout << " new score : " << scenicScore << endl;
      }
    }
  }

  cout << "The number of visible trees: " << visibleTrees << endl;
  cout << "Highest scenic score : " << scenicScore << endl;

  return 0;
}
