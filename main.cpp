#include <iostream>
#include <fstream>
#include <iomanip> // For setw and setfill
#include <string>
#include <cmath> // For pow exponents
using namespace std;

#ifdef _WIN32 // Check if Windows OS
#include <direct.h> // For mkdir functions on Windows
#define mkdir _mkdir
#else
#include <sys/stat.h> // For mkdir functions on Windows
#endif

// Prompt user for password generation configuration
void PromptUser(bool& useNumbers, bool& useLowercase, bool& useUppercase, bool& useSymbols, string& prefix, int& passwordLength) {
    int usePrefix;
    cout << "Include prefix string to prepend before each generated password? (1 for yes, 0 for no): ";
    cin >> usePrefix;
    if (usePrefix == true) {
        cout << "Enter prefix string to prepend before each generated password: ";
        cin >> prefix;
    } else {
        prefix = "";
    }

    cout << "Include numbers (0-9)? (1 for yes, 0 for no): ";
    cin >> useNumbers;
    cout << "Include lowercase letters (a-z)? (1 for yes, 0 for no): ";
    cin >> useLowercase;
    cout << "Inlude UpperCase letters (A-Z)? (1 for yes, 0 for no): ";
    cin >> useUppercase;
    cout << "Include symbols (!@#$%^&*()_-+=[]{}|;:,.<>?)? (1 for yes, 0 for no): ";
    cin >> useSymbols;

    cout << "Enter the length of each password to generate (in characters): ";
    cin >> passwordLength;
}

// Password generator fuction
void GeneratePassword(ofstream& outfile, const string& charset, int passwordLength, int& passwordCount, int totalPasswordCount, const string& prefix, string current = "") {
    if (passwordLength == 0) {
        if (!prefix.empty()) {
            outfile << prefix << current << endl;
        } else {
            outfile << current << endl;
        }
        passwordCount++;
        if (passwordCount % 1000 == 0 || passwordCount == totalPasswordCount) {
            cout << "Password generated: " << setw(8) << setfill(' ') << passwordCount << " / " << totalPasswordCount << "\r";
            cout.flush();
        }
        return;
    }
    // Recursive function call to build password
    for (char c : charset) {
        GeneratePassword(outfile, charset, passwordLength - 1, passwordCount, totalPasswordCount, prefix, current + c);
    }
}

int main() {
    string folderName = "Wordlist Dictionary";
    string fileName = "password.txt";
    string folderPath = folderName;
    string filePath = folderPath + "/" + fileName;

    int dir_error = mkdir(folderPath.c_str());

    if (dir_error == false || errno == EEXIST) {
        cout << "Success!, Directory '" << folderName << "' created or already exists" << endl;

        bool useNumbers, useLowercase, useUppercase, useSymbols;
        int passwordLength;
        string prefix;

        PromptUser(useNumbers, useLowercase, useUppercase, useSymbols, prefix, passwordLength);

        string charset;
        if (useNumbers == true) charset += "0123456789";
        if (useLowercase == true) charset += "abcdefghijklmnopqrstuvwxyz";
        if (useUppercase == true) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (useSymbols == true) charset += "!@#$%^&*()_-+=[]{}|;:,.<>?";

        int totalPasswordCount = 0;
        if (charset.size() != 0 && passwordLength > 0) {
            totalPasswordCount = pow(charset.size(), passwordLength);
        }
        
        ofstream outfile(filePath);
        if (outfile.is_open()) {
            int passwordCount = 0;
            GeneratePassword(outfile, charset, passwordLength, passwordCount, totalPasswordCount, prefix);
            outfile.close();
            cout << "\nGenerated passwords saved successfully to: " << filePath << endl;
        }
        else {
             cerr << "Error!, Failed to create file: " << filePath << endl;
        }
    }
    else {
        cerr << "Error!, Failed to create directory: " << folderName << endl;
    }

    return 0;
}