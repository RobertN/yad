#ifndef GOOGLETRANSLATESEARCH_HPP
#define GOOGLETRANSLATESEARCH_HPP

#include "QueryBuilder.hpp"
#include "ISearchable.hpp"
#include "NetworkConnection.hpp"
#include "ResultBuilder.hpp"

class GoogleTranslateSearch: public ISearchable
{
public:
	GoogleTranslateSearch();
	~GoogleTranslateSearch();

	int search(std::string search_string);
	std::string getResult();

private:
	int makeSearchRequest(std::string search_string);
	std::string retrieveSearchResponse();

	std::string m_results;
	NetworkConnection m_connection;
	ResultBuilder m_result_builder;
};

class GoogleTranslateQueryBuilder
	: public QueryBuilder
{
private:
	virtual std::string generateHeaders();
	virtual std::string generateRequestLine();
};

#endif
