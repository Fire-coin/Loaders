#include <iostream> // cout, endl
#include <conio.h> // getch
#include <string>
#include <vector>
#include <stdlib.h> // system
#include <filesystem> // path, directory_iterator

using namespace std;
namespace fs = filesystem;

int runMenu(const vector<string>&, int);
int loadPrograms(vector<string>&);

string getExtension(const string&);
string getName(const filesystem::path&);

int main() {
    vector<string> programs;
    
    loadPrograms(programs);
    int val = 0;
    do {
        val = runMenu(programs, val);
        system("cls");
        if (val != -1) {
            system(programs[val].c_str());
            cout << "Press enter to continue...\n";
            cin.get();
        }

    } while (val != -1);
    
    return 0;
}

/* Returns -1 if q is pressed, and index of selected option otherwise */
int runMenu(const vector<string>& menu, int current) {
    int c = 0;

    do {
        system("cls");
        for (int i = 0; i < menu.size(); ++i) {
            cout << (i == current ? "[]|" : "  |");
            cout << getName(menu[i]) << endl;
        }
        c = getch();
        if (c == 'j') {
            current++;
            if (current > menu.size() - 1) current = 0;
        } else if (c == 'k') {
            current--;
            if (current < 0) current = menu.size() - 1;
        }
    } while (c != 'q' && c != 13);

    return c == 'q' ? -1 : current;
}

string getName(const filesystem::path& path) {
    string name = path.string();

    int index = name.find_last_of('\\');
    return name.substr(index + 1, name.size() - index - 1);
}

string getExtension(const string& filename) {
    int index = filename.find_last_of('.');
    return filename.substr(index + 1, filename.size() - index - 1);
}

int loadPrograms(vector<string>& programs) {

    for (auto& f : fs::directory_iterator(fs::current_path())) {
        if (f.is_regular_file()) {
            string stringName = getName(fs::path(f));
            if (getExtension(stringName) == "exe") 
                programs.push_back(fs::path(f).string());
        }
    }
    return 0;
}