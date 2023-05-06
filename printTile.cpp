// printTile.cpp

#include <iostream>
#include <string>
#include "functions.h"
using namespace std;

void printTile(const string tile){
    // set the color of the output text based on the value of 'tile'
    if (tile == "DW" || tile == "<>")
        cout << "\033[1;37;45m" << tile; // magenta background, white text
    else if (tile == "TW")
        cout << "\033[1;37;41m" << tile; // red background, white text
    else if (tile == "DL")
        cout << "\033[1;37;46m" << tile; // cyan background, white text
    else if (tile == "TL")
        cout << "\033[1;37;44m" << tile; // blue background, white text
    else if (tile == "")
        cout << "\033[21;37;40m" << "  "; // black background, black text, two spaces (empty tile)
    else if (tile.substr(0,5) == "Blank")
        cout << "\033[1;30;43m" << "  "; // yellow background, bright black text, letter and tile value (blank tile)
    else {
        string subscript=" ₁₂₃₄₅₆₇₈₉⒑";
        char value = subscript[scorer(tile)]; // get the subscript value based on the score of the tile
        cout << "\033[21;30;43m" << tile << value; // yellow background, black text, tile value with subscript
    }
    cout << "\033[0m"; // reset the text color to the default
}