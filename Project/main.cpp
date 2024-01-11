#include <iostream>
#include <curses.h>
#include <string>
#include <windows.h>
#include "STARSHIP.h"

////////////////////////////////////////////////////////////////////////////////////
///////////					FUNCTIONS								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void update(WINDOW* win, STARSHIP& starship)
{
	halfdelay(1);
	int keyPressed = wgetch(win);
	starship.movement(keyPressed);
}

void draw(WINDOW* win, STARSHIP& starship)
{
	box(win, 0, 0);	// robi kwadrat wok� okna

	starship.draw(win);

}

////////////////////////////////////////////////////////////////////////////////////
///////////					MAIN										////////////
////////////////////////////////////////////////////////////////////////////////////



int main()
{

	////////////////////////////////////////////////////////////////////////////////////
	///////////					INICJALIZACJA								////////////
	////////////////////////////////////////////////////////////////////////////////////

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

	//zwraca naci�ni�ty przycisk
	getch();

	cbreak();	//jak wci�niesz ctrl+c to program si� zamknie dzia�a defaultowo

	//raw();		//raw input jak wci�niesz ctrl+c to ctrl te� si� wy�wietli

	noecho();	//input nie pokazuje si� na ekranie

	if (!has_colors())	//has_colors() zwraca true jak terminal mo�e uzywa� kolor�w
	{
		printw("Terminal nie obs�uguje kolor�w");
		getch();
		return -1;
	}

	start_color();	//startuje kolory dla terminala


	int height = 30, width = 120, start_y = 0, start_x = 0;

	WINDOW* win = newwin(height, width, start_y, start_x);	//tworzy nowe okno // w nucruses zawsze w kordach najpierw jest
	//y, a potem x

	curs_set(0);

	keypad(win, true);

	refresh();


	STARSHIP starship;

	////////////////////////////////////////////////////////////////////////////////////
	///////////					GAME LOOP									////////////
	////////////////////////////////////////////////////////////////////////////////////

	while (1)
	{

		update(win, starship);	//update stanu gry

		draw(win, starship);		//rysuje gre

		wrefresh(win);	//od�wie�amy okno

		Sleep(33);

		wclear(win);

		clear();

	}




	//usuwa pami�� i zamyka ncurses
	endwin();

	return 0;
}