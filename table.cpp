#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath> // max

using namespace std;

using matrix = vector<vector<string>>;

void loadMatrix(matrix&, ifstream&);

void split(const string&, const char, vector<string>&);

void getWidths(const matrix&, vector<int>&);

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
    if (fin.is_open()) {
        loadMatrix(mat, fin);
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[i].size(); ++j) {
                cout << mat[i][j] << ' ';
            }
            cout << endl;
        }
        getWidths(mat, widths);
        cout << "Column widths: ";
        for (auto& i : widths) {
            cout << i << ' ';
        } cout << endl;
    } else
        cerr << "Could not open file: '" << pathToFile << "'\n";


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