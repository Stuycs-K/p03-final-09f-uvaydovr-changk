# Dev Log:

This document must be updated daily every time you finish a work session.

## Katherine Chang

### 2026-01-06 | 2:40 PM (10 minute class period)
Setting up files and outlining plan in PROPOSAL.md at school and home.

### 2026-01-08 | ~1:20 AM (for 01-07)
Discussed project in class. Trying to figure out how to start and whether to use sockets/semaphores and struct vs file to store the data.
Tried to work on semaphore logic at home.

### 2026-01-08 | ~1:30 AM
Figured out that we need a server, two clients, and sockets in class. Started working on switching from semaphores to sockets based on prior networking lab. Created player.c to try and merge player c files. Mostly testing connections to server and clients.

### 2026-01-11 | 9:21 PM | Reworking game logic + fixing networking bugs
- Rebuilt game logic in main.c. Wrote printBoard so it processes a 2D board array instead of a malloced string. Implemeneted updateBoard with column checkers so it drops a token from the bottom of the column upward. Also added a new field to take in token. Wrote checkBoard to scan vertical, horizontal, and diagonal possibilities. Initially returned 1 or 2 depending on player but changed it to 'X' or "O.' Tested functions in separate test_game with no networking.
- Connected playerLogic to new functions in main.c. Simplifies playerLogic code to be less repetitive and added token/oppToken/oppositePlayer. Initialized board with '_' instead
- Debugging: Removed int *rBuff and int\*sBuff that was allocated with malloc but then passed sizeof(rBuff) or sizeof(sBuff) to recv/send. sizeof(pointer) isn't sizeof(int). Resulted in weird moves like 'X' appearing in column 0 even though it was never selected. Replaced with int rBuff and int sBuff. Also fixed infinite "column X is already filled" loop caused by repeatedly calling updateBoard. Fixed incorrect winner/loser logic so that the resulting message was correct.
- Removed extra main and client.c entirely because it was repetitive and didn't work.
(~4 hours in total)
