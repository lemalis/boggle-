# boggle-

Laura Malis 

Description-

This is a C implementation of the classic Boggle coded in C. A dictionary is read in as a file. 


Link to Video Tutorial:
```bash
https://www.youtube.com/watch?v=AgP60CrVOaM
```


Downloading and Compiling:
```bash
https://github.com/lemalis/boggle-
```
Clone using link, make using "make", and execute using "./boggle"

General Notes About Gamplay:

Words File:
The file read in for gameplay uses the built in words file in the unix operating system. The file only scans in alpha characters. If you are playing on a different operating system other than Mac OS, you will need to find a dictionary file, rename it "words", and move it into the same file for gameplay. 

Board Size:
The board size is taken from user input, but must be at least 3 x 3 to so that the user can find a word. It is encouraged to play Boggle in full screen mode to avoid scrolling. An error is returned if user input is not a valid number input. While the board size is arbitrary, larger inputs (user input greater than 50) will create a difficult to read display. 

Scoring the Game:
A word must be at 3 characters or greater to be scored if played. Duplicate words will only be scored once, and the highest score for each round played while the player continues game play will be displayed at the end of each round. Duplicate words will only be scored once. 
< 3 letters: No points granted 

3 Letters: 1 point granted <br/>
4 Letters: 1 point granted <br/>
5 Letters: 2 points granted <br/>
6 Letters: 3 points granted <br/>
7 Letters: 4 points granted <br/>
8 or more Letters: 5 points granted <br/>

The highest score will hold as long as the player continues playing with the same board size in the same round. If the score from the previous round is not replaced with a higher score, a new high score will not be displayed as a new high score was not reached. 

Playing the Game: 
Any board size greater than 5 will take significant time to load. Words can be constructed by inputting any letter above, beneath, to the left, and to the right of a letter, including all diagonals. Words must be no less than 3 letters in length, and must be in the dictionary to receive credit. In order to ensure that at least one word has been entered, the user will have one more chance to enter a word once time has run out. 


**Repository notes:
Due to repository difficulties in the midst of this project, a new repository had to be made. To see old repository and view more code history, please see the below link. **

```bash
https://github.com/lemalis/CS201_Portfolio-

```



