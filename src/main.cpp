#include <iostream>
#include "NetworkConnection.hpp"
#include "TydaSearch.hpp"
#include "GoogleTranslateSearch.hpp"
#include "DummySearch.hpp"
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{

	ISearchable *searchable;

	// TODO: Check what site we should search from
	if (argc == 2)
	{
		//TODO Standard search
		//TODO: should we really have dynamic allocation???
		searchable = new TydaSearch();
		searchable->search(argv[1]);
		cout << searchable->getResult() << endl;
		delete searchable;
	}
	else if (argc == 3)
	{
		//TODO Check flags for search options
		if (argv[1][0] != '-')
		{
			//TODO error message
			cout << "Error: Too many arguments or no flags!" << endl;
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
					   std::cout << "Error: Flag "
						   << "\"" << argv[1][i] << "\""
						   << " dose not exist!" << std::endl;
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
		std::cout << "Usage: " << argv[0] << "-[tgd] Search_word" << std::endl;
		return 1;
	}

	return 0;
}
