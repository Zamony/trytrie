CC=gcc
CFLAGS=-std=c11 -Wall

mkbin:
	mkdir -p bin

itertrie: dynlinks.o dynstring.o trie.o test_iterkeys.o
	$(CC) $(CFLAGS) test_iterkeys.o dynlinks.o dynstring.o trie.o -o bin/itertrie

dynstringtest: dynstring.o test_dynstring.o
	$(CC) $(CFLAGS) dynstring.o test_dynstring.o -o bin/dynstringtest

dynlinkstest: dynlinks.o test_dynlinks.o
	$(CC) $(CFLAGS) dynlinks.o test_dynlinks.o -o bin/dynlinkstest

test_iterkeys.o:
	$(CC) $(CFLAGS) -c -Isrc tests/test_iterkeys.c

test_dynstring.o:
	$(CC) $(CFLAGS) -c -Isrc tests/test_dynstring.c

test_dynlinks.o:
	$(CC) $(CFLAGS) -c -Isrc tests/test_dynlinks.c

dynlinks.o:
	$(CC) $(CFLAGS) -c src/dynlinks.c

dynstring.o:
	$(CC) $(CFLAGS) -c src/dynstring.c

trie.o:
	$(CC) $(CFLAGS) -c src/trie.c

tests: mkbin itertrie dynstringtest dynlinkstest
	python3 tests/test_iterkeys.py
	./bin/dynstringtest
	./bin/dynlinkstest

clean:
	rm -rf *.o
	rm -rf ./bin/*
