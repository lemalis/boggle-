#include "trieStructures.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <ncurses.h>



// init a new trie node
Trie *createTrieNode(){
    Trie *node = (Trie *)malloc(sizeof(Trie));
    node->isWord = 0;
    
    for (int i = 0; i < 26; i++)
        node->characters[i] = NULL;
    
    return node;
}
// add word to trie
int insert(Trie *head, char *str)
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
    if(curr->isWord == 1) {
        return 0;
    }
    // mark current node as leaf
    curr->isWord = 1;
    return 1;
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
                freeTree(head->characters[i]);
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