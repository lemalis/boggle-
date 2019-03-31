#ifndef boggle_h
#define boggle_h

GameBoard * createGameBoard( int size);
void freeGameBoard(GameBoard * board);
void unvisitGameBoard(GameBoard * board);
Trie *createTrieNode();
int insert(Trie *head, char *str);
int search(Trie* head, char* str);
void printTree(Trie *subtree, char word[100], int level);
void freeTree(Trie* head);


#endif /* boggle_h */
