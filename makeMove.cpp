// makeMove.cpp

#include "functions.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool operator==(Word a, Word b) {
  return (a.name == b.name && a.x == b.x && a.y == b.y && a.orient == b.orient);
}

bool makeMove(int turn, int n, vector<string>& letterbag,
              vector<vector<string>>& board, Player *playerlist) {

  // n represents size of playerlist
  vector<vector<string>> oldboard(board); // copies 'board' to 'oldboard'
  bool complete = false;
  vector<Word> newtiles;
  set<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
                          "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                          "S", "T", "U", "V", "W", "X", "Y", "Z", "Blank"};

  while (!complete) {
    // loops until player turn is over
    displayBoard(turn, n, letterbag.size(), board, playerlist);
    cout << "What's your move?\n";
    string input_str, move_str;
    getline(cin, input_str);
    istringstream iss(input_str);
    char delimiter = ' ';
    vector<string> move;
    while (getline(iss, move_str, delimiter)) {
      move.push_back(move_str);
    }

    if (!move.empty()) {
      if (move[0] == "blank") {
        move[0] = "Blank";
        /* Normally, lowercase and uppercase distinction matters, to tell the
        difference between tile input and command input. 'Blank' is the
        exception to this, so we add these lines of code to allow both 'Blank'
        and 'blank' as input. */
      }
    }
    set<string> valid_moves = {"s", "e", "p", "r", "f", "del", "search", "blank"};
    if (move.empty() ||
        (valid_moves.count(move[0]) == 0 && alphabet.count(move[0]) == 0) ||
        move.size() > 2) {
      cout << "Invalid selection, enter again!\n";
      cout << "Press Enter to continue\n";
      getline(cin, input_str);

    } else if (move[0] == "s") {
      // shuffle player's held tiles
      default_random_engine rng(random_device{}());
      shuffle(playerlist[turn].tiles.begin(), playerlist[turn].tiles.end(),
              rng);

    } else if (move[0] == "f") {
      // player finishes their turn
      if (newtiles.empty()) {
        cout << "You can't finish without making a move!\n";
        cout << "If you want to pass your turn, type 'p' instead.\n";
        cout << "Press Enter to continue\n";
        getline(cin, input_str);
        continue;
      } else if (oldboard[7][7] == "<>" && newtiles.size() == 1) {
        cout << newtiles[0].name << " is not an accepted word!\n";
        cout << "Press Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      vector<int> allx, ally;
      for (Word tile : newtiles) {
        allx.push_back(tile.x);
        ally.push_back(tile.y);
      }
      if (count(allx.begin(), allx.end(), allx[0]) != allx.size() && 
        count(ally.begin(), ally.end(), ally[0]) != ally.size()) {
        cout << "All placed tiles must be in a straight line!" << endl;
        getline(cin, input_str);
        continue;
      }
      vector<Word> newwords = findWords(board);
      vector<Word> oldwords = findWords(oldboard);
      vector<Word> words;
      for (Word i : newwords) {
        if (find(oldwords.begin(), oldwords.end(), i) == oldwords.end()) {
          words.push_back(i);
        }
      }
      bool valid = true;
      for (Word i : words) {
        if (!dictSearch(i.name)) {
          valid = false;
          cout << i.name << " is not an accepted word!\n";
        }
      }
      if (valid) {
        playerlist[turn].score += countPoints(words, board, oldboard);
        if (newtiles.size() == 7) {
          playerlist[turn].score += 50; // 50 bonus points for using 7 tiles in one turn
        }
        for (int i = 0; i < newtiles.size(); i++) {
          if (!letterbag.empty()) {
            playerlist[turn].tiles.push_back(letterbag.back());
            letterbag.pop_back();
          }
        }
        complete = true;
      } else {
        cout << "Press Enter to continue:\n";
        getline(cin, input_str); // Wait for Enter key to be pressed
      }

    } else if (move[0] == "e") {
      // Player exchanges their letters
      if (letterbag.empty()) {
        cout << "The bag is empty!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      for (Word i : newtiles) {
        // Returns any tiles on the board to the player's hand
        board[i.y][i.x] = oldboard[i.y][i.x];
        playerlist[turn].tiles.push_back(i.name);
      }
      newtiles.clear();
      displayBoard(turn, n, letterbag.size(), board, playerlist);
      cout << "What tiles would you like to replace?\n";
      cout << "(E.g. to replace the tiles E, C and D, type 'E C D')\n";
      cout << "(To cancel, type 'cancel')\n";
      string replace_str, tile_str;
      getline(cin, replace_str);
      istringstream iss2(replace_str);
      vector<string> replace;
      while (getline(iss2, tile_str, delimiter)) {
        replace.push_back(tile_str);
      }
      if (replace.empty()) {
        cout << "Invalid selection, enter again!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      if (replace[0] == "cancel") {
        continue;
      }
      bool valid = true;
      for (string i : replace) {
        if (count(replace.begin(), replace.end(), i) >
            count(playerlist[turn].tiles.begin(), playerlist[turn].tiles.end(),
                  i)) {
          valid = false;
        }
      }
      if (!valid) {
        cout << "Invalid selection, enter again!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      // Player input validated
      for (string i : replace) {
        playerlist[turn].tiles.erase(find(playerlist[turn].tiles.begin(),
                                          playerlist[turn].tiles.end(), i));
      }
      letterbag.insert(letterbag.end(), replace.begin(), replace.end());
      default_random_engine rng(random_device{}());
      shuffle(letterbag.begin(), letterbag.end(), rng);
      for (int i = 0; i < replace.size(); i++) {
        playerlist[turn].tiles.push_back(letterbag.back());
        letterbag.pop_back();
      }
      complete = true;

    } else if (move[0] == "p") {
      // Player passes their turn
      for (Word i : newtiles) {
        board[i.y][i.x] = oldboard[i.y][i.x];
        playerlist[turn].tiles.push_back(i.name);
      }
      return true;
      // scrabble_main.cpp counts the number of consecutive passes
      // In this case, the user has passed, so the return value is true

    } else if (move[0] == "r") {
      // Player resigns
      playerlist[turn].score = -1;
      for (Word i : newtiles) {
        // Returns any tiles on the board to the player's hand
        board[i.y][i.x] = oldboard[i.y][i.x];
        playerlist[turn].tiles.push_back(i.name);
      }
      for (string i : playerlist[turn].tiles) {
        letterbag.push_back(i);
      }
      playerlist[turn].tiles.clear();
      complete = true;

    } else if (move[0] == "search") {
      // Player checks to see if a word is legal
      if (move.size() == 1) {
        cout << "Invalid selection, enter again!\nPress Enter to continue\n";
        getline(cin, input_str);
      }
      transform(move[1].begin(), move[1].end(), move[1].begin(), ::toupper);
      bool valid = true;
      for (char i : move[1]) {
        string s(1, i);
        if (alphabet.count(s) == 0) {
          valid = false;
        }
      }
      if (valid) {
        if (dictSearch(move[1]) == true) {
          cout << move[1] << " is an accepted word.";
        } else {
          cout << move[1] << " is not an accepted word.";
        }
      } else {
        cout << "Invalid selection, please input again!\nPress Enter to "
                "continue\n";
      }
      getline(cin, input_str);

    } else if (move[0] == "del") {
      // Player removes one of their placed tiles from the board
      if (move.size() == 1) {
        cout << "Invalid selection, enter again!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      if (move[1] == "all") {
        // Player removes all tiles from the board at once
        for (Word i : newtiles) {
          board[i.y][i.x] = oldboard[i.y][i.x];
          playerlist[turn].tiles.push_back(i.name);
        }
        newtiles.clear();
        continue;
      }
      bool found = false;
      int x = int(move[1][0] - 65);
      int y = stoi(move[1].substr(1));
      for (Word i : newtiles) {
        if (i.x == x && i.y == y) {
          found = true;
        }
      }
      if (!found) {
        cout << "You can't remove that!\nPress Enter to continue'\n";
        getline(cin, input_str);
        continue;
      }
      // Input successfully validated
      if (board[y][x].substr(0, 5) == "Blank") {
        playerlist[turn].tiles.push_back("Blank");
      } else {
        playerlist[turn].tiles.push_back(board[y][x]);
      }
      board[y][x] = oldboard[y][x];
      for (Word i : newtiles) {
        if (i.x == x && i.y == y) {
          newtiles.erase(find(newtiles.begin(), newtiles.end(), i));
        }
      }
    } else {
      // Player places a tile on the board
      if (move.size() == 1) {
        cout << "Invalid selection, enter again!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      string tile = move[0];
      char in_x = move[1][0];
      int in_y = stoi(move[1].substr(1));
      set<string> nontile = {"", "DL", "TL", "DW", "TW", "<>"};
      if (count(playerlist[turn].tiles.begin(), playerlist[turn].tiles.end(), tile) == 0) {
        cout << "You don't have that letter!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      } else if ((in_x < 'A' || in_x > 'O') || (in_y < 0 || in_y > 14)) {
        cout << "Invalid coordinate!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      } else if (board[7][7] == "<>" && move[1] != "H7") {
        cout << "First tile must be on the middle square <>!\nPress Enter to "
                "continue\n";
        getline(cin, input_str);
        continue;
      } else if (nontile.count(board[in_y][int(in_x - 65)]) == 0) {
        cout << "There's already a tile there!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
      // Below code is only executed after player input is fully validated
      int x = int(in_x - 65);
      int y = in_y;
      bool adjacent = false;
      try {
        if (alphabet.count(board[y][x + 1].substr(0, 5)))
          adjacent = true;
      } catch (...) {
      }
      try {
        if (alphabet.count(board[y][x - 1].substr(0, 5)))
          adjacent = true;
      } catch (...) {
      }
      try {
        if (alphabet.count(board[y + 1][x].substr(0, 5)))
          adjacent = true;
      } catch (...) {
      }
      try {
        if (alphabet.count(board[y - 1][x].substr(0, 5)))
          adjacent = true;
      } catch (...) {
      }
      // The try statements are to catch out of range errors with the board 2D
      // vector array.
      if (adjacent || board[7][7] == "<>") {
        if (tile != "Blank") {
          Word temp;
          temp.name = tile;
          temp.x = x;
          temp.y = y;
          newtiles.push_back(temp);
          board[y][x] = tile;
          playerlist[turn].tiles.erase(find(playerlist[turn].tiles.begin(), playerlist[turn].tiles.end(), tile));
        } else {
          cout << "What letter would you like to play the Blank as?\n";
          cout << "Type 'cancel' to cancel.\n";
          string blankletter;
          cin >> blankletter;
          if (blankletter == "cancel") continue;
          if (blankletter == "Blank" || alphabet.count(blankletter) == 0) {
              cout << "Invalid, please input again!\nPress Enter to continue\n";
              getline(cin, input_str);
              continue;
          } else {
            Word temp;
            temp.name = "Blank";
            temp.x = x;
            temp.y = y;
            newtiles.push_back(temp);
            board[y][x] = "Blank"+blankletter;
            playerlist[turn].tiles.erase(find(playerlist[turn].tiles.begin(), playerlist[turn].tiles.end(), "Blank"));
            continue;
          }
        }
      } else {
        cout << "New tiles have to be adjacent to old ones!\nPress Enter to continue\n";
        getline(cin, input_str);
        continue;
      }
    }
  }
  string dummy;
  cout << "Turn complete!\nPress Enter to continue\n";
  getline(cin, dummy);
  return false;
  // scrabble_main.cpp counts the number of consecutive passes
  // In this case, the user has not passed, so the return value is false
}
