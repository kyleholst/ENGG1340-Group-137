// countPoints.cpp

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "functions.h"
using namespace std;

int countPoints(vector<Word> words, vector<vector<string>> board, vector<vector<string>> oldboard) {
    int score = 0;
    for (Word i : words) {
        int tempscore = 0;
        int x = i.x; // get coordinates of current word
        int y = i.y; 
        string orient = i.orient; // orientation of the current word ('h' for horizontal, 'v' for vertical)
        int DW = 0, TW = 0; // keep track of the number of double-word and triple-word squares covered by the word
        // iterate over the cells of the current word
        while (true) {
            // check if the current cell has a double-letter score modifier
            if (oldboard[y][x] == "DL") {
                tempscore += scorer(board[y][x]) * 2; // add the score of the current letter multiplied by 2 to the temporary score
            // check if the current cell has a triple-letter score modifier
            } else if (oldboard[y][x] == "TL") {
                tempscore += scorer(board[y][x]) * 3; // add the score of the current letter multiplied by 3 to the temporary score
            // if the current cell doesn't have a letter score modifier, just add the score of the current letter to the temporary score
            } else {
                tempscore += scorer(board[y][x]);
                // check if the current cell has a double-word score modifier or a start square (represented by '<>')
                if (oldboard[y][x] == "DW" || oldboard[y][x] == "<>") {
                    DW += 1; // increment the number of double-word squares covered by the word
                // check if the current cell has a triple-word score modifier
                } else if (oldboard[y][x] == "TW") {
                    TW += 1; // increment the number of triple-word squares covered by the word
                }
            }
            // move to the next cell based on the word orientation
            if (orient == "v") {
                y += 1; // if the word is vertical, increment the y-coordinate
            } else if (orient == "h") {
                x += 1; // if the word is horizontal, increment the x-coordinate
            }
            // if we have processed all the letters in the word, exit the loop
            if (x - i.x == i.name.length() || y - i.y == i.name.length()) {
                break;
            }  
        }
        // apply the word score multipliers (double-word and triple-word squares)
        tempscore *= pow(2, DW) * pow(3, TW);
        score += tempscore; // add the temporary score to the total score for all words
    }
    return score; // return the total score for all words
}