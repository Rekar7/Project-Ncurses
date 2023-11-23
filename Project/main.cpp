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

	//przesuwa kursor do podanych kordów i na tych kordach s¹ pisane rzeczy  

	move(10, 20); // move(y, x);

	int c = getch();

	printw("%d", c); //wyœwielta zmienn¹ c

	//zwraca naciœniêty przycisk
	getch();


	//usuwa pamiêæ i zamyka ncurses
	endwin();

	return 0;
}
