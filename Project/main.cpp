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


	

	if (!has_colors())	//has_colors() zwraca true jak terminal mo¿e uzywaæ kolorów
	{
		printw("Terminal nie obs³uguje kolorów");
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

	//can_change_color();	//zwraca true jak mo¿na zmieniaæ kolory w terminalu

	init_pair(1, COLOR_CYAN, COLOR_WHITE);	//najpierw znaki potem t³o znaku

	//init_color(COLOR_CYAN, 0 - 999, 0 - 999, 0 - 999);	// zmienia kolor COLOR_CYAN na podan¹ wartoœæ RGB

	init_color(COLOR_CYAN, 999, 0, 0);

	attron(COLOR_PAIR(1));	//stosuje nasze kolory jako atrybut

	//A_REVERSE zamienia kolor t³a znaku z kolorem znaku
	//A_STANDOUT zakreœla tekst jakby markerem
	//A_BLINK jeszcze inne t³o tekstu
	//A_DIM nwm co robi
	//A_BOLD nwm co robi chyba powinnien pisaæ w pogrubiony tekst
	//A_PROTECT nwm co robi
	//A_INVIS ma niby robiæ niewidzialny tekst
	//A_ALTCHARSET pisze chiñskie znaczki
	//A_CHARTEXT nwm co robi zgaduje, ¿e nic po u¿ywa zwyk³ego  chara

	attron(A_CHARTEXT);	//atrybut w³¹cz
	box(win, 0, 0);	// robi kwadrat wokó³ okna
	printw("szczepan");	
	//mvwprintw(win, 1, 1, "szczepan");	//rysuje w oknie
	attroff(COLOR_PAIR(1));	//wy³¹cza atrybut podany w argumencie

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
