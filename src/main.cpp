#include <iostream>
#include "NetworkConnection.hpp"
#include "TydaSearch.hpp"
#include "GoogleTranslateSearch.hpp"
#include "DummySearch.hpp"
#include "debug.hpp"
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	debug("Starting yad");

	ISearchable *searchable;
	if (argc == 2)
	{
		//TODO: should we really have dynamic allocation???
		searchable = new TydaSearch();
		searchable->search(argv[1]);
		cout << searchable->getResult() << endl;
		delete searchable;
	}
	else if (argc == 3)
	{
		if (argv[1][0] != '-')
		{
            std::cerr << "Error: Too many arguments or no flags!" << endl;
			return 1;
		}
		int i = 1;
		while (argv[1][i] != '\0')
		{
			switch(argv[1][i])
			{
				case 't':
					searchable = new TydaSearch();
					break;
				case 'g':
						 searchable = new GoogleTranslateSearch();
					   break;
				case 'd':
						 searchable = new DummySearch();
						 break;
				default:
					   std::cerr << "Error: Flag "
						   << "\"" << argv[1][i] << "\""
						   << " dose not exist!" << endl;
					   return 1;
			}
			searchable->search(argv[2]);
			cout << searchable->getResult() << endl;
			delete searchable;
			i++;
		}
		if (i == 1)
		{
			cout << "Error: No flags!" << endl;
		}
	}
	else
	{
		cout << "Usage: " << argv[0] << "-[tgd] Search_word" << endl;
		return 1;
	}

	return 0;
}
