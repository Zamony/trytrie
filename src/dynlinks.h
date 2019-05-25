#pragma once

#include "trie.h"


struct DynamicLinkArray {
    int len;
    int cap;
    struct Link *value;
};


struct DynamicLinkArray * NewDynamicLinkArray();
void deleteDynamicLinkArray(struct DynamicLinkArray *s);
void appendLink(struct DynamicLinkArray *s, struct Link link);
struct Link *popLink(struct DynamicLinkArray *);