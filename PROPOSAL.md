# Final Project Proposal

## Group Members:

Rachel Uvaydov, Katherine Chang

# Intentions:

We intend to create a Connect Four tournament game in which two people can compete against each other using separate terminals.

# Intended Usage:

The two players will be assigned Player 1 and Player 2, each with their own tokens (as of now, we’re using X and O, but that may change in the future). The terminal for Player 1 will print out an empty board, then ask which column they’d like to place a piece in. While Player 1 is taking their turn, Player 2 will get a message that Player 1 is thinking, and once Player 1 is done, the board will be printed for Player 2, and so on. If a player chooses an invalid column (one that doesn’t exist or that is already filled) they will get an error, and the game will again ask what column they’d like to put a piece in. The game ends when a player manages to connect 4 pieces or when all the columns are filled.

# Technical Details:

To accomplish this, we’ll need to allocate memory to certain variables that store necessary information about the game. We’ll also utilize either processes (likely forking) or writing/reading from files to store information about all of the games in each tournament. To communicate between the players, we’ll use either pipes or sockets to allow information to be transferred between the two players. We’ll likely use signals to make sure that if one player quits the game, the other will too and will get a specific message printed. We will likely add other topics that have been covered in class as we progress through the project. To break this down, we may have one person focusing on storing information throughout the entire tournament, while the other focuses on communication between the two active processes playing the game.

# Intended Pacing:

We’ll probably start by trying to make the game playable between two different active windows, which will likely be the hardest part, as we’ll have to make sure the pieces go to the correct spot on the board every time one is played, and check if there is a four in a row to end the game. Once we get the game itself working (hopefully after 2-4 days), we can start coding the tournament and keeping track of how many games each person has won (which will probably only take 1 or 2 days). If we have extra time, we can try to add extra features to the game, possibly something like cool visuals or extra modes/customizations for the tournament.
