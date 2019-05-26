#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
#include "dynstring.h"
#include "dynlinks.h"


int findLink(struct Node *node, char token) {
    int found = 0;
    int idx;
    for (idx = 0; idx < node->nlink; idx++){
        if (node->links[idx]->token == token){
            found = 1;
            break;
        }
    }

    if (!found) {
        return -1;
    } 

    return idx;
}


struct Node * addLink(struct Node *node, char token) {
    int idx = findLink(node, token);

    if (idx < 0) {
        if (node->nlink > 0) {
            idx = node->nlink;
            node->nlink = node->nlink + 1;
            node->links = (struct Link **) realloc(
                node->links, sizeof(struct Link *) * node->nlink
            );
        } else {
            idx = 0;
            node->nlink = 1;
            node->links = (struct Link **) malloc(sizeof(struct Link *));
        }

        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
        new_node->used = 0;
        new_node->value = NULL;
        new_node->nlink = 0;
        new_node->links = NULL;

        struct Link *new_link = (struct Link *) malloc(sizeof(struct Link));
        new_link->token = token;
        new_link->next = new_node;

        node->links[idx] = new_link;

        return new_node;
    }

    return node->links[idx]->next;
}


void storeValue(struct Node *node, char *key, char *value) {
    int n = strlen(key);
    struct Node *next_node = node;
    for (int i = 0; i < n; i++) {
        next_node = addLink(next_node, key[i]);
    }

    next_node->used = 1;
    next_node->value = value;
}


struct Node * findKey(struct Node *node, char *key) {
    int n = strlen(key);
    struct Node *next_node = node;
    for (int i = 0; i < n; i++) {
        int idx = findLink(next_node, key[i]);
        
        if (idx < 0) {
            return NULL;
        }

        next_node = next_node->links[idx]->next;
    }

    return next_node;
}


int deleteKey(struct Node *node, char *key) {
    struct Node *needle = findKey(node, key);
    if (!needle) {
        return 0;
    }

    needle->used = 0;
    return 1;
}


struct Node * iterKeys(
    struct Node *node, struct Node *trie, struct DynamicString *s,
    struct DynamicLinkArray *stack, int *idx, int *nretry
) {
    while (1) {
        if (*idx < s->len - 1) {
            char next_token = s->value[*idx + 1];
            int i = 0;
            for (i = 0; i < node->nlink; i++) {
                if (node->links[i]->token == next_token) {
                    break;
                }
            }

            i = i + 1;
            if (i == node->nlink) {
                *idx = *idx - 1;
                if (*idx == -1 && *nretry < trie->nlink) {
                    *nretry = *nretry + 1;
                    node = trie;
                    continue;
                } else if (*idx < 0) {
                    return NULL;
                }

                node = (stack->value[*idx]).next;
            } else {
                int d = s->len - *idx - 1;
                for (int k = 0; k < d; k++){
                    popChar(s);
                    popLink(stack);
                }

                appendChar(s, node->links[i]->token);
                appendLink(stack, *(node->links[i]));
                *idx = *idx + 1;
                node = (stack->value[*idx]).next;
                if (node->used) {
                    return node;
                }
            }
        } else if (node->nlink > 0) {
            appendChar(s, node->links[0]->token);
            appendLink(stack, *(node->links[0]));
            *idx = *idx + 1;
            node = (stack->value[*idx]).next;
            if (node->used) {
                return node;
            }
        } else {
            *idx = *idx - 1;

            if (*idx == -1 && *nretry < trie->nlink) {
                *nretry = *nretry + 1;
                node = trie;
                continue;
            } else if (*idx < 0) {
                return NULL;
            }
            node = (stack->value[*idx]).next;
        }

    }
}


struct Node * NewTrie() {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->used = 0;
    node->value = NULL;
    node->nlink = 0;
    node->links = NULL;

    return node;
}


void deleteTrie(struct Node *node) {
    for (int i = 0; i < node->nlink; i++) {
        struct Link *link = node->links[i];
        deleteTrie(link->next);
        free(link);
    }

    free(node->links);
    free(node);
}
