#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
#include "dynlinks.h"


struct DynamicLinkArray * NewDynamicLinkArray() {
    struct DynamicLinkArray *s = malloc(sizeof(struct DynamicLinkArray));
    s->len = 0;
    s->cap = 4;
    s->value = (struct Link *) calloc(s->cap, sizeof(struct Link));
    return s;
}


void deleteDynamicLinkArray(struct DynamicLinkArray *s) {
    free(s->value);
    free(s);
}


void appendLink(struct DynamicLinkArray *s, struct Link link) {
    if (s->len + 2 < s->cap) {
        s->value[s->len] = link;
        s->len = s->len + 1;
    } else {
        s->cap = 2 * s->cap;
        s->value = realloc(s->value, sizeof(struct Link) * (s->cap));
        s->value[s->len] = link;
        s->len = s->len + 1;
    }
}


struct Link *popLink(struct DynamicLinkArray *s) {
    if (s->len < 1) {
        return NULL;
    }

    s->len = s->len - 1;
    return &(s->value[s->len]);
}

