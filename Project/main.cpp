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


	

	if (!has_colors())	//has_colors() zwraca true jak terminal mo�e uzywa� kolor�w
	{
		printw("Terminal nie obs�uguje kolor�w");
		getch();
		return -1;
	}
	/*
	* Wszystkie kolory w terminalu
	* 
	COLOR_BLACK
	COLOR_RED
	COLOR_GREEN
	COLOR_YELLOW
	COLOR_BLUE
	COLOR_MAGENTA
	COLOR_CYAN
	COLOR_WHITE
	*/
	start_color();	//startuje kolory dla terminala

	//can_change_color();	//zwraca true jak mo�na zmienia� kolory w terminalu

	init_pair(1, COLOR_CYAN, COLOR_WHITE);	//najpierw znaki potem t�o znaku

	//init_color(COLOR_CYAN, 0 - 999, 0 - 999, 0 - 999);	// zmienia kolor COLOR_CYAN na podan� warto�� RGB

	init_color(COLOR_CYAN, 999, 0, 0);

	attron(COLOR_PAIR(1));	//stosuje nasze kolory jako atrybut

	//A_REVERSE zamienia kolor t�a znaku z kolorem znaku
	//A_STANDOUT zakre�la tekst jakby markerem
	//A_BLINK jeszcze inne t�o tekstu
	//A_DIM nwm co robi
	//A_BOLD nwm co robi chyba powinnien pisa� w pogrubiony tekst
	//A_PROTECT nwm co robi
	//A_INVIS ma niby robi� niewidzialny tekst
	//A_ALTCHARSET pisze chi�skie znaczki
	//A_CHARTEXT nwm co robi zgaduje, �e nic po u�ywa zwyk�ego  chara

	attron(A_CHARTEXT);	//atrybut w��cz
	box(win, 0, 0);	// robi kwadrat wok� okna
	printw("szczepan");	
	//mvwprintw(win, 1, 1, "szczepan");	//rysuje w oknie
	attroff(COLOR_PAIR(1));	//wy��cza atrybut podany w argumencie

	wrefresh(win);	//od�wie�amy okno
	getch();

	//usuwa pami�� i zamyka ncurses
	endwin();

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
