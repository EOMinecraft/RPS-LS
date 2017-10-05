#include "game.h"

Game::Game()
{
	Option *rock = new Option(ROCK, "Rock", { SCISSORS, LIZARD }, { "Rock breaks scissors", "Rock covers lizard" });
	Option *scissors = new Option(SCISSORS, "Scissors", { PAPER, LIZARD }, { "Scissors cut paper", "Scissors decapitates lizard" });
	Option *paper = new Option(PAPER, "Paper", { ROCK, SPOCK }, { "Paper covers rock", "Paper disproves Spock" });
	Option *spock = new Option(SPOCK, "Spock", { ROCK, SCISSORS }, { "Spock vaporizes rock", "Spock crushes scissors" });
	Option *lizard = new Option(LIZARD, "Lizard", { SPOCK, PAPER }, { "Lizard poisons Spock", "Lizard eats paper" });
	Option *quit = new Option(QUIT, "Quit", { QUIT }, { "" });

	options[ROCK] = rock;
	options[SCISSORS] = scissors;
	options[PAPER] = paper;
	options[SPOCK] = spock;
	options[LIZARD] = lizard;
	options[QUIT] = quit;

	currentMenuSelection = 1;
	live = true;
	userTurn = true;
}

// check for win conditions
void Game::winCheck()
{
	// if game is a tie
	if (userChoice == computerChoice)
	{
		tieCount++;
	}

	// if computer choice is in the userChoice objects win condition
	for (auto &p : options.at(userChoice)->win)
	{
		// check first key of the win map
		if (computerChoice == p.first)
		{
			// store win message
			winMessage = p.second;
			userScore++;
		}
	}

	// loop through the computerChoice win condition map
	for (auto &p : options.at(computerChoice)->win)
	{
		// if user choice is contained as a key
		if (userChoice == p.first)
		{
			// store the value of p to winMessage
			winMessage = p.second;
			computerScore++;
		}
	}

}

// display final results
void Game::displayResults()
{
	std::cout << "\n\nUser Choice: " << options.at(userChoice)->name << std::endl;
	std::cout << "Computer Choice: " << options.at(computerChoice)->name << std::endl;
	std::cout << winMessage << std::endl;

	/*
	int results = winCheck();

	switch (results)
	{
	case WIN:
		std::cout << "You Win!" << std::endl;
		break;
	case LOSE:
		std::cout << "You Lose!" << std::endl;
		break;
	case TIE:
		std::cout << "The game was a tie" << std::endl;
		break;
	}
	*/
}

// advanced abstract menu
void Game::displayMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	// menu
	std::cout << "RPSSL\n";
	std::cout << "Please select an option: \n";
	std::cout << "------\n";

	for (auto it = options.begin(); it != options.end(); it++)
	{
		int index = std::distance(options.begin(), it) + 1;
		// highlight current selection
		if (index == currentMenuSelection)
			SetConsoleTextAttribute(hConsole, 16);
		else
			SetConsoleTextAttribute(hConsole, 7);

		// display
		std::cout << it->second->id + 1 << ". " << it->second->name << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "\n\n\n";
	std::cout << "SCORE\n";
	std::cout << "-------------\n";
	std::cout << "YOU: " << userScore << "\n";
	std::cout << "COMPUTER: " << computerScore << "\n";
	std::cout << "TIE: " << tieCount << "\n";

	if (userScore > 0 || computerScore > 0 || tieCount > 0)
		displayResults();
}

// redraw the menu
void Game::redraw()
{
	system("CLS");
	displayMenu();
}

// get a random number for computerChoice
void Game::computerTurn()
{
	computerChoice = std::rand() % (LIZARD);
	computerChoice += 1;
}

// start the game
void Game::start()
{
	// seed
	std::srand(time(NULL));

	// throw away the first random number
	std::rand();

	// display the menu
	displayMenu();

	// initialize variables to contain our console inputs
	DWORD mode;
	INPUT_RECORD event;
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hstdin, &mode);
	SetConsoleMode(hstdin, 0);

	while (live)
	{
		DWORD count;
		// wait for hstdin
		if (WaitForSingleObject(hstdin, 0) == WAIT_OBJECT_0)
		{
			// get console input
			ReadConsoleInput(hstdin, &event, 1, &count);

			if ((event.EventType == KEY_EVENT) && event.Event.KeyEvent.bKeyDown)
			{
				switch (event.Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_ESCAPE:	// escape key
					exit(0);	// terminate the program
					break;
				case VK_UP:
					if (currentMenuSelection <= ROCK)
						break;
					else
					{
						currentMenuSelection--;
						redraw();
						Sleep(20);
						break;
					}
				case VK_DOWN:
					if (currentMenuSelection >= QUIT)
						break;
					else
					{
						currentMenuSelection++;
						redraw();
						Sleep(20);
						break;
					}

				case VK_RETURN:
					computerTurn();
					//live = false;
					userChoice = currentMenuSelection;
					if (userChoice == QUIT)
					{
						live = false;
						//exit(0);
					}
					else
					{
						winCheck();
						redraw();
					}
					break;
				}
			}
		}
	}
}
