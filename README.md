# trytrie
Fast and memory efficient Trie for Python

# Usage
```
from trytrie import Trie

trie = Trie()
trie["hello"] = "world"
trie["helly"] = "friend"

print(trie["hello"]) # world

for k in trie:
    print(k) # prints hello, helly

del trie["helly"]

print(trie.get("helly", "nothing")) # nothing

```

# Installation
Python 3+ only

``
pip install trytrie
``
