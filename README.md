# boggle-

Description-

This is a C implementation of the classic Boggle coded in C. A dictionary is read in as a file.


Link to Video Tutorial:
```bash
youtube link
```


Downloading and Compiling:
```bash
the repository
```

General Notes About Gamplay:

Words File:
The file read in for gameplay uses the built in words file in the unix operating system. The file only scans in alpha characters.

Board Size:
The board size is taken from user input, but must be at least 3 x 3 to so that the user can find a word. It is encouraged to play Boggle in full screen mode to avoid scrolling. An error is returned if user input is not a valid number input. While the board size is arbitrary, larger inputs (user input greater than 50) will create a difficult to read display. 

Scoring the Game:
A word must be at 3 characters or greater to be scored if played. Duplicate words will only be scored once, and the highest score for each round played while the player continues game play will be displayed at the end of each round.
< 3 letters: No points granted 
3 Letters: 1 point granted 
4 Letters: 1 point granted
5 Letters: 2 points granted 
6 Letters: 3 points granted
7 Letters: 4 points granted 
8 Letters: 5 points granted

The highest score will hold as e

Playing the Game: 
Any board size greater than 5 will take significant time to load. Words can be constructed by inputting any letter above, beneath, to the left, and to the right of a letter, including all diagonals. Words must no less than 3 letters in length, and must be in the dictionary to receive credit. 

