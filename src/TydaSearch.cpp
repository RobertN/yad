#include <iostream>
#include "boost/regex.hpp"
#include "ISearchable.hpp"
#include "TydaSearch.hpp"

#include "NetworkConnection.hpp"

TydaSearch::TydaSearch()
{
	std::cout << "TydaSearch()" << std::endl;
}

TydaSearch::~TydaSearch()
{
	std::cout << "~TydaSearch()" << std::endl;
}

int TydaSearch::search(std::string search_string)
{
	std::cout << "Searching for: " << search_string << std::endl;

	if (m_connection.establish("tyda.se", 80))
	{
		std::string query = "GET /search?form=1&w=hej&w_lang=&x=0&y=0 HTTP/1.1\r\n";
		query += "Host: tyda.se\r\n";
		query += "\r\n";
		m_connection.send(query);
	}

	/*
	   std::string txt = connection.recv(100);

	   std::cout << txt;
	//TODO: should this be in getResult() ?
	//<a id="tyda_transR7" href="/search/hey">hey</a>
	//const boost::regex exp("<a id=\"(tyda_transR[^\"]*)\" href=\"[^\"]*\">([^<]*)");

	//<a href="/search/goddag">goddag</a>
	//const boost::regex exp("<a href=\"\\/(search)\\/[^\"]*\">([^<]*)");

	// Find synonyms and translations
	const boost::regex exp("<a (id=\"tyda_transR|href=\"\\/search\\/)[^\"]*\"[^>]*>([^<]*)<");

	int const subs[] = {1, 2};
	boost::sregex_token_iterator itr(txt.begin(), txt.end(), exp, subs);
	boost::sregex_token_iterator end;

	for (;itr != end; ++itr){
	//std::string tmp(itr->first, itr->second);
	//std::cout << " [ " << tmp << " ]" << std::endl;
	std::cout << " [ " << *itr  << " ] "  << std::endl;
	//TODO: Save results in a nicer format in the result string.
	results += std::string("[") + *itr + std::string("]");

	}
	 */

    return 0;
}

std::string TydaSearch::getResult()
{
	std::string response = connection.recv(100);
	return response;
}
