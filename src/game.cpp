#include "game.h"

Game::Game() {
	// create our options
	// use a pointer so it doesn't get deleted until we explicity delete it
    // probably doesn't need to be a pointer
	Option *rock = new Option(ROCK, "Rock", { SCISSORS, LIZARD }, { "Rock breaks scissors", "Rock crushes lizard" });
	Option *scissors = new Option(SCISSORS, "Scissors", { PAPER, LIZARD }, { "Scissors cut paper", "Scissors decapitates lizard" });
	Option *paper = new Option(PAPER, "Paper", { ROCK, SPOCK }, { "Paper covers rock", "Paper disproves Spock" });
	Option *spock = new Option(SPOCK, "Spock", { ROCK, SCISSORS }, { "Spock vaporizes rock", "Spock crushes scissors" });
	Option *lizard = new Option(LIZARD, "Lizard", { SPOCK, PAPER }, { "Lizard poisons Spock", "Lizard eats paper" });
	Option *quit = new Option(QUIT, "Quit", { QUIT }, { "" });

	// store our options in a map
	options[ROCK] = rock;
	options[SCISSORS] = scissors;
	options[PAPER] = paper;
	options[SPOCK] = spock;
	options[LIZARD] = lizard;
	options[QUIT] = quit;

	// set our defaults
	currentMenuSelection = 1;
	live = true;
	userTurn = true;
}

// check for win conditions
void Game::winCheck() {
	// if game is a tie
	if (userChoice == computerChoice) {
		tieCount++;
		winMessage = "The game was a tie";
	}

	// if computer choice is in the userChoice objects win condition
	for (auto &p : options.at(userChoice)->win) {
		// check first key of the win map
		if (computerChoice == p.first) {
			// store win message
			winMessage = p.second;
			userScore++;
		}
	}

	// loop through the computerChoice win condition map
	for (auto &p : options.at(computerChoice)->win) {
		// if user choice is contained as a key
		if (userChoice == p.first) {
			// store the value of p to winMessage
			winMessage = p.second;
			computerScore++;
		}
	}

}

// display final results
void Game::displayResults() {
	std::cout << "\n\nUser Choice: " << options.at(userChoice)->name << std::endl;
	std::cout << "Computer Choice: " << options.at(computerChoice)->name << std::endl;
	std::cout << winMessage << std::endl;
}

// display menu
void Game::displayMenu() {
	// get console output object
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// set the console color
	SetConsoleTextAttribute(hConsole, 7);

	// menu
	std::cout << "RPSSL\n";
	std::cout << "Please select an option: \n";
	std::cout << "------\n";

	// loop through our options map
	for (auto it = options.begin(); it != options.end(); it++) {
		// if the map[int] is equal to currentMenuSelection
		if (it->first == currentMenuSelection) {
			// set selected color
			SetConsoleTextAttribute(hConsole, 16);
		}
		else {
			// set default color
			SetConsoleTextAttribute(hConsole, 7);
		}
		// display info about item
		std::cout << it->second->id << ". " << it->second->name << std::endl;
	}
	// set default color
	SetConsoleTextAttribute(hConsole, 7);
	// display score
	std::cout << "\n\n\n";
	std::cout << "SCORE\n";
	std::cout << "-------------\n";
	std::cout << "YOU: " << userScore << "\n";
	std::cout << "COMPUTER: " << computerScore << "\n";
	std::cout << "TIE: " << tieCount << "\n";

	// if score is greater than zero
	if (userScore > 0 || computerScore > 0 || tieCount > 0) {
		// display results
		displayResults();
	}
}

// redraw the menu
void Game::redraw() {
	// clear screen
	system("CLS");
	// display our menu
	displayMenu();
}

// get a random number for computerChoice
void Game::computerTurn() {
	computerChoice = std::rand() % (LIZARD);
	computerChoice += 1;
}

// start the game
void Game::start() {
	// seed
    // (CLion hilights std:: and states "qualifier is redundant")
    // (Clion hilights NULL and states "(macro) NULL 0 \n Zero constant can be replaced with NULLPTR)
	std::srand(time(NULL));

	// throw away the first random number
    // (CLion hilights std:: and states "qualifier is redundant")
	std::rand();

	// display the menu
	displayMenu();

	// initialize variables to contain our console inputs
	DWORD mode;
	INPUT_RECORD event;
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hstdin, &mode);
	SetConsoleMode(hstdin, 0);

	// loop for days
	while (live) {
		DWORD count;
		// wait for input
		if (WaitForSingleObject(hstdin, 0) == WAIT_OBJECT_0) {
			// get console input
			ReadConsoleInput(hstdin, &event, 1, &count);
			// on keydown
			if ((event.EventType == KEY_EVENT) && event.Event.KeyEvent.bKeyDown) {
				switch (event.Event.KeyEvent.wVirtualKeyCode) {

				case VK_ESCAPE:	// escape key
					exit(0);	// terminate the program
				case VK_UP:	// up
				    if (currentMenuSelection <= ROCK)
				        break;
				    currentMenuSelection--;
				    redraw();
				    Sleep(20);
				    break;
				case VK_DOWN:	// down
				    if (currentMenuSelection >= QUIT)
				        break;
				    currentMenuSelection++;
				    redraw();
				    Sleep(20);
				    break;
				case 0x31:	// 1
					currentMenuSelection = 1;
					redraw();
					break;
				case 0x32:	// 2
					currentMenuSelection = 2;
					redraw();
					break;
				case 0x33:	// 3
					currentMenuSelection = 3;
					redraw();
					break;
				case 0x34:	// 4
					currentMenuSelection = 4;
					redraw();
					break;
				case 0x35:	// 5
					currentMenuSelection = 5;
					redraw();
					break;
				case 0x36:	// 6
					currentMenuSelection = 6;
					redraw();
					break;
				case VK_RETURN:		// enter
					computerTurn();
					//live = false;
					userChoice = currentMenuSelection;
					if (userChoice == QUIT) {
					    live = false;
					    //exit(0);
					}
					else {
				        winCheck();
				        redraw();
				    }
					break;
				}
			}
		}
	}
}

// deconstructor
Game::~Game() {
    // delete our stuff so memory doesn't leak
    for (int i = ROCK; i <= QUIT; i++) {
        try {
            delete options[i];
        }
        catch (int err) {
            exit(1);
        }
    }
}
