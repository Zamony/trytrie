import os
from cffi import FFI

ffibuilder = FFI()

header = """
struct Link {
    char token;
    struct Node *next;
};
struct Node {
    unsigned char used;
    char *value;
    int nlink;
    struct Link **links;
};
struct DynamicLinkArray {
    int len;
    int cap;
    struct Link *value;
};
struct DynamicLinkArray * NewDynamicLinkArray();
void deleteDynamicLinkArray(struct DynamicLinkArray *s);
void appendLink(struct DynamicLinkArray *s, struct Link link);
struct Link *popLink(struct DynamicLinkArray *);
struct DynamicString {
    int len;
    int cap;
    char *value;
};
struct DynamicString * NewDynamicString();
void deleteDynamicString(struct DynamicString *s);
void appendChar(struct DynamicString *s, char token);
char popChar(struct DynamicString *s);
int findLink(struct Node *node, char token);
struct Node * addLink(struct Node *node, char token);
void storeValue(struct Node *node, char *key, char *value);
struct Node * findKey(struct Node *node, char *key);
int deleteKey(struct Node *node, char *key);
struct Node * iterKeys(
    struct Node *, struct Node *, struct DynamicString *,
    struct DynamicLinkArray *, int *, int *
);
struct Node * NewTrie();
void deleteTrie(struct Node *node);
"""

ffibuilder.cdef(header)

ffibuilder.set_source(
    "_trytrie",
    header, libraries=["trie"], library_dirs=[".",]
)

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)