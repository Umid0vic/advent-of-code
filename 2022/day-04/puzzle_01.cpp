// problem: https://adventofcode.com/2022/day/4

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// A range of numbers
struct Range {
    int start;
    int end;
};

// Parse a range from a string in the form "START-END"
Range parse_range(const string range_str) {
    int dash_pos = range_str.find('-');
    int start = stoi(range_str.substr(0, dash_pos));
    int end = stoi(range_str.substr(dash_pos + 1));
    return {start, end};
}

// Count the number of pairs where one range fully contains the other
int fully_contained(const vector<pair<Range, Range>> pairs) {
    int count = 0;
    for (int i = 0; i < pairs.size(); i++) {
      // Check if one range fully contains the other
      if ((pairs[i].first.start <= pairs[i].second.start && 
          pairs[i].first.end >= pairs[i].second.end) ||
          (pairs[i].second.start <= pairs[i].first.start && 
          pairs[i].second.end >= pairs[i].first.end)) {
        count++;
      }
    }
    return count;
}

int main() {
    // Read pairs of numbers from a text file
    vector<pair<Range, Range>> pairs;
    ifstream file("ranges.txt");
    string line;
    while (getline(file, line)) {
        // Parse the two ranges from the line
        int comma_pos = line.find(',');
        auto range1 = parse_range(line.substr(0, comma_pos));
        auto range2 = parse_range(line.substr(comma_pos + 1));
        pairs.emplace_back(range1, range2);
    }

    // Test the function
    cout << fully_contained(pairs) << endl;

    return 0;
}