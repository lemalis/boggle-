#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boggleDataStructures.c"
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
    
    // create a queue.
    //Queue * q = (Queue *)malloc(sizeof(Queue));
    // insert the first board element into the queue.
    //enqueue(q, board->adj[i][j].value);
    
    // printf("Checking: i=%d,j=%d, curIndex=%d\n",i,j,curIndex); // DELETE
    // mark current start node as visited
    // SEGFAULT 11. perhaps instead of a guitile, a temporary gameboard.
    board->adj[i][j].visited = 1;
    // iterate as long as the queue isn't empty
    
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


void getWords(GameBoard* board, int i, int j, int size, char* userInput, int c, struct Trie * head){
    board->adj[i][j].visited = true;
    userInput[c] = board->adj[i][j].value;
    if (userInput[c] == 'q'){
        c++;
    }
    if (userInput[c] == 'u'){
            // do stuff
    }
}

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


void gameplayLoop(){
    
}

int main(int argc, const char * argv[]) {
    
    initscr();
	//open text file
    char word[100];
    FILE *fp;
    fp = fopen("words", "r");
    if(fp == NULL) {
        printw("System error: no words found for game play ;(\n");
        refresh();
        return 1;
    }

   Trie * head = createTrieNode();

    while (fgets(word, 100, fp) != NULL){
    	word[strlen(word)-2] = '\0';

    	insert(head, word);

    }
    fclose(fp);
    //system("clear");
    clear();

    
    // ask for board size
    int s = getSize();
   
	GameBoard *board = createGameBoard(s);
    
    printw("\n");
    for(int i=0; i<s; i++){
        for(int j=0;j<s;j++){
            printw("%c ",board->adj[i][j].value);
        }
        printw("\n");
    }
    refresh();
    

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
        
        
        if(userInput[0] == '\n'){
            
            printw("Exiting %s\n",userInput);
            refresh();
            break;
        }
        // check against the board and dictionary.
        if(isValidWord(board, head, userInput)){
            totalScore += getScore(userInput);
            printw("valid word %s!\nCurrent score: %d\n",userInput, totalScore);
            refresh();
            
        } else {
            printw("Not a word: '%s'. try again\n",userInput);
            refresh();
            
        }
        
    } while(1);

    printw("\nPress any key to continue.");
    refresh();
    getch();
    endwin();

      return EXIT_SUCCESS;
}

void displayBoard(int size, GameBoard* board) {
  printw("Does anything happen?");
  int j = size;
    while (j != 0) {
        printw("------");
        j--;
    }
    printw("\n");

    for (int i = 0; i < size; i++) {
        printw("|  ");
        for (int j = 0; j < size; j++) {
            if (board->adj[i][j].value == 'Q')
                printw("Qu ");
            else
                printw("%c  ", board->adj[i][j].value);
            if (j == size - 1)
                printw("|");
        }
        printw("\n");
    }

    while (j != size) {
        printw("----");
        j++;
    }
    printw("\n");
    refresh();
    return;
}




