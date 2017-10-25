#pragma once

#include <vector>
#include <string>
#include <map>

enum MENU {
	ROCK = 1,
	PAPER,
	SCISSORS,
	SPOCK,
	LIZARD,
	QUIT
};

struct Option {
    // name of option
	std::string name;
    // int id
	int id;
    // map to store win condtions
    // int stores the id's we win against
    // string is the win message
    // ---------------------------
    // if this is a rock and we want to check against scissors
    // rock[SCISSORS] = "Rock breaks scissors" (after we pass the correct information to the constructor)
	std::map<int, std::string> win;

	// constructor
	Option(int y, std::string x, std::vector<int> z, std::vector<std::string> w);
};