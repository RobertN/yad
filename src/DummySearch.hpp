#ifndef DUMMYSEARCH_HPP
#define DUMMYSEARCH_HPP

#include "ISearchable.hpp"

class DummySearch : public ISearchable
{
	public:
		DummySearch();
		~DummySearch();

	    int search(const int argc, const char *argv[]);
		std::string getResult();
};

#endif
