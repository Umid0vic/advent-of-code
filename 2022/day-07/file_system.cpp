#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// A struct that represents a directory or a file in the file system
struct File {
    string name;
    int size;
    bool isDirectory;
    vector<File> children;
};

// A function to parse a line of input and create a File object
File parseInputLine(string line) {
    File file;
    if (line.substr(0,3) == "dir") {
        // The line represents a directory
        file.isDirectory = true;
        int spaceIndex = line.find(' ');
        file.name = line.substr(spaceIndex + 1);
        cout << "log: parsed a dir with name : " << file.name  << endl;
    } else {
        // The line represents a file
        file.isDirectory = false;
        int spaceIndex = line.find(' ');
        file.size = stoi(line.substr(0, spaceIndex));
        file.name = line.substr(spaceIndex + 1);
        cout << "log: parsed a file with name : " << file.name << " and size : " << file.size << endl;
    }
    return file;
}

// Recursive function to calculate the total size of a directory
int calculate_directory_size(File& directory) {
    int size = 0;
    for ( File& child : directory.children) {
        if (child.isDirectory) {
            // Recursively calculate the size of this child directory
            size += calculate_directory_size(child);
        } else {
            // This child is a file, so add its size to the total
            size += child.size;
        }
    }
    return size;
}



int main() {
    
    vector<string> input;
    string line;
    ifstream datastream("file.txt");

    while (getline(datastream, line)) {
        input.push_back(line);
    }
    // The keys of the map are strings representing the names of directories, 
    // and the values are pointers to the corresponding File objects representing those directories. 
    unordered_map<string, File*> directories;
    // This vector is used to store the entire file and directory tree, 
    // with the root directory being the first element in the vector.
    vector<File> files;
    File* currentDirectory = &files.emplace_back();
    currentDirectory->isDirectory = true;
    // A root directory
    currentDirectory->name = "/";
    directories["/"] = currentDirectory;

    for (const string& line: input) {
        
        if (line[0] == '$') {
            // Commands
            if (line == "$ cd /") {
                // Change the current directory to the root directory
                currentDirectory = directories["/"];
                cout << "log: changing to root dir " << line << endl;
                cout << "log: curentDir is " << currentDirectory->name << endl;
            } else if (line.substr(0, 4 ) == "$ cd") {

                if (line == "$ cd ..") {
                    cout << "log: changing to parent " << line << endl;
                    currentDirectory = directories["/"];
                    for (auto file : files) {
                        if (file.isDirectory) {
                            for (auto child : file.children) {
                                if (&child == currentDirectory) {
                                    // The current directory is a child of this directory, so this is the parent
                                    currentDirectory = &file;
                                    break;
                                }
                            }
                        }
                    }
                    
                    cout << "log: curentDir is " << currentDirectory->name << endl;
                } else {
                    // Change the current directory to a subdirectory
                    
                    string subdirectoryName = line.substr(5);
                    File* subdirectory = directories[subdirectoryName];
                    if (subdirectory == nullptr) {
                        // This subdirectory does not exist yet, so create it
                        cout << "log: creating subdir " << line << endl;
                        subdirectory = &files.emplace_back();
                        subdirectory->isDirectory = true;
                        subdirectory->name = subdirectoryName;
                        currentDirectory->children.push_back(*subdirectory);
                    }
                    cout << "log: changing to subdir " << line << endl;
                    currentDirectory = subdirectory;
                    cout << "log: curentDir is " << currentDirectory->name << endl;
                }

            } else if (line == "$ ls") {
                // List the contents of the current directory
                cout << "log: ls command " << line << endl;
            }
        } else {
            // This line is a file or directory, so add it to the current directory
            File file = parseInputLine(line);
            currentDirectory->children.push_back(file);
            if (file.isDirectory) {
                directories[file.name] = &currentDirectory->children.back();
                cout << "log: added " << line << endl;
            }
        }
    }

    vector<File> small_directories;
    // TODO: Calculate total size of small directories.


    return 0;
}