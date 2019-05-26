import json
from _trytrie import lib, ffi


class Trie:

    def __init__(self, encoder=None, decoder=None):
        self.trie = ffi.gc(lib.NewTrie(), lib.deleteTrie)
        if encoder:
            self.encoder = encoder
        else:
            self.encoder = json.dumps
        if decoder:
            self.decoder = decoder
        else:
            self.decoder = json.loads

    def get(self, key, value=None):
        node = lib.findKey(self.trie, key.encode("utf-8"))
        if node == ffi.NULL or node.used != 1:
            return value
        
        found_val = ffi.string(node.value).decode("utf-8")
        return self.decoder(found_val)

    def __setitem__(self, key, value):
        v = self.encoder(value).encode("utf-8")
        lib.storeValue(
            self.trie,
            key.encode("utf-8"),
            ffi.new("char []", v)
        )

    def __getitem__(self, key):
        node = lib.findKey(self.trie, key.encode("utf-8"))
        if node == ffi.NULL or node.used != 1:
            raise KeyError
        
        found_val = ffi.string(node.value).decode("utf-8")
        return self.decoder(found_val)        

    def __delitem__(self, key):
        lib.deleteKey(self.trie, key.encode("utf-8"))

    def __iter__(self):
        idx = ffi.new("int *")
        state = ffi.new("int *")
        idx[0] = -1
        state[0] = 0

        stack = ffi.gc(lib.NewDynamicLinkArray(), lib.deleteDynamicLinkArray)
        s = ffi.gc(lib.NewDynamicString(), lib.deleteDynamicString)
        trie_it = lib.iterKeys(self.trie, self.trie, s, stack, idx, state)
        while trie_it != ffi.NULL:
            key = ffi.string(s.value).decode("utf-8")
            yield key
            trie_it = lib.iterKeys(trie_it, self.trie, s, stack, idx, state)

    def items(self):
        idx = ffi.new("int *")
        state = ffi.new("int *")
        idx[0] = -1
        state[0] = 0

        stack = ffi.gc(lib.NewDynamicLinkArray(), lib.deleteDynamicLinkArray)
        s = ffi.gc(lib.NewDynamicString(), lib.deleteDynamicString)
        trie_it = lib.iterKeys(self.trie, self.trie, s, stack, idx, state)
        while trie_it != ffi.NULL:
            key = ffi.string(s.value).decode("utf-8")
            val = ffi.string(trie_it.value).decode("utf-8")
            yield key, self.decoder(val)
            trie_it = lib.iterKeys(trie_it, self.trie, s, stack, idx, state)

    def values(self):
        idx = ffi.new("int *")
        state = ffi.new("int *")
        idx[0] = -1
        state[0] = 0

        stack = ffi.gc(lib.NewDynamicLinkArray(), lib.deleteDynamicLinkArray)
        s = ffi.gc(lib.NewDynamicString(), lib.deleteDynamicString)
        trie_it = lib.iterKeys(self.trie, self.trie, s, stack, idx, state)
        while trie_it != ffi.NULL:
            val = ffi.string(trie_it.value).decode("utf-8")
            yield self.decoder(val)
            trie_it = lib.iterKeys(trie_it, self.trie, s, stack, idx, state)
    