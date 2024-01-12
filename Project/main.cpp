#include <iostream>
#include <curses.h>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <time.h> 
#include <vector>
#include "STARSHIP.h"
#include "METEOR.h"
#include "AMMOPACK.h"
#include "MISSILE.h"
#include "SCIENCEPACK.h"

////////////////////////////////////////////////////////////////////////////////////
///////////					FUNCTIONS								    ////////////
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
///////////					  UPDATE								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void update(WINDOW* win, STARSHIP& starship, METEOR& meteor, AMMOPACK& ammopack, MISSILE& missile, SCIENCEPACK& sciencepack, bool& gameOver)
{
	starship.movement();
	if (starship.shoot() == true)
	{
		missile.shoot(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight());
	}
	meteor.movement();
	ammopack.movement();
	sciencepack.movement();
	missile.movement();
	if (meteor.checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight()))
	{
		gameOver = true;
	}

	starship.moreAmmo(ammopack.checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight()));
	starship.gatherScience(sciencepack.checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight()));

	
	missile.checkHitbox(meteor.getX(),meteor.getY(),meteor.getWidth(),meteor.getHeight());

	
}

////////////////////////////////////////////////////////////////////////////////////
///////////					     DRAW								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void draw(WINDOW* win, STARSHIP& starship, METEOR& meteor, AMMOPACK& ammopack, MISSILE& missile, SCIENCEPACK& sciencepack, bool gameOver)
{
	box(win, 0, 0);	// robi kwadrat wokó³ okna

	
	meteor.draw(win);
	missile.draw(win);
	ammopack.draw(win);
	sciencepack.draw(win);

	starship.draw(win);


	starship.drawHUD(win);

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

	srand(time(NULL));

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


	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);


	int height = 30, width = 120, start_y = 0, start_x = 0;

	WINDOW* win = newwin(height, width, start_y, start_x);	//tworzy nowe okno // w nucruses zawsze w kordach najpierw jest
	//y, a potem x

	curs_set(0);

	keypad(win, true);

	refresh();


	STARSHIP starship;
	METEOR meteor;
	AMMOPACK ammopack;
	MISSILE missile;
	SCIENCEPACK sciencepack;

	bool gameOver = false;
	////////////////////////////////////////////////////////////////////////////////////
	///////////					GAME LOOP									////////////
	////////////////////////////////////////////////////////////////////////////////////

	while (gameOver == false)
	{

		update(win, starship, meteor, ammopack, missile, sciencepack, gameOver);	//update stanu gry

		draw(win, starship, meteor, ammopack, missile, sciencepack, gameOver);		//rysuje gre

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