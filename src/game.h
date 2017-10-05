#include <map>
#include <string>
#include <Windows.h>
#include <iostream>
#include <ctime>
#include "option.h"

enum RESULTS
{
	WIN = 10,
	LOSE,
	TIE
};

class Game
{
private:
	int userChoice;
	int computerChoice;
	int userScore;
	int computerScore;
	int tieCount;
	bool userTurn;
	bool live;
	int currentMenuSelection;
	std::string winMessage;
	std::map<int, Option*> options;
public:
	Game();
	void winCheck();
	void displayResults();
	void displayMenu();
	void redraw();
	void computerTurn();
	void start();
};