#include <iostream>
#include <curses.h>
#include <string>

int main() 
{
	//inicjalizuje ekran
	//czy�ci ekran
	initscr();

	//rysuje stringa w oknie
	printw("hello world");

	//od�wie�a ekran
	refresh();

	//zwraca naci�ni�ty przycisk
	getch();


	//usuwa pami�� i zamyka ncurses
	endwin();

	return 0;
}
