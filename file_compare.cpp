// file_compare.cpp

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1, ios::binary);
    ifstream f2(file2, ios::binary);

    if (!f1 || !f2) {
        cerr << "Failed to open one or both files." << endl;
        return false;
    }

    char ch1, ch2;
    size_t pos = 0;
    while (f1.get(ch1) && f2.get(ch2)) {
        if (ch1 != ch2) {
            cout << "Difference at byte position " << pos << ": '" << ch1 << "' vs '" << ch2 << "'\n";
            return false;
        }
        pos++;
    }

    if (f1.get(ch1) || f2.get(ch2)) {
        cout << "Files differ in length." << endl;
        return false;
    }

    return true;
}

int main() {
    string file1, file2;
    cout << "Enter first file name: ";
    cin >> file1;
    cout << "Enter second file name: ";
    cin >> file2;

    if (compareFiles(file1, file2)) {
        cout << "Files are identical." << endl;
    } 
    else {
        cout << "Files differ." << endl;
    }
    return 0;
}
