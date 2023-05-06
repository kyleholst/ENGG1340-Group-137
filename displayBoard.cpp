// displayBoard.cpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "functions.h"
using namespace std;

void displayBoard(int turn, int lbag_size, vector<vector<string>> board, Player playerlist[]) {
    cout << "\033[2J\033[H"; // clears the screen
  
    // prints the top row of coordinates
    for (int x = 0; x < 15; x++) {
        if (x == 0) {
            cout << "   ";
        }
        cout << setw(2) << left << char('A'+x);
    }
    cout << "     " << playerlist[0].name << ": " << playerlist[0].score << endl;
    
    int length = sizeof(playerlist)/sizeof(Player);
    for (int y = 0; y < 15; y++) {
        // prints board and side coordinates
        cout << setw(2) << right << y << " ";
        for (string x : board[y]) {
            printTile(x);
        }
        cout << " " << setw(2) << left << y << "  ";

        // prints player names, scores, and options
        if (y+1 < length) {
            cout << playerlist[y+1].name << ": " << playerlist[y+1].score << endl;
        } else if (y == 4) {
            cout << "Remaining Letters: " << lbag_size << endl;
        } else if (y == 6) {
            cout << "=== OPTIONS ===\n";
        } else if (y == 7) {
            cout << "<Tile> <Coord>: places <Tile> at <Coord> (e.g. Z H7)\n";
        } else if (y == 8) {
            cout << "del <Coord>: removes the tile at <Coord>\n";
        } else if (y == 9) {
            cout << "s: shuffle your tiles\n";
        } else if (y == 10) {
            cout << "f: finish this turn\n";
        } else if (y == 11) {
            cout << "e: exchange your tiles (this uses your turn)\n";
        } else if (y == 12) {
            cout << "p: pass your turn\n";
        } else if (y == 13) {
            cout << "r: resign\n";
        } else if (y == 14) {
            cout << "search <Word>: check if <Word> is an accepted word\n";
        } else {
            cout << endl;
        }
    }

    // prints bottom row of coordinates
    for (int x = 0; x < 15; x++) {
        if(x==0) {
            cout << "   ";
        }
        cout << setw(2) << left << char('A'+x);
    }
    cout << "\n\n";

    
    // prints the player's tiles
    cout << playerlist[turn].name << "'s tiles:\n";
    for (string tile : playerlist[turn].tiles) {
        if (tile == "Blank") {
            printTile(" ");
        } else {
            printTile(tile);
        }
        cout << " ";
    }
    cout << endl;
}



      