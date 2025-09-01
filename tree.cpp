#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm> // sort
#include <utility> // std::pair
#include <deque>

using namespace std;

namespace fs = filesystem;

string getCurrentName(fs::path);

struct Directory
{
    vector<string> dirs;
    vector<string> files;
    fs::path m_dirPath;

    Directory(fs::path path) {
        m_dirPath = path;
        dirs.reserve(10);
        files.reserve(10);

        for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) files.emplace_back(getCurrentName(entry.path()));
            if (entry.is_directory()) dirs.emplace_back(getCurrentName(entry.path()));
        }

        sort(dirs.begin(), dirs.end());
        sort(files.begin(), files.end());
    }

    Directory() {
        m_dirPath = "";
    }

    void displayAll() {
        std::cout << "Directories:\n";
        for (const auto& d : dirs) cout << d << endl;

        std::cout << "\nFiles:\n";
        for (const auto& f : files) cout << f << endl;
    }

    pair<string, Directory> getNext() {
        if (dirs.size() > 0) {
            string nextDir = dirs.back();
            dirs.pop_back();
            return pair<string, Directory>(nextDir, Directory(m_dirPath / nextDir));
        } else if (files.size() > 0) {
            string nextFile = files.back();
            files.pop_back();
            return pair<string, Directory>(nextFile, Directory());
        } else {
            return pair<string, Directory>("", Directory());
        }
    }

    int getRemaining() {
        return dirs.size() + files.size();
    }
};


void recursiveIteration(Directory);


int main() {
    Directory dir = Directory(fs::current_path());
    recursiveIteration(dir);

    return 0;
}

string getCurrentName(fs::path p) {
    string str = p.string();

    int index = str.find_last_of('/');
    if (index == -1) index = str.find_last_of('\\');

    return str.substr(index + 1, str.length() - index - 1);
}


void recursiveIteration(Directory startDirectory) {
    deque<Directory> dirStack;

    dirStack.push_back(startDirectory);

    while (dirStack.size() > 0) {
        Directory& curDir = dirStack.back();
        {
            if (curDir.getRemaining() > 0) {
            auto[name, dir] = curDir.getNext();
            if (dir.m_dirPath.empty()) cout << "File: " << name << endl;
            else {
                cout << "Folder: " << name << endl;
                dirStack.push_back(dir);
            }
        } else dirStack.pop_back();
    }
    }
}