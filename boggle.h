//  boggle.h
//  BoggleGame
//
//

#ifndef boggle_h
#define boggle_h


typedef struct GuiTile {
    char value;
    int visited;
} GuiTile;

typedef struct GameBoard {
    int size;
    int vertices;
    GuiTile ** adj;
} GameBoard;

// trie for checking user moves
typedef struct Trie{
    int isWord;
    struct Trie* characters[26];
} Trie;

GameBoard * createGameBoard( int size);
void freeGameBoard(GameBoard * board);
void unvisitGameBoard(GameBoard * board);
Trie *createTrieNode();
int insert(Trie *head, char *str);
int search(Trie* head, char* str);
void printTree(Trie *subtree, char word[100], int level);
void freeTree(Trie* head);


#endif /* boggle_h */
