#include "menus.h"
#include "boggle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <sys/poll.h>
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>


int getSize();
void displayBoard();
bool isValidWordHelper();

bool isValidWord(GameBoard * board, Trie* dictionary, char * inputWord){
    
    // ensure valid word
    if(!search(dictionary, inputWord)){
        printw("Word not in dictionary.\n");
        refresh();
        return false;
    }
    // ensure the word is on the board.
    // iterate every node.
    for (int i = 0; i < board->size; i++){
        for(int j = 0; j<board->size; j++){
            // make sure the node is the letter of the starting char
            if((!board->adj[i][j].value) == inputWord[0]){
                continue;
            }
            
            if(isValidWordHelper(board, inputWord, 0, i, j)){
                // reset the game board regardless of is word or not.
                unvisitGameBoard(board);
                return true;
            }
           
        }
    }
    // reset the game board
    unvisitGameBoard(board);
    return false;
}


bool isValidWordHelper(GameBoard * board, char *inputWord, int curIndex, int i, int j){
    
    if(inputWord[curIndex+1] == '\0'){
        return true;
    }
    // start search for word.
    // array of size of board (number of tiles).
    
    board->adj[i][j].visited = 1;
    
    // check east side of board for words 
    
    if(i + 1 < board->size){
        if(board->adj[i+1][j].value == inputWord[curIndex+1]  && !board->adj[i+1][j].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i+1, j)){
                return true;
            }
        }
    }
    // check west for words 
    if(i - 1 >= 0 ){
        if(board->adj[i-1][j].value == inputWord[curIndex+1] && !board->adj[i-1][j].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i-1, j)){
                return true;
            }
        }
    }
    // check south for words
    if(j + 1 < board->size ){
        if(board->adj[i][j+1].value == inputWord[curIndex+1] && !board->adj[i][j+1].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i, j+1)){
                return true;
            }
        }
    }
    // check north for words 
    if(j - 1 >= 0){
        if(board->adj[i][j-1].value == inputWord[curIndex+1] && !board->adj[i][j-1].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i, j-1)){
                return true;
            }
        }
    }
    
    // check south east for words
    if(i + 1 < board->size && j + 1 < board->size ){
        if(board->adj[i+1][j+1].value == inputWord[curIndex+1] && !board->adj[i+1][j+1].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i+1, j+1)){
                return true;
            }
        }
    }
    // check south west for words 
    if(i - 1 >= 0 && j + 1 < board->size ){
        if(board->adj[i-1][j+1].value == inputWord[curIndex+1] && !board->adj[i-1][j+1].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i-1, j+1)){
                return true;
            }
        }
    }
    // check north east for words 
    if(i + 1 < board->size && j - 1 >= 0 ){
        if(board->adj[i+1][j-1].value == inputWord[curIndex+1] && !board->adj[i+1][j-1].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i+1, j-1)){
                return true;
            }
        }
    }
    //check north west for words 
    if(i - 1 >= 0 && j - 1 >= 0 ){
        if(board->adj[i-1][j-1].value == inputWord[curIndex+1] && !board->adj[i-1][j-1].visited){
            if( isValidWordHelper(board, inputWord, curIndex+1, i-1, j-1)){
                return true;
            }
        }
    }
    
    // if it hits this case, have run out of valid options.
    board->adj[i][j].visited = 0;
    return false;
}



int getSize(){
    int boardSize = 0;
    clear();
    printw("Welcome to Boggle!\n");
    printw("Enter the game board size: (numeric values only) \n");
    printw("Please note that extremely large input will mess with display.\n");
    refresh();
    if(scanw("%d", &boardSize)) {
        return boardSize;
    }
    else {
        printw("Invalid. Press any key to continue.");
        refresh();
        getch();
        return 0 + getSize();
    }
}


/*void getWords(GameBoard* board, int i, int j, int size, char* userInput, int c, struct Trie * head){
    board->adj[i][j].visited = true;
    userInput[c] = board->adj[i][j].value;
    if (userInput[c] == 'q'){
        c++;
    }
    if (userInput[c] == 'u'){
            // do stuff
    }
} */

// get score function 
int getScore(char* wordInput) {
    int len = strlen(wordInput);
    int score = 0;
    if (len > 2 && len < 5){
        score = 1;
        score = score +1;
    } 
    if (len == 5){
        score = 2;
        score = score +2;
    } 
    if (len == 6) {
        score = 3;
        score = score +3;
    }
    if (len == 7){
        score = 4;
        score = score +4;
    } 
    if (len >= 8){
        score = 5;
        score = score +5;
    }

    return score;
}


