#include "trie.h"
#include "dynstring.h"
#include "dynlinks.h"


int main(int argc, char **argv){
    struct Node *trie = NewTrie();
    for (int i = 1; i < argc; i++) {
        storeValue(trie, argv[i], i);
    }

    int idx = -1, state = 0;
    struct DynamicLinkArray *stack = NewDynamicLinkArray();
    struct DynamicString *s = NewDynamicString();
    struct Node *trie_it;
    trie_it = iterKeys(trie, trie, s, stack, &idx, &state);
    while (trie_it) {   
        printf("%s\n", s->value);
        trie_it = iterKeys(trie_it, trie, s, stack, &idx, &state);
    };


    deleteDynamicLinkArray(stack);
    deleteDynamicString(s);
    deleteTrie(trie);

    return 0;

}