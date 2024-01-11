#include <iostream>
#include <curses.h>
#include <string>
#include <windows.h>
#include "STARSHIP.h"
#include "METEOR.h"

////////////////////////////////////////////////////////////////////////////////////
///////////					FUNCTIONS								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void update(WINDOW* win, STARSHIP& starship, METEOR& meteor, bool& gameOver)
{
	starship.movement();
	meteor.movement();
	if (meteor.checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight()))
	{
		gameOver = true;
	}
}

void draw(WINDOW* win, STARSHIP& starship, METEOR& meteor, bool gameOver)
{
	box(win, 0, 0);	// robi kwadrat wokó³ okna

	starship.draw(win);
	meteor.draw(win);

	if (gameOver == true)
	{
		mvwprintw(win, 15, 80, "KONIEC GRY!");
	}

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
		//czyœci ekran
	initscr();

	noecho();	//input nie pokazuje siê na ekranie

	if (!has_colors())	//has_colors() zwraca true jak terminal mo¿e uzywaæ kolorów
	{
		printw("Terminal nie obs³uguje kolorów");
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
	METEOR meteor;


	bool gameOver = false;
	////////////////////////////////////////////////////////////////////////////////////
	///////////					GAME LOOP									////////////
	////////////////////////////////////////////////////////////////////////////////////

	while (gameOver == false)
	{

		update(win, starship, meteor, gameOver);	//update stanu gry

		draw(win, starship, meteor, gameOver);		//rysuje gre

		wrefresh(win);	//odœwie¿amy okno

		Sleep(33);
		
		if (gameOver == false)
		{
			wclear(win);
		}
		else
		{
			Sleep(5000);
			getch();
		}

	}




	//usuwa pamiêæ i zamyka ncurses
	endwin();

	return 0;
}