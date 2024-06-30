#include <iostream>
#include <fstream>
#include <iomanip> // For setw and setfill
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
        // Ask for use of prefix string
    int usePrefix;
    cout << "Include prefix string to prepend before each generated password? (1 for yes, 0 for no): ";
    cin >> usePrefix;

        // Ask for character types to include
    cout << "Include numbers (0-9)? (1 for yes, for = no): ";
    cin >> useNumbers;
    cout << "Include lowercase letters (a-z)? (1 for yes, 0 for no): ";
    cin >> useLowercase;
    cout << "Inlude UpperCase letters (A-Z)? (1 for yes, 0 for no): ";
    cin >> useUppercase;
    cout << "Include symbols (!@#$%^&*()_-+=[]{}|;:,.<>?)? (1 for yes, 0 for no): ";
    cin >> useSymbols;

    if (usePrefix == true) {
        cout << "Enter prefix string to prepend before each generated password: ";
        cin >> prefix;
    } else {
        prefix = "";
    }

        // For password length
    cout << "Enter the length of each password to generate (in characters): ";
    cin >> passwordLength;
}

// Password generator fuction
void GeneratePasswords() {

}

int main() {
    string folderName = "Wordlist Dictionary";
    string fileName = "password.txt";
    string folderPath = "/" + folderName;
    string filePath = folderPath + "/" + fileName;

    int dir_error = mkdir(folderPath.c_str());

    if (dir_error == true || errno == !EEXIST) {
        cerr << "Error!, Failed to created directory: " << folderName << endl;
    }
    else {
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
        
    }
    




return 0;
}