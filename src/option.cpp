#include "option.h"

Option::Option(int y, std::string x, std::vector<int> z, std::vector<std::string> w)
{
    // set arguments to member values
	id = y;
	name = x;

	for (int i = 0; i < z.size(); i++)
	{
		win[z[i]] = w[i];
	}
}