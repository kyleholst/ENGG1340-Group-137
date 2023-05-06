// functions.h

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

struct Player {
  string name = "";
  int score = 0;
  vector<string> tiles;
};

struct Word {
  string name = "";
  int x = -1;
  int y = -1;
  string orient = "";
};

// Print the title screen
void titleScreen(); // finalised

// Given an input tile, it returns the score of that tile
int scorer(string tile); // finalised

// Given an input tile, it prints it according to colour and score
void printTile(string tile); // finalised

// Given the turn, size of letterbag, board, and playerlist, print the board and
// other info
void displayBoard(int turn, int n, int lbag_size, vector<vector<string>> board,
                  Player playerlist[]); // finalised

// Given the current board, find all the words created by a player in their turn
vector<Word> findWords(vector<vector<string>> board); // Farhan in progress

// Given an input word, find if the word is in the standard scrabble dictionary
// using text file IO
bool dictSearch(string word); // finalised

// Given the list of new words (found from findWords), the oldboard and the
// newboard, count the points gained in a turn
int countPoints(vector<Word> words, vector<vector<string>> newboard,
                vector<vector<string>> oldboard);
// Ravi in progress

// Given the turn, letterbag, board, and playerlist, make the move according to
// user input, and return bool 'passed' (true if passed, false if otherwise)
bool makeMove(int turn, int n, vector<string>& letterbag, vector<vector<string>>& board,
              Player playerlist[]);

#endif