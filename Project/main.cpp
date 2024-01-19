#include <iostream>
#include <curses.h>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <time.h> 
#include <vector>
#include <fstream>
#include "STARSHIP.h"
#include "METEOR.h"
#include "AMMOPACK.h"
#include "MISSILE.h"
#include "SCIENCEPACK.h"

////////////////////////////////////////////////////////////////////////////////////
///////////					FUNCTIONS								    ////////////
////////////////////////////////////////////////////////////////////////////////////


void save(std::fstream& file, STARSHIP starship)
{
	file.open("save.txt", std::ios::out);
	if (file.good())
	{
		file << starship.getHighScore();
		file.flush();
	}
	file.close();
}


void drawButton(WINDOW* win, int x, int y, std::string text)
{
	const char* str = text.c_str();	//zwraca wskaźnik do tablicy znaków (stringa)
	mvwprintw(win, y + 1, x, "|");
	mvwhline(win, y, x, '#', 30);
	mvwhline(win, y + 2, x, '#', 30);
	mvwprintw(win, y + 1, x + 29, "|");
	mvwprintw(win, y + 1, x + 1, "siema: %s", str);
}

void endMenu(WINDOW* win, STARSHIP& starship)
{
	std::string str[3] = { "KONIEC!","Highscore: " + std::to_string(starship.getHighScore()),"Score: " + std::to_string(starship.getScore()) };
	for (int i = 0; i < 3; i++)
	{
		wattron(win, COLOR_PAIR(1));
		drawButton(win, 50, 15 + (i * 3), str[i]);
		wattroff(win, COLOR_PAIR(1));
	}
}

void drawMenu(WINDOW* win, STARSHIP& starship, int selected)
{
	std::string str[3] = { "GRAJ","Highscore: " + std::to_string(starship.getHighScore()), "WYJDZ" };
	for (int i = 0; i < 3; i++)
	{
		if(i==selected)
			wattron(win, COLOR_PAIR(2));
		drawButton(win, 50, 15 + (i * 3), str[i]);
		if(i==selected)
			wattroff(win, COLOR_PAIR(2));
	}

}

void updateMenu(int& selected, int& timer, char& screen, bool& gameOver)
{
	

	if (timer == 0)
	{
		if (GetAsyncKeyState(0x57))
		{
			timer = 5;
			selected--;
			if (selected < 0)
			{
				selected = 2;
			}
		}
		if (GetAsyncKeyState(0x53))
		{
			timer = 5;
			selected++;
			if (selected > 2)
			{
				selected = 0;
			}
		}
	}
	else
	{
		timer--;
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (selected)
		{
		case 0:
		{
			screen='g';
			break;
		}
		case 2:
		{
			gameOver = true;
			break;
		}
		default:
			break;
		}
	}
}

void spawn(STARSHIP& starship, METEOR& meteor, AMMOPACK& ammopack, MISSILE& missile, SCIENCEPACK& sciencepack, std::vector<METEOR>& meteors, std::vector<AMMOPACK>& ammopacks, std::vector<SCIENCEPACK>& sciencepacks)
{

	int meteorChance = 20 + starship.getScore() / 25;
	int ammoChance = 20 - starship.getScore() / 35;
	int scienceChance = 5;

	if (ammoChance < 1)
	{
		ammoChance = 1;
	}

	if (rand() % 1000 < meteorChance)
	{
		meteor.spawn();
		meteors.push_back(meteor);
	}

	if (rand() % 1000 < ammoChance)
	{
		ammopack.spawn();
		ammopacks.push_back(ammopack);
	}

	if (rand() % 1000 < scienceChance)
	{
		sciencepack.spawn();
		sciencepacks.push_back(sciencepack);
	}
}

////////////////////////////////////////////////////////////////////////////////////
///////////					  UPDATE								    ////////////
////////////////////////////////////////////////////////////////////////////////////

