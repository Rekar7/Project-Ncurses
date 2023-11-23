#include <iostream>
#include <curses.h>
#include <string>

int main() 
{
	//inicjalizuje ekran
	//czyœci ekran
	initscr();

	//rysuje stringa w oknie
	printw("hello world");

	//odœwie¿a ekran
	refresh();

	//zwraca naciœniêty przycisk
	getch();


	//usuwa pamiêæ i zamyka ncurses
	endwin();

	return 0;
}
