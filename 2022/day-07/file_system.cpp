// Puzzle from https://adventofcode.com/2022/day/7

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

// File struct to represent a file or directory
struct File {
    string name;
    int size;
    unordered_map<string, File> children;  // Only used for directories
    File* parent;
};

// Function to create a new file or directory based on the given line of input
// The file or directory will be added to the current directory specified by pCurrentDir
void createFile(File *pCurrentDir, string line) {
    File file;
    if (line.substr(0, 4) == "dir ") {
      // Create a new directory
        string dirName = line.substr(4);
        file.name = dirName;
        file.size = -1;
        file.parent = pCurrentDir;
        pCurrentDir->children[dirName] = file;
    } else {
        // Create a new file
        int size = stoi(line.substr(0, line.find(' ')));
        string fileName = line.substr(line.find(' ') + 1);
        file.name = fileName;
        file.size = size;
        file.parent = pCurrentDir;
        pCurrentDir->children[fileName] = file;
    }
}

// Recursive function to calculate the total size of a directory in bytes
// The size of a directory is the sum of the sizes of all its files and subdirectories
int calculateDirectorySize(File& directory) {
    int totalSizeOfDir = 0;
    int size = 0;
    for (auto& [name, child] : directory.children) {
        if (child.size == -1) {
        // Recursively calculate the size of this child directory
        size += calculateDirectorySize(child);
        } else {
        // This child is a file, so add its size to the total
        size += child.size;
        }
    }
    return size;
}

// Recursive function to traverse the file system and sum up the sizes
// of all the directories that have at most 100000 bytes in total
int sumDirectorySizes(File& dir, int& totalSize) {
    int dirSize = calculateDirectorySize(dir);
    if (dirSize <= 100000) {
        totalSize += dirSize;
    }
    // Traverse the children of the current directory
    for (auto& [name, child] : dir.children) {
        // If the child is a directory, recursively sum its sizes
        if (child.size == -1) {
        sumDirectorySizes(child, totalSize);
        }
    }
    return totalSize;
}

// Recursive function to find the directory with a size closest to spaceToFreeUp
// dir: the current directory being considered
// spaceToFreeUp: the amount of space that needs to be freed up
// dirToRemove: a pointer to a File struct that will be updated to point to
// the directory with the size closest to spaceToFreeUp
void removeDir(File& dir, int spaceToFreeUp, File*& dirToRemove) {
    int dirSize = calculateDirectorySize(dir);
    if (dirSize >= spaceToFreeUp && (dirToRemove == nullptr || 
        abs(dirSize - spaceToFreeUp) < abs(calculateDirectorySize(*dirToRemove) - spaceToFreeUp))) {
        cout << "log: found dir " << dir.name << " with size " << dirSize << endl;
        dirToRemove = &dir;
    }
    for (auto& [name, child] : dir.children) {
        if (child.size == -1) {
            removeDir(child, spaceToFreeUp, dirToRemove);
        }
    }
}


// Function to print the file structure of a directory and its children
void printFileStructure(const File& file, int level) {
    // Print the file name and type
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << "- " << file.name;
    if (file.size == -1) {
        cout << " (dir)";
    } else {
        cout << " (file, size=" << file.size << ")";
    }
    cout << endl;
    // Recursively print the children
    for (const auto& [name, child] : file.children) {
        printFileStructure(child, level + 1);
    }
}


int main() {

    // Create the root directory
    File root;
    root.name = "/";
    root.size = -1;
    root.parent = nullptr;
    File* pCurrentDir = &root;
    
    ifstream input("input.txt");
    string line;

    while (getline(input, line)) {
        // Change directory
        if (line.substr(0, 4) == "$ cd") {
            string command = line.substr(5);

            if (command == "/") {
                // Set the current directory to the root directory
                pCurrentDir = &root;
            } else if (command == "..") {
                /// Set the current directory to the parent directory if it exists
                if (pCurrentDir->parent) pCurrentDir = pCurrentDir->parent;
                else cout << "Error: Already at root directory" << endl;
            } else {
                // Set the current directory to the subdirectory if it exists
                string subdir_name = line.substr(5);
                if (pCurrentDir->children.count(subdir_name)) {
                pCurrentDir = &pCurrentDir->children[subdir_name];
                } else {
                cout << "Error: No such directory" << endl;
                }
            }
        } else if (line != "$ ls") {
            createFile(pCurrentDir, line);
        }
    }
    // Print file structure
    printFileStructure(root, 0);

    int sum = sumDirectorySizes(root, sum);
    cout << "Sum of sizes of all directories with at least 100000 bytes: " << sum << endl;

    // The total disk space available in the file system is 70000000.
    // To run the update, we need unused space of at least 30000000.
    // So find a directory, if deleted can free up enough space to run the update

    // Calculate the total used space
    int totalUsedSpace = 70000000 - calculateDirectorySize(root);
    // Calculate the amount of space that needs to be freed up
    int spaceToFreeUp = abs(30000000 - totalUsedSpace);
    if (spaceToFreeUp > 0) {
        File* dirToRemove = nullptr;
        removeDir(root, spaceToFreeUp, dirToRemove);
        if (dirToRemove != nullptr) {
            cout << "Found dir to remove: " << dirToRemove->name << endl;
            // Delete the found directory
            dirToRemove->parent->children.erase(dirToRemove->name);
            cout << "Deleted directory " << dirToRemove->name << " to free up space." << endl;
        } else {
            cout << "Could not find a directory with enough size to delete." << endl;
        }
    } else {
        cout << "There is already enough space to run the update." << endl;
    }

    // Print the file system structure
    //cout << "File system structure after update:" << endl;
    //printFileStructure(root, 0);
    return 0;
}