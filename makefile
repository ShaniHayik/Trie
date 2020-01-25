all: frequency

frequency: Trie.o
	gcc -Wall -g Trie.c -o frequency

Trie.o: Trie.c
	gcc -Wall -g -c Trie.c -o Trie.o

.PHONY: clean all

clean:
	rm -f *.o frequency

