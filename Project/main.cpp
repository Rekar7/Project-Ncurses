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

	//przesuwa kursor do podanych kord�w i na tych kordach s� pisane rzeczy  

	move(10, 20); // move(y, x);

	int c = getch();

	printw("%d", c); //wy�wielta zmienn� c

	mvprintw(40, 60, "ucin");	//robi move'a i printuje


	//zwraca naci�ni�ty przycisk
	getch();


	clear();	//wyczyszcza ekran

	//usuwa pami�� i zamyka ncurses
	endwin();

	return 0;
}