void update(WINDOW* win, STARSHIP& starship, METEOR& meteor, AMMOPACK& ammopack, MISSILE& missile, SCIENCEPACK& sciencepack, std::vector<METEOR>& meteors, std::vector<AMMOPACK>& ammopacks, std::vector<MISSILE>& missiles, std::vector<SCIENCEPACK>& sciencepacks, bool& gameOver, int& score, char& screen)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		screen = 'm';
	}

	spawn(starship, meteor, ammopack, missile, sciencepack, meteors, ammopacks, sciencepacks);

	//starship
	starship.movement();
	if (starship.shoot() == true)
	{
		missile.shoot(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight());
		missiles.push_back(missile);
	}

	//ammopacks
	for (int i = 0; i < ammopacks.size(); i++)
	{
		ammopacks[i].movement();
		if (starship.moreAmmo(ammopacks[i].checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight())) == true)
		{
			ammopacks.erase(ammopacks.begin() + i);
			continue;
		}

		if (ammopacks[i].outsideMap() == true)
		{
			ammopacks.erase(ammopacks.begin() + i);
			continue;
		}
	}

	//sciencepacks
	for (int i = 0; i < sciencepacks.size(); i++)
	{
		sciencepacks[i].movement();

		if (starship.gatherScience(sciencepacks[i].checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight())) == true)
		{
			starship.scoreUpdate(1);

			sciencepacks.erase(sciencepacks.begin() + i);
			//i--;
			continue;
		}

		if (sciencepacks[i].outsideMap() == true)
		{
			sciencepacks.erase(sciencepacks.begin() + i);
			//i--;
			continue;
		}
	}

	//missiles
	for (int i = 0; i < missiles.size(); i++)
	{

		missiles[i].movement();

		for (int j = 0; j < meteors.size(); j++)
		{
			missiles[i].checkHitbox(meteors[j].getX(), meteors[j].getY(), meteors[j].getWidth(), meteors[j].getHeight());
		}

		if ((missiles[i].outsideMap() == true) && (missiles.size() > 1))
		{
			missiles.erase(missiles.begin() + i);
			i--;
			continue;
		}

	}
	
	//meteors
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
				break;
			}
		}


		if (meteors[i].checkHitbox(starship.getX(), starship.getY(), starship.getWidth(), starship.getHeight()))
		{
			gameOver = true;
		}

		if (meteors[i].outsideMap() == true)
		{
			meteors.erase(meteors.begin() + i);
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
	box(win, 0, 0);	// robi kwadrat wokó³ okna

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

	std::fstream file;

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
	char screen = 'm'; // m - menu, g - gra
	int selectedButton = 0;
	int timer = 0;

	int a = 0;
	//wczytywanie
	file.open("save.txt", std::ios::in);
	if (file.good() == true)
	{
		file >> a;
	}
	starship.setHighScore(a);

	file.close();

	////////////////////////////////////////////////////////////////////////////////////
	///////////					GAME LOOP									////////////
	////////////////////////////////////////////////////////////////////////////////////

	while (gameOver == false)
	{
		
		switch (screen)
		{
		case 'm':
		{
			updateMenu(selectedButton, timer, screen, gameOver);
			drawMenu(win, starship, selectedButton);
			break;
		}
		case 'g':
		{
			update(win, starship, meteor, ammopack, missile, sciencepack, meteors, ammopacks, missiles, sciencepacks, gameOver, score, screen); //update stanu gry

			draw(win, starship, meteors, ammopacks, missiles, sciencepacks, gameOver);		//rysuje gre
			break;
		}
		default:
			break;
		}
		

		wrefresh(win);	//odświeżamy okno

		Sleep(33);	//ok. 30FPS


		if (gameOver == false)
		{
			wclear(win);
		}
		else
		{
			save(file, starship);
			wclear(win);
			endMenu(win, starship);
			wrefresh(win);
			Sleep(5000);
			system("pause");
		}

	}

	//usuwa pamiêæ i zamyka ncurses
	endwin();

	return 0;
}