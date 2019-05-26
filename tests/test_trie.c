#include "trie.h"
#include "dynstring.h"
#include "dynlinks.h"


int test_store_value() {
    int flag = 0;
    struct Node *trie = NewTrie();

    storeValue(trie, "abcd", "x");
    storeValue(trie, "abce", "y");

    struct Node *node = findKey(trie, "ab");
    if (node && node->used) {
        printf("Found ab, but it is not used\n");
        flag = 1;
    }        

    node = findKey(trie, "abcd");
    if (!node || !(node->used)) {
        printf("abcd not found or not used\n");
        flag = 1;
    } else if (node->value[0] != "x") {
        printf("key != x, = %c", node->value[0]);
        flag = 1;
    }

    node = findKey(trie, "abce");
    if (!node || !(node->used)) {
        printf("abce not found or not used\n");
        flag = 1;
    }

    deleteTrie(trie);

    return flag;
}


int test_delete_value() {
    int flag = 0;
    struct Node *trie = NewTrie();
    storeValue(trie, "a", "x");
    storeValue(trie, "ab", "x");
    storeValue(trie, "b", "x");

    deleteKey(trie, "a");
    struct Node *node = findKey(trie, "ab");
    if (!node || !(node->used)) {
        printf("ab not found\n");
        flag = 1;
    }

    node = findKey(trie, "a");
    if (node && node->used) {
        printf("Found a, but it was deleted\n");
        flag = 1;
    }

    node = findKey(trie, "b");
    if (!node || !(node->used)) {
        printf("b not found\n");
        flag = 1;
    }

    deleteTrie(trie);

    return flag;        
}


int main(int argc, char **argv) {
    if (test_store_value()){
        printf("Test Store failed\n");
        return 1;
    }

    if (test_delete_value()){
        printf("Test Delete failed\n");
        return 1;
    }

    printf("All tests passed\n");

    return 0;
}