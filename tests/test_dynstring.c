#include "dynstring.h"


int test_append() {
    struct DynamicString *s = NewDynamicString();
    appendChar(s, 'a');
    appendChar(s, 'b');
    appendChar(s, 'c');
    appendChar(s, 'd');

    int flag = 0;
    if (s->len != 4) {
        printf("len != 4, len = %d\n", s->len);
        flag = 1;
    }

    if (s->value[0] != 'a'){
        printf("s[0] != a\n");
        flag = 1;
    }

    if (s->value[1] != 'b'){
        printf("s[1] != b\n");
        flag = 1;
    }

    if (s->value[2] != 'c'){
        printf("s[2] != c\n");
        flag = 1;
    }

    if (s->value[3] != 'd'){
        printf("s[3] != d\n");
        flag = 1;
    }

    if (s->value[4] != '\0'){
        printf("s[4] != 0\n");
        flag = 1;
    }

    deleteDynamicString(s);

    return flag;
}


int test_pop() {
    struct DynamicString *s = NewDynamicString();
    appendChar(s, 'a');
    appendChar(s, 'b');
    appendChar(s, 'c');
    appendChar(s, 'd');

    int flag = 0;
    char ch = popChar(s);
    if (ch != 'd') {
        printf("last != d, last = %c\n", ch);
        flag = 1;
    }

    ch = popChar(s);
    if (ch != 'c') {
        printf("last != c, last = %c\n", ch);
        flag = 1;
    }

    ch = popChar(s);
    if (ch != 'b') {
        printf("last != b, last = %c\n", ch);
        flag = 1;
    }

    ch = popChar(s);
    if (ch != 'a') {
        printf("last != a, last = %c\n", ch);
        flag = 1;
    }

    ch = popChar(s);
    if (ch > -1) {
        printf("String must be empty, but got %c\n", ch);
        flag = 1;
    }

    ch = popChar(s);
    if (ch > -1) {
        printf("String must be empty, but got %c\n", ch);
        flag = 1;
    }

    deleteDynamicString(s);

    return flag;
}


int test_empty() {
    int flag = 0;
    struct DynamicString *s = NewDynamicString();
    appendChar(s, 'a');
    appendChar(s, 'b');
    
    if (s->len != 2) {
        printf("Len != 2, len = %d\n", s->len);
        flag = 1;
    }

    popChar(s);
    popChar(s);
    if (s->len != 0) {
        printf("Len != 0, len = %d\n", s->len);
        flag = 1;
    }

    popChar(s);
    if (s->len != 0) {
        printf("Len != 0, len = %d\n", s->len);
        flag = 1;
    }

    deleteDynamicString(s);

    return flag;   
}


int main() {

    if (test_append()){
        printf("Test Append failed\n");
        return 1;
    }

    if (test_pop()){
        printf("Test Pop failed\n");
        return 1;
    }

    if (test_empty()){
        printf("Test Empty failed\n");
        return 1;
    }

    printf("All tests passed\n");

    return 0;
}