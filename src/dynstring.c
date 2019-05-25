#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynstring.h"


struct DynamicString * NewDynamicString() {
    struct DynamicString *s = malloc(sizeof(struct DynamicString));
    s->len = 0;
    s->cap = 4;
    s->value = (char *) calloc(s->cap, sizeof(char));
    return s;
}


void deleteDynamicString(struct DynamicString *s) {
    free(s->value);
    free(s);
}


void appendChar(struct DynamicString *s, char token) {
    if (s->len + 2 < s->cap) {
        s->value[s->len] = token;
        s->len = s->len + 1;
    } else {
        s->cap = 2 * s->cap;
        s->value = realloc(s->value, sizeof(char) * (s->cap));
        for (int i = s->len; i < s->cap; i++){
            s->value[i] = 0;
        }
        s->value[s->len] = token;
        s->len = s->len + 1;
    }
}


char popChar(struct DynamicString *s) {
    if (s->len < 1) {
        return -1;
    }

    char ch = s->value[s->len - 1];
    s->value[s->len - 1] = '\0';
    s->len = s->len - 1;
    return ch;
}
