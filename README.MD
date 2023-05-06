------------------------------------------------------------------------
                         === Scrabble™ ===
------------------------------------------------------------------------         
  designed by HICKS Daniel (3036063682), BAHUKHANDI Ravi (3036086270), 
KHAN Farhan (3035962087), TAN Megan (3035977812), HOLST Kyle (3036050350)

                            === * ===
------------------------------------------------------------------------
Scrabble™ is a simple word game that accommodates 2, 3, or 4 players. 
By placing letter tiles on the Scrabble™ playing board, players aim 
to construct crossword-style words with varying score values to try 
and score as many points as possible. The player with the highest 
scorewill win, so each player must carefully choose and arrange their
tiles in ways that best utilise the board's Bonus Squares to get the
highest points.

-------------------------------------------------------------------------
    ===  QUICK START  ===
-------------------------------------------------------------------------
* Download and unzip the file
* Navigate to the directory which the folder is unzipped in
* Type "make" in the Terminal and wait for code to execute
* Type "./scrabble"
* Follow the printed instructions on the console to play the game


------------------------------------------------------------------------
    ===  HOW TO PLAY  ===
------------------------------------------------------------------------
* Press [Enter] to exit the titlescreen and begin the initialization.
* Input the number of players and the names of each player when asked.
* The system will randomly assign a player to start. 
* Now, everyone is ready to play Scrabble™.

* At a players turn, they must first press [Enter] to display their tiles
* Note: The tiles include the letter followed by their point value. 'x' 
  represeents 10 points (ie. the tile Qx is worth 10 points)
* On each turn, the player has the following options:
------------------------------------------------------------------------
1.(a)  <Tile> <Coord> 
- Player places <Tile> at <Coord>. The player is required to enter the 
  tile (the tile they wish to play) and the coordinate (where the letter 
  will be placed). e.g. ‘Z A0’ would place the 'Z' tile at coordinate A0. 

1.(b) del <Coord>
- Removes the tile at <Coord>. The player is only required to enter the
  coordinate of the letter they want to remove. (The player can only 
  remove tiles placed by the player within that turn.) The removed letter 
  will be put back into your hand.

2. s (shuffle)
- The system rearranges the player’s tiles. 

3. f (finish)
- Players are required to enter ‘f’ to tell the system to end the turn 
  if the turn is not ended automatically.

4. e (exchange)
- The player chooses which letter(s) to replace and the player’s turn 
  ends automatically.

5. p (pass)
- The player ends their turn without making any moves.

6. r (resign)
- The player resigns from the game. The accumulated scores of the player 
  will return to zero. Tiles owned by the player will be returned to the 
  letterbag.

7. search <Word>
- Checks if a word is accepted.
-------------------------------------------------------------------------
* For special cases, if additional inputs are required, instructions will
  be displayed on the screen. Simply follow these instructions to complete
  the turn.
* At the end of each turn, players are required to press ‘Enter’ to pass
  their turn to the next player.
-------------------------------------------------------------------------
    ===  ENDING THE GAME  ===
-------------------------------------------------------------------------
* If every tile has been placed, the game will end.
* Should all players pass twice in succession, the game will also end.
* The winner is decided by whoever has the highest score at the end of
  the game. If multiple people share the highest score, the result will 
  be a tie.

------------------------------------------------------------------------
    ===  FEATURES  ===
------------------------------------------------------------------------
* Randomized choice for starting player and tile selection every turn
* All major functions (eg. making the move, checking word validity, 
  score keeping, etc) in separate files
* 26 external textfiles of accepted Scrabble words imported and used
  in the function dictSearch() to check validity of player word inputs
* Dynamic array of the struct Player which stores players information 
  (names, scores, and tiles)
* Board information stored in a 2-dimensional vector to be used and 
  updated each turn

------------------------------------------------------------------------
 * NO NON-STANDARD C/C++ LIBRARIES USED
------------------------------------------------------------------------