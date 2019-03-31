all:
	gcc -Wall -std=c11 boggle.c board.c trieStructures.c  menus.c  -o boggle -lncurses

clean:
	rm *.0 encode

