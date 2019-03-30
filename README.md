# boggle-

Description-

This is a C implementation of the classic Boggle coded in C. A dictionary is read in as a file.


Link to Video Tutorial:


Downloading and Compiling:

General Notes About Gamplay:

Words File:
The file read in for gameplay uses the built in words file in the unix operating system. The file only scans in alpha characters.

Board Size:
The board size is taken from user input, but must be at least 2 x 2 to facilitate game play. It is encouraged to play Boggle in full screen mode to avoid scrolling. An error is returned if user input is not a valid number input. While the board size is arbitrary, larger inputs (user input greater than 50) will create a difficult to read display. 

Scoring the Game:
A word must be at 3 characters or greater to be scored if played. Duplicate words will only be scored once, and the highest score for each round played while the player continues game play will be displayed at the end of each game.