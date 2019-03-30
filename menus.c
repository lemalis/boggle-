#include "menus.h"
#include <curses.h>
#include <ncurses.h>

int mainMenu() {
	int menuOption;
	clear();
	printw("Welcome to Boggle!\n");
	printw("Would you like to:\n");
	printw("\tStart a new game (1)\n");
	printw("\tExit Boggle (2)\n");
	printw("Enter the your option here: ");
	refresh();
	if(scanw("%d", &menuOption)) {
		if(menuOption == 1 || menuOption == 2) {
			return menuOption;
		}
		else {
			printw("\nInvalid, please enter 1 or 2.\n");
			printw("Press any key to continue.");
			getch();
			return 0 + mainMenu();
		}
	}
	else {
		printw("\nInvalid, please enter 1 or 2.\n");
		printw("Press any key to continue.");
		getch();
		return 0 + mainMenu();
	}
}

int endMenu() {
	int menuOption;
	clear();
	printw("Thank you for playing Boggle!\n");
	printw("Would you like to:\n");
	printw("\tPlay again (1)\n");
	printw("\tReturn to the main menu (2)\n");
	printw("\tExit the game (3)\n");
	printw("Enter you option here: ");
	refresh();
	if(scanw("%d", &menuOption)) {
		if(menuOption == 1 || menuOption == 2 || menuOption == 3) {
			return menuOption;
		}
		else {
			printw("\nInvalid, please enter 1, 2, or 3.\n");
			printw("Press any key to continue.");
			getch();
			return 0 + endMenu();
		}
	}
	else {
		printw("\nInvalid, please enter 1, 2, or 3.\n");
		printw("Press any key to continue.");
		getch();
		return 0 + endMenu();
	}
}