#include <iostream>
#include <curses.h>
#include <string>

int main() 
{
	//inicjalizuje ekran
	//czy�ci ekran
	initscr();
	cbreak();	//jak wci�niesz ctrl+c to program si� zamknie dzia�a defaultowo

	//raw();		//raw input jak wci�niesz ctrl+c to ctrl te� si� wy�wietli

	noecho();	//input nie pokazuje si� na ekranie

	int height=30, width=120, start_y=0, start_x=0;

	WINDOW* win=newwin(height, width, start_y, start_x);	//tworzy nowe okno // w nucruses zawsze w kordach najpierw jest
							//y, a potem x


	refresh();	//od�wie�y� wszystko, �eby ncurses wiedzia�, �e zrobili�my okono



	//pozwala na wi�ksz� customizacje bordera boxa
	//wborder(win, left, right, top, bottom, corner1, corner2, corner3, corner4);


	box(win, 0, 0);	// robi kwadrat wok� okna
	mvwprintw(win, 1, 1, "szczepan");	//rysuje w oknie
	wrefresh(win);	//od�wie�amy okno

	getch();

	//usuwa pami�� i zamyka ncurses
	endwin();kjl
		kllk
	/*

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

	*/


	return 0;
}
