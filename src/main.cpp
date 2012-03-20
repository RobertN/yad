#include <iostream>
#include "NetworkConnection.hpp"
#include "TydaSearch.hpp"

int main(int argc, char *argv[])
{
	std::cout << "yad" << std::endl;

	ISearchable *searchable;

	// TODO: Check what site we should search from

	searchable = new TydaSearch();
	searchable->search(argv[1]);

	std::cout << searchable->getResult() << std::endl;

	delete searchable;
}
