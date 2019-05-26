CC=gcc
CFLAGS=-std=c11 -Wall
pythoncmd=pipenv run python

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
	$(pythoncmd) tests/test_iterkeys.py
	./bin/dynstringtest
	./bin/dynlinkstest

trieso:
	$(CC) -c -Wall -Werror -fpic src/dynstring.c src/dynlinks.c src/trie.c
	$(CC) -shared -o trytrie/libtrie.so dynstring.o dynlinks.o trie.o


.ONESHELL:
cffi: trieso
	cd trytrie && $(pythoncmd) build_trie.py

wheel: cffi
	cp trytrie/*.so trytrie/*.o trytrie/*.c .
	$(pythoncmd) setup.py sdist bdist_wheel

wheel_upload: wheel
	$(pythoncmd) setup.py sdist upload

clean:
	rm -f *.so
	rm -f *.c
	rm -f *.o
	rm -rf bin
	rm -rf build
	rm -rf dist
	rm -f trytrie/*.so
	rm -f trytrie/*.c
	rm -f trytrie/*.o
	rm -rf trytrie.egg-info
