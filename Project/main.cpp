#include <iostream>
#include <curses.h>
#include <string>

int main() 
{
	//inicjalizuje ekran
	//czyœci ekran
	initscr();
	cbreak();	//jak wciœniesz ctrl+c to program siê zamknie dzia³a defaultowo

	//raw();		//raw input jak wciœniesz ctrl+c to ctrl te¿ siê wyœwietli

	noecho();	//input nie pokazuje siê na ekranie

	int height=30, width=120, start_y=0, start_x=0;

	WINDOW* win=newwin(height, width, start_y, start_x);	//tworzy nowe okno // w nucruses zawsze w kordach najpierw jest
							//y, a potem x


	refresh();	//odœwie¿yæ wszystko, ¿eby ncurses wiedzia³, ¿e zrobiliœmy okono



	//pozwala na wiêksz¹ customizacje bordera boxa
	//wborder(win, left, right, top, bottom, corner1, corner2, corner3, corner4);


	box(win, 0, 0);	// robi kwadrat wokó³ okna
	mvwprintw(win, 1, 1, "szczepan");	//rysuje w oknie
	wrefresh(win);	//odœwie¿amy okno

	getch();

	//usuwa pamiêæ i zamyka ncurses
	endwin();kjl
		kllk
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
