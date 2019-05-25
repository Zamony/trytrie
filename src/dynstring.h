#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct DynamicString {
    int len;
    int cap;
    char *value;
};

struct DynamicString * NewDynamicString();
void deleteDynamicString(struct DynamicString *s);
void appendChar(struct DynamicString *s, char token);
char popChar(struct DynamicString *s);