void findWordsUtil(GameBoard *board, int **visited, Trie *dictionary, Trie *boardWords, int i, 
                   int j, char *str) 
{ 
    // Mark current cell as visited and append current character 
    // to str 
    visited[i][j] = 1; 
    char temp[2];
    temp[0] = board->adj[i][j].value;
    temp[1] = '\0'; 
    strcat(str, temp); 
  
    // If str is present in dictionary, then print it 
    if (strlen(str) > 2 && search(dictionary, str)) {
        //add valid word to tree
        insert(boardWords, str);
        //printw("%s\t", str);
        //refresh();
    }
  
    // Traverse 8 adjacent cells of boggle[i][j] 
    for (int row=i-1; row<=i+1 && row<board->size; row++) 
      for (int col=j-1; col<=j+1 && col<board->size; col++) 
        if (row>=0 && col>=0 && !visited[row][col]) 
          findWordsUtil(board,visited, dictionary, boardWords, row, col, str); 
  
    // Erase current character from string and mark visited 
    // of current cell as false 
    str[strlen(str) - 1] = '\0';
    visited[i][j] = 0; 
} 

// Prints all words present in dictionary. 
void findWords(GameBoard * board, Trie *dictionary, Trie *boardWords) { 
    // Mark all characters as not visited 
    int **visited;
    visited = malloc(board->size * sizeof(int *));
    for(int i = 0; i < board->size; i++) {
        visited[i] = malloc(board->size * sizeof(int));
    } 
    for (int i = 0; i < board->size; i ++){
        for (int j = 0; j < board->size; j++){
            visited[i][j] = 0;
        }
    }
  
    // Initialize current string 
    char *str = malloc(45 * sizeof(char));
    str[0] = '\0';
  
    // Consider every character and look for all words 
    // starting with this character 
    for (int i=0; i<board->size; i++) 
       for (int j=0; j<board->size; j++) 
             findWordsUtil(board, visited, dictionary, boardWords, i, j, str); 

    free(str);
    for(int i = 0; i < board->size; i++) {
        free(visited[i]);
    }
    free(visited);
}

int main(int argc, const char * argv[]) {
    
    initscr();
    //open text file
    char word[100] = "okay";
    FILE *fp;
    fp = fopen("words", "r");
    if(fp == NULL) {
        printw("System error: no words found for game play ;(\n");
        refresh();
        return 1;
    }

   Trie * head = createTrieNode();

    //while (fgets(word, 100, fp) != NULL){
    while(fscanf(fp, "%s", word)) {
        //word[strlen(word)-2] = '\0';

        insert(head, word);
        if(fgets(word, 100, fp) == NULL) 
            break;

    }
    fclose(fp);

    int playGame = 1;
    while(playGame) {
        int mainMenuOption = mainMenu();
        if(mainMenuOption == 1) {
            //ask for board size
            int highScore = 0;
            int s = getSize();
            int rematch = 1;
            while(rematch) {
                GameBoard *board = createGameBoard(s);
                Trie *boardWords = createTrieNode();
                // find words before game play 
                findWords(board, head, boardWords);
                displayBoard(s, board);
                char userInput[512];
                int totalScore = 0;
    
    
                time_t now;
                unsigned int endTime;
    
                // Obtain current time
                // time() returns the current time of the system as a time_t value
                time(&now);
    
                endTime = now + 30;
    
                // Convert to local time format and print to stdout
                printw("time is : %ld\n", now);
                refresh();
    
                do {
                    //play for 3 minutes 
                    struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
                    time(&now);
                    unsigned int timeLeft = endTime - now;
                    printw("Input a word:\n");
                    refresh();
                    // poll here
                    if(poll(&mypoll, 1, (timeLeft * 1000))){
                        scanw(" %s", userInput);
                    } else {
                        printw("Time's up!\n");
                        refresh();
                        break;
                    }
        

                    // check against the board and dictionary.
                    if(strlen(userInput) >= 3 && isValidWord(board, head, userInput)){
                        totalScore += getScore(userInput);
                        printw("valid word %s!\nCurrent score: %d\n",userInput, totalScore);
                        refresh();
                
                    } else {
                        printw("Not a word: '%s'. try again\n", userInput);
                        refresh();
            
                    }
        
                } while(1);

                if (totalScore > highScore){
                    highScore = totalScore;
                    printw("You got a high score of %d\n", highScore);
                    refresh();
                }
                char word[100];
                int level = 0;
                printTree(boardWords, word, level);
                printw("\nPress any key to continue.");
                refresh();
                getch();
                freeTree(boardWords);
                freeGameBoard(board);
                int endMenuOption = endMenu();
                if(endMenuOption == 1) {

                }
                else if(endMenuOption == 2) {
                    rematch = 0;
                }
                else if(endMenuOption == 3) {
                    rematch = 0;
                    playGame = 0;
                }
            }

        }
        else {
            playGame = 0;
        }
    }
    endwin();
    freeTree(head);
    return 0;
}

void displayBoard(int size, GameBoard* board) {
  printw("\n");
    for(int i=0; i< board->size; i++){
        for(int j=0;j<board->size;j++){
            printw("%c ",board->adj[i][j].value);
        }
        printw("\n");
    }
    refresh();
}




