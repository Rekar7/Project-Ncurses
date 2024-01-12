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


void spawn(METEOR meteor, AMMOPACK ammopack, MISSILE missile, SCIENCEPACK sciencepack, std::vector<METEOR>& meteors, std::vector<AMMOPACK>& ammopacks, std::vector<SCIENCEPACK>& sciencepacks)
{

	int meteorChance = rand() % 1000;
	int ammoChance = rand() % 1000;
	int scienceChance = rand() % 1000;

	if (meteorChance < 50)
	{
		meteor.spawn();
		meteors.push_back(meteor);
	}

	if (ammoChance < 20)
	{
		ammopack.spawn();
		ammopacks.push_back(ammopack);
	}

	if (scienceChance < 10)
	{
		sciencepack.spawn();
		sciencepacks.push_back(sciencepack);
	}
}

////////////////////////////////////////////////////////////////////////////////////
///////////					  UPDATE								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void update(WINDOW* win, STARSHIP& starship, METEOR& meteor, AMMOPACK& ammopack, MISSILE& missile, SCIENCEPACK& sciencepack, std::vector<METEOR>& meteors, std::vector<AMMOPACK>& ammopacks, std::vector<MISSILE>& missiles, std::vector<SCIENCEPACK>& sciencepacks, bool& gameOver, int& score)
{
	spawn(meteor, ammopack, missile, sciencepack, meteors, ammopacks, sciencepacks);

	///ddd
	starship.movement();
 	if (starship.shoot() == true)
	{
		missile.shoot(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight());
		missiles.push_back(missile);
	}

	for (int i = 0; i < ammopacks.size(); i++)
	{
		ammopacks[i].movement();
		if (starship.moreAmmo(ammopacks[i].checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight())) == true)
		{
			ammopacks.erase(ammopacks.begin() + i);
			i--;
			continue;
		}

		if (ammopacks[i].outsideMap(win) == true)
		{
			ammopacks.erase(ammopacks.begin() + i);
			i--;
			continue;
		}
	}
	
	for (int i = 0; i < sciencepacks.size(); i++)
	{
		sciencepacks[i].movement();

		if (starship.gatherScience(sciencepacks[i].checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight())) == true)
		{
			starship.scoreUpdate(1);
			
			sciencepacks.erase(sciencepacks.begin() + i);
			i--;
			continue;
		}

		if (sciencepacks[i].outsideMap(win) == true)
		{
			sciencepacks.erase(sciencepacks.begin() + i);
			i--;
			continue;
		}
	}
	
	for (int i = 0; i < missiles.size(); i++)
	{

		missiles[i].movement();

		for (int j = 0; j < meteors.size(); j++)
		{
			missiles[i].checkHitbox(meteors[j].getX(), meteors[j].getY(), meteors[j].getWidth(), meteors[j].getHeight());
		}

		if ((missiles[i].outsideMap(win) == true) && (missiles.size() > 1))
		{
			missiles.erase(missiles.begin() + i);
			i--;
			continue;
		}
	
	}

	for (int i = 0; i < meteors.size(); i++)
	{
		meteors[i].movement();

		for (int j = 0; j < missiles.size(); j++)
		{
			if (meteors[i].checkHitbox(missiles[j].getX(), missiles[j].getY(), missiles[j].getWidth(), missiles[j].getHeight()) == true)
			{
				starship.scoreUpdate(2);
				
				meteors.erase(meteors.begin() + i);
				missiles.erase(missiles.begin() + j);
				i--;
				break;
			}
		}

		
		if (meteors[i].checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight()))
		{
			gameOver = true;
		}

		if (meteors[i].outsideMap(win) == true)
		{
			meteors.erase(meteors.begin() + i);
			i--;
			continue;
		}

		if (score > 30)
		{
			starship.scoreUpdate(3);
			score = 0;
		}
			

	}

	score++;

}

////////////////////////////////////////////////////////////////////////////////////
///////////					     DRAW								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void draw(WINDOW* win, STARSHIP& starship, std::vector<METEOR>& meteors, std::vector<AMMOPACK>& ammopacks, std::vector<MISSILE>& missiles, std::vector<SCIENCEPACK>& sciencepacks, bool gameOver)
{
	box(win, 0, 0);	// robi kwadrat wok� okna

	for (int i = 0; i < meteors.size(); i++)
	{
		meteors[i].draw(win);
	}
	
	for (int i = 0; i < missiles.size(); i++)
	{
		missiles[i].draw(win);
	}

	for (int i = 0; i < ammopacks.size(); i++)
	{
		ammopacks[i].draw(win);
	}

	for (int i = 0; i < sciencepacks.size(); i++)
	{
		sciencepacks[i].draw(win);
	}
	
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
		//czy�ci ekran
	initscr();

	noecho();	//input nie pokazuje si� na ekranie

	if (!has_colors())	//has_colors() zwraca true jak terminal mo�e uzywa� kolor�w
	{
		printw("Terminal nie obs�uguje kolor�w");
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

	std::vector<METEOR> meteors;
	std::vector<AMMOPACK> ammopacks;
	std::vector<MISSILE> missiles;
	std::vector<SCIENCEPACK> sciencepacks;

	bool gameOver = false;
	int score = 0;
	////////////////////////////////////////////////////////////////////////////////////
	///////////					GAME LOOP									////////////
	////////////////////////////////////////////////////////////////////////////////////

	while (gameOver == false)
	{

		update(win, starship, meteor, ammopack, missile, sciencepack, meteors, ammopacks, missiles, sciencepacks, gameOver, score); //update stanu gry

		draw(win, starship, meteors, ammopacks, missiles, sciencepacks, gameOver);		//rysuje gre

		wrefresh(win);	//od�wie�amy okno

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




	//usuwa pami�� i zamyka ncurses
	endwin();

	return 0;
}