#include <iostream>
#include "ISearchable.hpp"
#include "DummySearch.hpp"

DummySearch::DummySearch()
{
	std::cout << "DummySearch()" << std::endl;
}

DummySearch::~DummySearch()
{
	std::cout << "~DummySearch()" << std::endl;
}

int DummySearch::search(std::string search_string)
{
	std::cout << "Searching for: " << search_string << std::endl;
    return 0;
}

std::string DummySearch::getResult()
{
	return std::string("results....");
}
