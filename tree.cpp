#include <iostream> // cout, cin, cerr, endl
#include <string> // string
#include <vector> // vector
#include <filesystem> // path, directory_entry, directory_itrator
#include <algorithm> // sort, replace
#include <utility> // pair
#include <deque> // deque

using namespace std;

namespace fs = filesystem;

string getCurrentName(const fs::path&);

struct Directory
{
    vector<string> dirs;
    vector<string> files;
    fs::path m_dirPath;
    
    Directory(fs::path path) {
        m_dirPath = path;
        dirs.reserve(10);
        files.reserve(10);
        
        try {
            for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
                if (entry.is_regular_file()) files.emplace_back(getCurrentName(entry.path()));
                if (entry.is_directory()) dirs.emplace_back(getCurrentName(entry.path()));
            }
        } catch (const fs::filesystem_error& e) {
            
        }
        
        sort(dirs.begin(), dirs.end());
        sort(files.begin(), files.end());
    }
    
    Directory() {
        m_dirPath = "";
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
    
    int getRemaining() const {
        return dirs.size() + files.size();
    }
};

void recursiveIteration(Directory&);


int main() {
    string dir;
    std::cout << "Enter directory: ";
    getline(cin, dir);
    if (dir.empty() || dir == ".") dir = fs::current_path().string();
    replace(dir.begin(), dir.end(), '/', '\\');

    fs::directory_entry entry = fs::directory_entry(fs::current_path() / dir);
    if (!entry.exists()) {
        cerr << "Invalid directory entered!\n";
        cout << "Changing to current directory, press enter to proceed\n";
        cin.get();
        entry = fs::directory_entry(fs::current_path());
    }
    Directory curDir = Directory(entry);
    recursiveIteration(curDir);

    return 0;
}


string getCurrentName(const fs::path& p) {
    string str = p.string();

    int index = str.find_last_of('\\');

    return str.substr(index + 1, str.length() - index - 1);
}


void recursiveIteration(Directory& startDirectory) {
    deque<Directory> dirStack;

    dirStack.push_back(startDirectory);
    std::cout << getCurrentName(startDirectory.m_dirPath) << endl;
    while (dirStack.size() > 0) {
        Directory& curDir = dirStack.back();
        if (curDir.getRemaining() > 0) {
            auto[name, dir] = curDir.getNext();
            std::cout << "|";
            for (auto it = dirStack.begin(); it != dirStack.end() - 1; ++it) {
                cout << "   ";
                if ((it + 1)->m_dirPath == curDir.m_dirPath) cout << '|';
                else cout << ((it + 1)->getRemaining() > 0 ? '|' : ' ');
            }
            if (!dir.m_dirPath.empty()) dirStack.push_back(dir);

            cout << "---" << name << endl;

        } else dirStack.pop_back();
    }
}