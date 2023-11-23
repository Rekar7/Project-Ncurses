#include <iostream>
#include <curses.h>
#include <string>

int main() 
{
	//inicjalizuje ekran
	//czyœci ekran
	initscr();

	int height=10, width=20, start_y=10, start_x=10;

	WINDOW* win=newwin(height, width, start_y, start_x);	//tworzy nowe okno // w nucruses zawsze w kordach najpierw jest
							//y, a potem x


	refresh();	//odœwie¿yæ wszystko, ¿eby ncurses wiedzia³, ¿e zrobiliœmy okono


	
	box(win, 0, 0);	// robi kwadrat wokó³ okna
	mvwprintw(win, 1, 1, "szczepan");	//rysuje w oknie
	wrefresh(win);	//odœwie¿amy okno

	getch();

	//usuwa pamiêæ i zamyka ncurses
	endwin();

	/*

	//rysuje stringa w oknie
	printw("hello world");

	//odœwie¿a ekran
	refresh();

	//przesuwa kursor do podanych kordów i na tych kordach s¹ pisane rzeczy  

	move(10, 20); // move(y, x);

	int c = getch();

	printw("%d", c); //wyœwielta zmienn¹ c

	mvprintw(40, 60, "ucin");	//robi move'a i printuje


	//zwraca naciœniêty przycisk
	getch();


	clear();	//wyczyszcza ekran

	*/


	return 0;
}
