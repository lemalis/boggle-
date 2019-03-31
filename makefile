all:
	gcc -Wall -std=c11 boggle1.c board.c trieStructures.c  menus.c  -o boggle -lncurses

clean:
	rm *.0 encode

