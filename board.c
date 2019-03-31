#include "board.h"
#include <stdio.h>
#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <ncurses.h>



// create gameboard and randomly assign letters to board
GameBoard * createGameBoard( int size){
    GameBoard * board = malloc(sizeof(GameBoard));
    board->size = size;
    board->vertices = size*size;
    time_t t;
    srand((unsigned) time(&t));
    
    GuiTile ** tiles = (GuiTile **)malloc(size * sizeof(GuiTile *));
    for(int i=0; i<size; i++){
        tiles[i] = (GuiTile *)malloc(size * sizeof(GuiTile));
        for(int j=0;j<size;j++){
            // take a random number 0-25
            int r = rand() % 25;
            // pick a letter and assign it.
            tiles[i][j].value = (char) r + 97;
        }
    }
    
    board->adj = tiles;
    // the board is initialized, return.
    return board;
}
// free gameboard memory
void freeGameBoard(GameBoard * board){
    for (int i = 0; i < board->size; i++){
        free (board->adj[i]);
    }
    free (board->adj);
    free(board);
}
// unvisit tiles if word is incomplete
void unvisitGameBoard(GameBoard * board){
    for(int i=0;i< board->size;i++){
        for(int j=0; j<board->size;j++){
            board->adj[i][j].visited = 0;
        }
    }
}

// display board as i x j
void displayBoard(int size, GameBoard* board) {
  printw("\n");
  printw("You're playing Boggle!\n");
    for(int i=0; i< board->size; i++){
        for(int j=0;j<board->size;j++){
            printw("%c ",board->adj[i][j].value);
        }
        printw("\n");
    }
    refresh();
}

