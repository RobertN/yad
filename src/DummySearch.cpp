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

int DummySearch::search(const int argc, const char *argv[])
{
    std::string search_string;
    if (argc == 3)
        search_string = argv[2];
    else
        return 1;

    std::cout << "Searching for: " << search_string << std::endl;
    return 0;
}

std::string DummySearch::getResult()
{
    return std::string("results....");
}
