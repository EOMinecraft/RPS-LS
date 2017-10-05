#include <vector>
#include <string>
#include <map>

enum MENU
{
	ROCK = 1,
	PAPER,
	SCISSORS,
	SPOCK,
	LIZARD,
	QUIT
};

struct Option
{
public:
	std::string name;
	int id;
	std::map<int, std::string> win;

	// constructor
	Option(int y, std::string x, std::vector<int> z, std::vector<std::string> w);
};