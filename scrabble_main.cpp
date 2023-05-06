// scrabble_main.cpp

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "functions.h"
using namespace std;

int main(){
    titleScreen();
    int numPlayers;
    cout << "How many players? (2-4): ";
    while (cin >> numPlayers){
        if (numPlayers < 2 || numPlayers > 4)
            cout << "\nInvalid input, please enter again: ";
        else
            break;
    }
    Player* playerlist = new Player[numPlayers]; // create a dynamic array of Player type
    for (int i=0; i<numPlayers; ++i){
        string name;
        cout << "Input name for player " << i+1 << ": ";
        while (cin >> name){
            bool valid=true;
            for (int j=0; j<numPlayers; j++){
                if (name==playerlist[j].name) {
                    valid = false;
                    break;
                }
            }
            if (!valid)
                cout << "Name already used, please enter again: ";
            else
                break;
        }
        playerlist[i].name = name;
    }
    vector<vector<string>> board =
        {{"TW","","","DL","","","","TW","","","","DL","","","TW"},
         {"","DW","","","","TL","","","","TL","","","","DW",""},
         {"","","DW","","","","DL","","DL","","","","DW","",""},
         {"DL","","","DW","","","","DL","","","","DW","","","DL"},
         {"","","","","DW","","","","","","DW","","","",""},
         {"","TL","","","","TL","","","","TL","","","","TL",""},
         {"","","DL","","","","DL","","DL","","","","DL","",""},
         {"TW","","","DL","","","","<>","","","","DL","","","TW"},
         {"","","DL","","","","DL","","DL","","","","DL","",""},
         {"","TL","","","","TL","","","","TL","","","","TL",""},
         {"","","","","DW","","","","","","DW","","","",""},
         {"DL","","","DW","","","","DL","","","","DW","","","DL"},
         {"","","DW","","","","DL","","DL","","","","DW","",""},
         {"","DW","","","","TL","","","","TL","","","","DW",""},
         {"TW","","","DL","","","","TW","","","","DL","","","TW"}};
    // initial setup of the scrabble board, in a 2-dimensional vector
    /* Note: we used a 2D vector, as opposed to a 2D array, because it's easier to copy the contents of a vector,
    which is needed later in the makeMove function */
    vector<string> letterbag =
        {"A","A","A","A","A","A","A","A","A","B","B","C","C","D","D","D","D",
         "E","E","E","E","E","E","E","E","E","E","E","E","F","F","G","G","G",
         "H","H","I","I","I","I","I","I","I","I","I","J","K","L","L","L","L",
         "M","M","O","O","O","O","O","O","O","O",
         "P","P","Q","R","R","R","R","R","R","S","S","S","S",
         "T","T","T","T","T","T","U","U","U","U","V","V",
         "W","W","X","Y","Y","Z","Blank","Blank"};
    // initial setup of the letterbag, in a vector
    default_random_engine rng(random_device{}());
    shuffle(letterbag.begin(), letterbag.end(), rng);
    shuffle(playerlist, playerlist+numPlayers, rng);
    for (int i=0; i<numPlayers; i++){
        for (int j=0; j<7; j++){
            string tile = letterbag.back();
            letterbag.pop_back();
            playerlist[i].tiles.push_back(tile);
        }
    }
    string input;
    cout << "\nThe randomly assigned player order is:" << endl;
    for (int i=0; i<numPlayers-1; i++)
        cout << playerlist[i].name << " -> ";
    cout << playerlist[numPlayers-1].name << endl;
    cout << "Pass the device to " << playerlist[0].name << "." << endl;
    cout << "Press Enter when you are ready to begin" << endl;
    getline(cin, input);
    getline(cin, input);

    bool gameOver=false;
    int turn=0, passcount=0;
  
    // main game loop
    while (!gameOver) {
        bool passed = makeMove(turn, numPlayers, letterbag, board, playerlist);
        // returns true if the user passed on their turn, returns false otherwise
        turn = (turn+1)%numPlayers;
        if (passed) passcount += 1;
        else passcount = 0;

        int playersLeft=0, tilesLeft=0;
        for (int i=0; i<numPlayers; i++){
            if (playerlist[i].score != -1) 
              // player's score is set to -1 upon resignation
                playersLeft += 1;
            tilesLeft+=playerlist[i].tiles.size();
        }
        if (playersLeft == 1 || passcount == playersLeft*2 || tilesLeft == 0){
        // (if only one player has not resigned || too many passes || no one has any tiles left)
            gameOver = true;
            break;
        } else {
            while(playerlist[turn].score == -1) {
                turn = (turn+1)%numPlayers;
            }
        }
        cout << "\033[2J\033[H";
        cout << "Next up: " << playerlist[turn].name << endl;
        cout << "Number of consecutive passes: " << passcount << endl;
        cout << "(If this hits " << playersLeft*2 << ", the game will end)\n";
        cout << "Press Enter when you are ready";
        getline(cin, input);
    }
    cout << "\033[2J\033[H"; // clears the console screen
    vector<string> winners;
    int highest=0;
    for (int i=0; i < numPlayers; i++){
        if (playerlist[i].score > highest)
            highest = playerlist[i].score;
    }
    for (int i=0; i < numPlayers; i++){
        if (playerlist[i].score == highest)
            winners.push_back(playerlist[i].name);
    }
    if (winners.size()==1) // only one winner
        cout << winners[0] << " has won the game! Congratulations!\n";
    else { // more than one winner (a tie)
        cout << "It's a tie between ";
        for (int j=0; j<winners.size()-2; j++){
            cout << winners[j] << ", ";
        }
        cout << winners[winners.size()-2] << " and " << winners.back() << "!\n";
    }
    cout << endl;
    cout << "The final scores were:\n";
    for (int i=0 ; i < numPlayers; i++){
        cout << playerlist[i].name << ": ";
        if (playerlist[i].score == -1) cout << "Resigned\n";
        else cout << playerlist[i].score << endl;
    }
    return 0;
}
