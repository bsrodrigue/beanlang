#ifndef trie_clox_h
#define trie_clox_h

#include "common.h"
#include <stdlib.h>
#include <string.h>

#define ALPHABET_MAX 26

typedef struct Node Node_t;

struct Node {
  bool isWord;
  // Why do we need pointer?
  Node_t *children[ALPHABET_MAX];
};

typedef struct Trie Trie_t;

struct Trie {
  int count;
  Node_t *root;
};

void initTrie(Trie_t *trie);
void insertTrie(Trie_t *trie, char *key);
bool searchTrie(Trie_t *trie, char *key);

#endif // !trie_clox_h
