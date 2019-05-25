#pragma once

#include "dynstring.h"
#include "dynlinks.h"


struct Link {
    char token;
    struct Node *next;
};


struct Node {
    unsigned char used;
    int value;
    int nlink;
    struct Link **links;
};


int findLink(struct Node *node, char token);
struct Node * addLink(struct Node *node, char token);
void storeValue(struct Node *node, char *key, int value);
struct Node * findKey(struct Node *node, char *key);
int deleteKey(struct Node *node, char *key);
struct Node * iterKeys(
    struct Node *, struct Node *, struct DynamicString *,
    struct DynamicLinkArray *, int *, int *
);
struct Node * NewTrie();
void deleteTrie(struct Node *node);
