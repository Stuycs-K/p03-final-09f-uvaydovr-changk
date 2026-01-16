[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QfAIDTGi)
# CONNECT FOUR

### OutletBird

Rachel Uvaydov, Katherine Chang

### Project Description:

A two player Connect Four tournament game with a central server. Players are assigned as X or O and can take turns dropping pieces into a shared board.
When a game ends, the server records the winner's name in a leaderboard. Multiple games can be played over time, and wins accumulate across games.

### Instructions:

#### How to Run
From the project directory: 
```
make compile	# build server and player
make server 	# starts the server (Terminal 1)

```

Then, in two other terminals on the same machine:
```
make player       
```

You can end the game with ```Ctrl+C``` - this will end all active games if run in the server, and it will quit the current game if in player.
Run ```make clean``` to reset the tournament and clear files and leaderboard.

#### How to Play
For each player:
1. On start, enter your name when prompted. The server assigns you Player 1 or Player 2 based on the order that you joined and prints your token. The board shows columns 0-6.
2. On your turn, enter a number from 0-6. If the column is invalid or full, you’ll see an error and be asked again.
3. When it's the opponent's turn, your client will tell you to wait and updates the board after their move.
4. The game ends when someone connects four in a row (winner is then announced), or the board is full (draw).

After a win, the server records the winner's name in leaderboard.txt and prints an updated tournament leaderboard.

### Resources/ References:
Beej's Guide to Network Programming Using Internet Sockets  
https://beej.us/guide/bgnet/html/
