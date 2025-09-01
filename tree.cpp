#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

namespace fs = filesystem;

string getCurrentName(fs::path);

struct Directory
{
    vector<string> dirs;
    vector<string> files;
    fs::path dirPath;

    Directory(fs::path path) {
        dirPath = path;
        dirs.reserve(10);
        files.reserve(10);

        for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) files.emplace_back(getCurrentName(entry.path()));
            if (entry.is_directory()) dirs.emplace_back(getCurrentName(entry.path()));
        }
    }

    void displayAll() {
        std::cout << "Directories:\n";
        for (const auto& d : dirs) cout << d << endl;

        std::cout << "\nFiles:\n";
        for (const auto& f : files) cout << f << endl;
    }
};


int main() {

    Directory dir = Directory(fs::current_path());
    dir.displayAll();

    return 0;
}

string getCurrentName(fs::path p) {
    string str = p.string();

    int index = str.find_last_of('/');
    if (index == -1) index = str.find_last_of('\\');

    return str.substr(index + 1, str.length() - index - 1);
}