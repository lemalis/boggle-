//
//  boggleStructures.c
//  BoggleGame
//
//

#include "boggle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <ncurses.h>


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

void freeGameBoard(GameBoard * board){
    for (int i = 0; i < board->size; i++){
        free (board->adj[i]);
    }
    free (board->adj);
    free(board);
}

void unvisitGameBoard(GameBoard * board){
    for(int i=0;i< board->size;i++){
        for(int j=0; j<board->size;j++){
            board->adj[i][j].visited = 0;
        }
    }
}


// init a new trie node
Trie *createTrieNode(){
    Trie *node = (Trie *)malloc(sizeof(Trie));
    node->isWord = 0;
    
    for (int i = 0; i < 26; i++)
        node->characters[i] = NULL;
    
    return node;
}
// add word to trie
void insert(Trie *head, char *str)
{
    // start from root node
    Trie *curr = head;
    int i =0;
    while (i < strlen(str))
    {
        str[i] = tolower(str[i]);
        if(!isalpha(str[i])){

            i++;

            continue;
        }
        // create a new node if path doesn't exists
        if (curr->characters[str[i] - 'a'] == NULL)
            curr->characters[str[i] - 'a'] = createTrieNode();
        
        // go to next node
        curr = curr->characters[str[i] - 'a'];
        
        // move to next character
        //str++;
        i++;
    }
    
    // mark current node as leaf
    curr->isWord = 1;
}

// search a trie
int search(Trie* head, char* str)
{
    // return 0 if Trie is empty
    if (head == NULL)
        return 0;
    
    Trie* curr = head;
    while (*str)
    {
        // go to next node
        curr = curr->characters[*str - 'a'];
        
        // if string is invalid (reached end of path in Trie)
        if (curr == NULL) {
            return 0;
        }
        
        // move to next character
        str++;
    }
    
    // if current node is a leaf and has reached the
    // end of the string, return 1
    return curr->isWord;
}

void freeTree(Trie* head) {
    if(head != NULL)
    {
        for(int i = 0; i < 26; i++)
        {
            if(head->characters[i] != NULL)
            {
                free(head->characters[i]);
            }
        }
        free(head);
    }
}

void printTree(Trie *subtree, char word[100], int level) {
    if(subtree->isWord == 1) {
        word[level] = '\0';
        //print words in tree
        printw("%s\t", word);
        refresh();
    }

    for(int i = 0; i < 26; i++) {
        if(subtree->characters[i] != NULL) {
            //traverse levels of trie
            word[level] = 97 + i;
            //recursively call printTree
            printTree(subtree->characters[i], word, level+1);
        }
    }


}
