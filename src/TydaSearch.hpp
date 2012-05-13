#ifndef TYDASEARCH_HPP
#define TYDASEARCH_HPP

#include "ISearchable.hpp"
#include "NetworkConnection.hpp"

class TydaSearch: public ISearchable
{
	public:
		TydaSearch();
		~TydaSearch();

		int search(std::string search_string);
		std::string getResult();
    private:
		std::string results;
		NetworkConnection m_connection;
};

#endif
