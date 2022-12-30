// Puzzle from https://adventofcode.com/2022/day/11

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Struct to represent a monkey in a simulation.
struct Monkey {
    int id;
    vector<int> items;
    pair<string, string> operation;
    int divides;
    int ifTrue;
    int ifFalse;
    int ispected = 0;
};

// Processes the items for a given monkey and updates the items of other monkeys as needed
void processItems(Monkey& monkey, vector<Monkey>& monkeys) {
    for (auto& item: monkey.items) {
        string op = monkey.operation.first;
        string value = monkey.operation.second;
        int divides  = monkey.divides;
        int trueVal  = monkey.ifTrue;
        int falseVal = monkey.ifFalse;
        if (op == "+") {
            value == "old" ? item += item : item += stoi(value);
        } else if (op == "*") {
            value == "old" ? item = item * item : item = item  * stoi(value);
        }
        item = item / 3;
        monkey.ispected++;
        if (item % divides == 0) {
            monkeys[trueVal].items.push_back(item);
        } else {
            monkeys[falseVal].items.push_back(item);
        }
    }
    // Clear the monkey's list of items after processing them
    monkey.items.clear();
}


int main() {
    
    vector<Monkey> monkeys;
    ifstream input("input.txt");
    string line;

    while (getline(input, line)) {
        // Split the line into tokens
        stringstream ss(line);
        string token;
        int item, num;
        vector<string> tokens;

        while (ss >> token) {
            if (token == "Monkey") {
                Monkey m;
                ss >> token;
                m.id = stoi(token.substr(0, token.size()-1));
                monkeys.push_back(m);
            } else   if (token == "items:") {
                // Read the items for the current monkey
                while (ss >> token) {
                    stringstream tokenStream(token);
                    while (tokenStream >> num) {
                        monkeys.back().items.push_back(num);
                    }
                }
            } else if (token == "old") {
                // Read the operation and value for the current monkey
                ss >> token;
                monkeys.back().operation.first = token;
                ss >> token;
                monkeys.back().operation.second = token;
            } else if (token == "by") {
                // Read the divide value for the current monkey
                ss >> num; 
                monkeys.back().divides = num; 
            } else if (token == "true:") {
                while (ss >> token) {
                    if (token == "monkey") {
                        ss >> num;
                        monkeys.back().ifTrue = num;
                        break;
                    }
                }
            } else if (token == "false:") {
                while (ss >> token) {
                    if (token == "monkey") {
                        ss >> num;
                        monkeys.back().ifFalse = num;
                        break;
                    }
                }
            }
        }
    }
    // Close the file
    input.close();
    
    // Perform the rounds
    for (int i = 0; i < 20; i++) {
        for (auto& monkey : monkeys) {
            if (!monkey.items.empty()) {
                processItems(monkey, monkeys);
            }
        }
    }

    // Print result
    for (auto& monkey : monkeys) {
        cout << "monkey : " << monkey.id << endl;
        cout << "inspected : " << monkey.ispected << endl;
        if (!monkey.items.empty()) {
            cout << "items: ";
            for (auto& item : monkey.items)
                cout << item << " ";
            cout << endl;
        }
    }
    return 0;
}