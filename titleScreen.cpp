// titleScreen.cpp ✅

#include <iostream>
#include <string>
#include "functions.h"
using namespace std;

void titleScreen() {
    cout << "\033[2J\033[H"; // clears the console screen
    string dummy;
    cout << "Welcome to\n";
    cout << "        _____                 __    __    __\n";
    cout << "       / ___/______________ _/ /_  / /_  / /__\n";
    cout << "       \\__ \\/ ___/ ___/ __ `/ __ \\/ __ \\/ / _ \\\n";
    cout << "      ___/ / /__/ /  / /_/ / /_/ / /_/ / /  __/\n";
    cout << "     /____/\\___/_/   \\__,_/_.___/_.___/_/\\___/\n\n";
    cout << "Please make the terminal window as large as possible\n\n";
    cout << "                Press Enter to begin\n";
    getline(cin, dummy);
    cout << "\033[2J\033[H"; // clears the console screen
}