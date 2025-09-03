#include <iostream> // cout, endl
#include <conio.h> // getch
#include <string> 
#include <vector> 
#include <stdlib.h> // system

using namespace std;

int runMenu(vector<string>&, int);

int main() {
    vector<string> programs;
    
    programs.push_back("tree.exe");
    programs.push_back("hello.exe");
    programs.push_back("prog.exe");

    int val = 0;
    do {
        val = runMenu(programs, val);
        
    } while (val != -1);
    
    return 0;
}

/* Returns -1 if q is pressed, and index of selected option otherwise */
int runMenu(vector<string>& menu, int current) {
    int c = 0;

    do {
        system("cls");
        for (int i = 0; i < menu.size(); ++i) {
            cout << (i == current ? "[]|" : "  |");
            cout << menu[i] << endl;
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