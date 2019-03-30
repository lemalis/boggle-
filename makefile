all:
	gcc -Wall -std=c11 -lncurses boggle1.c boggleDataStructures.c menus.c  -o boggle

clean:
	rm *.0 encode

