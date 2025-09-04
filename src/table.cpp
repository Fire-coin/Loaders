#include <iostream>
#include <string>
#include <fstream> // ifstream, ofstream
#include <vector>
#include <sstream>
#include <cmath> // max

using namespace std;

using matrix = vector<vector<string>>;

void loadMatrix(matrix&, ifstream&);

void split(const string&, const char, vector<string>&);

void getWidths(const matrix&, vector<int>&);

void displayInConsole(const matrix&, const vector<int>&);

string getChars(int spaces, char c);

int sum(const vector<int>&);

int writeToFile(const matrix&, const vector<int>&, string);

int main() {

    string pathToFile;
    cout << "Enter filename or path to file to make table from: ";
    getline(cin, pathToFile);

    string outputFile;
    cout << "Enter filename for output file, or press enter for console output: ";
    getline(cin, outputFile);

    ifstream fin(pathToFile);
    matrix mat;
    vector<int> widths;
    if (!fin.is_open()) {
        cerr << "Could not open file: '" << pathToFile << "'\n";
        return -1;
    }
    
    loadMatrix(mat, fin);
    getWidths(mat, widths);

    if (outputFile.empty() || outputFile == ".")
        displayInConsole(mat, widths);
    else
        writeToFile(mat, widths, outputFile);

    return 0;
}


void split(const string& line, const char delimiter, vector<string>& output) {
    string data;
    stringstream ss(line);
    while (getline(ss, data, delimiter))
        output.push_back(data);
}

void loadMatrix(matrix& mat, ifstream& fin) {
    string line;
    vector<string> row;
    while (getline(fin, line, '\n')) {
        split(line, ' ', row);
        mat.emplace_back(row);
        row.clear();
    }
}   

void getWidths(const matrix& mat, vector<int>& widths) {
    widths.clear();
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[i].size(); ++j) {
            if (widths.size() <= j) 
                widths.push_back(mat[i][j].size());
            else
                widths[j] = max(widths[j], (int)mat[i][j].size());
        }
    }
}

void displayInConsole(const matrix& mat, const vector<int>& widths) {
    int totalWidth = sum(widths) + widths.size() * 3 + 1;
    cout << getChars(totalWidth, '_') << endl;
    for (int i = 0; i < mat.size(); ++i) {
        cout << '|';
        for (int j = 0; j < mat[i].size(); ++j) {
            if (widths[j] % 2 == 1) {
                int spaces = (widths[j] - mat[i][j].size()) / 2 + 1;
                if (mat[i][j].size() % 2 == 1)
                    cout << getChars(spaces, ' ') << mat[i][j] << getChars(spaces, ' ');
                else
                    cout << getChars(spaces, ' ') << mat[i][j] << getChars(spaces + 1, ' ');
            } 
            else {
                int spaces = (widths[j] - mat[i][j].size()) / 2 + 1;
                if (mat[i][j].size() % 2 == 1) 
                    cout << getChars(spaces, ' ') << mat[i][j] << getChars(spaces + 1, ' ');
                else
                    cout << getChars(spaces, ' ') << mat[i][j] << getChars(spaces, ' ');
            }
            cout << '|';
        }
        cout << endl << getChars(totalWidth, '-') << endl;
    }
}

string getChars(int spaces, char c) {
    string output = "";
    for (int i = 0; i < spaces; ++i) {
        output += c;
    }
    return output;
}

int sum(const vector<int>& vec) {
    int total = 0;
    for (const int& i : vec) 
        total += i;
    return total;
}

int writeToFile(const matrix& mat, const vector<int>& widths, string filename) {
    ofstream fon(filename);
    if (!fon.is_open()) {
        cerr << "Could not open file '" << filename << "' to write into\n";
        return -1;
    }
    int totalWidth = sum(widths) + widths.size() * 3 + 1;
    fon << getChars(totalWidth, '_') << endl;
    for (int i = 0; i < mat.size(); ++i) {
        fon << '|';
        for (int j = 0; j < mat[i].size(); ++j) {
            if (widths[j] % 2 == 1) {
                int spaces = (widths[j] - mat[i][j].size()) / 2 + 1;
                if (mat[i][j].size() % 2 == 1)
                    fon << getChars(spaces, ' ') << mat[i][j] << getChars(spaces, ' ');
                else
                    fon << getChars(spaces, ' ') << mat[i][j] << getChars(spaces + 1, ' ');
            } 
            else {
                int spaces = (widths[j] - mat[i][j].size()) / 2 + 1;
                if (mat[i][j].size() % 2 == 1) 
                    fon << getChars(spaces, ' ') << mat[i][j] << getChars(spaces + 1, ' ');
                else
                    fon << getChars(spaces, ' ') << mat[i][j] << getChars(spaces, ' ');
            }
            fon << '|';
        }
        fon << endl << getChars(totalWidth, '-') << endl;
    }

    return 0;
}