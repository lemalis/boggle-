#ifndef trieStructures_h
#define trieStructures_h

typedef struct Trie{
    int isWord;
    struct Trie* characters[26];
} Trie;


Trie *createTrieNode();
int insert(Trie *head, char *str);
int search(Trie* head, char* str);
void freeTree(Trie* head);
void printTree(Trie *subtree, char word[100], int level);


#endif /* trieStructures_h */
