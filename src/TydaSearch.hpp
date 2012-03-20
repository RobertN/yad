#ifndef TYDASEARCH_HPP
#define TYDASEARCH_HPP

#include "ISearchable.hpp"

class TydaSearch: public ISearchable
{
	public:
		TydaSearch();
		~TydaSearch();

		int search(std::string search_string);
		std::string getResult();
    private:
		std::string results;
};

#endif
