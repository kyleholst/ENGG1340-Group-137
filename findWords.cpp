// findWords.cpp

#include "functions.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

vector<Word> findWords(vector<vector<string>> board) {
  // finds all the words on the array board
  bool valid;
  set<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
                             "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                             "S", "T", "U", "V", "W", "X", "Y", "Z", "Blank"};
  vector<Word> words;
  for (int y = 0; y < 15; y++) {
    for (int x = 0; x < 15; x++) {
      // For every square in the board, check if it houses a letter tile,
      // then check if the square directly to the left is empty (or out of
      // range). If both are true, move to the right until another empty square
      // is found. Then store all letter tiles in between as a word, and append
      // to a list.
      valid = false;
      if (y > 0 && alphabet.count(board[y][x].substr(0, 5)) != 0) {
        if (alphabet.count(board[y-1][x].substr(0, 5)) == 0) {
          valid = true;
        }
      } else if (y == 0 && alphabet.count(board[y][x].substr(0, 5)) != 0) {
        valid = true;
      }
      if (valid) {
        Word word;
        word.name = "";
        word.x = x;
        word.y = y;
        word.orient = "v";
        // store the starting coordinate of the word, as well as its orientation
        // (h or v)
        int k = y;
        while (k != 15 && alphabet.count(board[k][x].substr(0, 5)) != 0) {
          if (board[k][x].substr(0, 5) == "Blank") {
            word.name += board[k][x][5];
          } else {
            word.name += board[k][x];
          }
          k++;
        } 
        if (word.name.length() > 1) {
          words.push_back(word);
        } // only words with >2 letters are counted
      }
      // For every square in the board, check if it houses a letter tile,
      // then check if the square directly above is empty (or out of range).
      // If both are true, move downwards until another empty square is found.
      // Then store all letter tiles in between as a word, and append to a list.
      valid = false;
      if (x > 0 && alphabet.count(board[y][x].substr(0, 5)) != 0) {
        if (alphabet.count(board[y][x-1].substr(0, 5)) == 0) {
          valid = true;
        }
      } else if (x == 0 && alphabet.count(board[y][x].substr(0, 5)) != 0) {
        valid = true;
      }
      if (valid) {
        Word word;
        word.name = "";
        word.x = x;
        word.y = y;
        word.orient = "h";
        // store the starting coordinate of the word, as well as its orientation
        // (h or v)

        int k = x;
        while (k != 15 && alphabet.count(board[y][k].substr(0, 5))) {
          if (board[y][k].substr(0, 5) == "Blank") {
            word.name += board[y][k].substr(5);
          } else {
            word.name += board[y][k];
          }
          k++;
        }
        if (word.name.length() > 1) {
          words.push_back(word);
        }
      }
    }
  }
  return words;
}