#include "trie.h"

Node_t *createNode() {
  Node_t *node = NULL;
  node = (Node_t *)malloc(sizeof(Node_t));

  node->isWord = false;

  for (int i = 0; i < ALPHABET_MAX; i++) {
    node->children[i] = NULL;
  }

  return node;
}

void initTrie(Trie_t *trie) {
  trie->count = 0;
  trie->root = createNode();
}

void insertTrie(Trie_t *trie, char *key) {
  int length = strlen(key);
  int level, index;
  Node_t *node = trie->root;

  for (level = 0; level < length; level++) {
    index = key[level] - 'a';
    if (!node->children[index]) {
      node->children[index] = createNode();
    }
    node = node->children[index];
  }

  node->isWord = true;
}

bool searchTrie(Trie_t *trie, char *key) {
  int length = strlen(key);
  int level, index;
  Node_t *node = trie->root;

  for (level = 0; level < length; level++) {
    index = key[level] - 'a';
    if (!node->children[index]) {
      return false;
    }
    node = node->children[index];
  }

  return (node != NULL && node->isWord);
}
