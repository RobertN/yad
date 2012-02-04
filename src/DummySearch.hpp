#ifndef DUMMYSEARCH_HPP
#define DUMMYSEARCH_HPP

#include "ISearchable.hpp"

class DummySearch : public ISearchable
{
	public:
		DummySearch();
		~DummySearch();

		int search(std::string search_string);
		std::string getResult();
};

#endif
