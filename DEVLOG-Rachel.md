# Dev Log:

This document must be updated daily every time you finish a work session.

## Rachel Uvaydov

### 2026-01-06 - PROPOSAL.md+Branches, Updated plan
PROPOSAL.md was updated with the proposal my partner and I created (5 minutes), we joined the repo and created our branches (3 minutes). AT HOME: Updated main.c with a more detailed and thought out plan of how to achieve this, created p1.c and p2.c files with preliminary player1Logic() and player2Logic() functions and added them into main.h, updated makefile (1 hour).

### 2026-01-07 - Extra planning+starting logic functions, created templates of functions+worked more on logic functions
My partner and I spent most of our class time (~25 minutes) planning how to make this game work and rethinking our past ideas (like deciding to use an array for the board instead of a .txt file), an initial version of player1Logic() was created outlining where it would connect with player 2 and printing out initial messages to the player, saying what their token is and reading from stdin to ask for the move they want to make. AT HOME: main.c and main.h were updated with 3 new function templates: checkBoard, printBoard, and updateBoard, with comments on what they're supposed to do and what they return, the player1Logic() and player2Logic() functions were written to incorporate the new board functions and have full outlines for how a single Connect 4 game would be completed (but not a tournament yet), the only thing missing from the logic functions is actual communication between the 2 players (with comments showing where those need to be implemented), also updated makefile and main to fix a small issue (1.5 hours).

### 2026-01-08 - Reworked plan+added networking files, editing networking files
We asked Mr. K for advice during class and he told us to rework our plan and explained how we should go about it (~40 minutes), added files from networking lab for future use (5 minutes). AT HOME: Edited networking files with comments to reflect new plan (~20 minutes).

### 2026-01-09 - Editing networking files
The files from the networking lab were worked on to make them work for this project. Not everything was updated, so I added comments to certain places where more changes needed to be made (30 minutes).

### 2026-01-10 - Debugging+Updating files, Working versions of playerLogic and subserver_logic
After we reworked our plan, a lot of our old code got pushed to the side but we still needed it so I updated the makefile to correctly use main.c and main.h, I fixed an error with the player handshake function, I also changed old code that was causing errors because it was using player1Logic and player2Logic instead of our new playerLogic (1 hour). Reworked subserver_logic to take 2 sockets (one for each player), changed Server main() to incorporate both sockets as well, added the server logic so it reads from P1, sends to P2, reads from P2, then sends to P1 and so on, did the same for the playerLogic and main() functions in player.c, planning to make playerLogic less repetitive by using a helper function in the future (2 hours).

### 2026-01-11 - Fixed makefile+renamed files
I merged main with my partner's new code to my branch in order to test out her code to make sure it worked with mine. When I tried to run everything, it wasn't working and I realized something was wrong with the makefile, so I fixed it (10 minutes). I renamed main.c and main.h to game.c and game.h (more fitting names) and changed the other files accordingly (5 minutes). Lastly, I tested the code and besides the issues with the makefile, everything ran smoothly, except I realized the game wasn't ending when someone won, but did actually end once randomly after a non-game-ending move, so there must be an error with the checkBoard function. I don't have time to fix it currently so I'll notify my partner and try to look at it later if I have the time.

### 2026-01-12 - Updated printBoard+added to-do list, Sighandler+recv()==0
The board that printBoard prints was updated to look cleaner, with the row numbers removed because those are uneecessary (20 minutes), changed comments at the end of game.c to add a new list of things we need to do (10 minutes). AT HOME: Created sighandler function to detect SIGINT and tried implementing it, but it doesn't exactly work as intended, also add statements to exit the game when recv() returns 0 but also not working as intended, need to make sure that both players quit, because right now only one quits and the other is stuck in an infinite loop (1 hour).

### 2026-01-13 - Trying to fix error with players not closing at same time+New plan to fix player 1 and player 2 getting assigned incorrectly
Tried to figure out why only one player closed when server closed, we asked Mr. K what to do about assigning p1 and p2 in server and he suggested to just not ask the player for args and instead assign them based on who runs player first, so I will implement that in the future (30 minutes).

### 2026-01-14 - Updated files+Changing print messages, Working on implementing select
Updated makefile to get rid of ARGS when doing make player, changed print messages in server.c and player.c when game is ending due to signhandler, recv, or an error to make why the game is ending more clear (30 minutes). AT HOME: Worked on implementing select in player.c, the code compiles but both players freeze while running so I have to fix it (30 minutes).

### 2026-01-15 - Working on select, updating print statements, fixed makefile, recorded presentation video
Worked on implementing select, made some progress but it's still bugged (worked during all of class and for 30 minutes at home), AT HOME: Fixed error with makefile, updated print statements for errors and sighandler to make them more clear and detailed, worked with my partner to record our video for the presentation, fixed minor errors and bugs and I made sure everything was consistent with the code so it wouldn't break while presenting it (3 hours).
