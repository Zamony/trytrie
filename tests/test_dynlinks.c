#include "trie.h"
#include "dynlinks.h"


int test_append() {
    struct DynamicLinkArray *s = NewDynamicLinkArray();
    struct Link link1 = {.token='a', .next=NULL};
    struct Link link2 = {.token='b', .next=NULL};
    appendLink(s, link1);
    appendLink(s, link2);

    int flag = 0;
    if (s->len != 2) {
        printf("len != 2, len = %d\n", s->len);
        flag = 1;
    }

    if (s->value[0].token != 'a'){
        printf("s[0] token != a, = %c\n", s->value[0].token);
        flag = 1;
    }

    if (s->value[1].token != 'b'){
        printf("s[0] token != b, = %c\n", s->value[1].token);
        flag = 1;
    }

    deleteDynamicLinkArray(s);

    return flag;
}


int test_pop() {
    struct DynamicLinkArray *s = NewDynamicLinkArray();
    struct Link link1 = {.token='a', .next=NULL};
    struct Link link2 = {.token='b', .next=NULL};
    appendLink(s, link1);
    appendLink(s, link2);

    int flag = 0;
    struct Link *link = popLink(s);
    if (link->token != 'b') {
        printf("pop != b, = %c \n", link->token);
        flag = 1;
    }

    link = popLink(s);
    if (link->token != 'a') {
        printf("pop != a, = %c \n", link->token);
        flag = 1;
    }

    if (s->len != 0) {
        printf("len != 0\n");
        flag = 1;
    }

    deleteDynamicLinkArray(s);

    return flag;
}


int test_empty() {
    struct DynamicLinkArray *s = NewDynamicLinkArray();
    struct Link link1 = {.token='a', .next=NULL};
    appendLink(s, link1);
    popLink(s);

    int flag = 0;
    if (s->len != 0){
        printf("len != 0\n");
        flag = 1;
    }

    struct Link *link = popLink(s);
    if (link) {
        printf("ptr != null\n");
        flag = 1;
    }

    if (s->len != 0) {
        printf("len != 0\n");
        flag = 1;        
    }

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