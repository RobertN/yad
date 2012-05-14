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
		std::string query("GET /search?form=1&w=");
        query += search_string;
        query += "&w_lang=&x=0&y=0 HTTP/1.1\r\n";
		query += "Host: tyda.se\r\n";
		query += "\r\n";
		m_connection.send(query);
	}
    else //TODO what happens here? Should we do somthing more? free somthing?
        return EXIT_FAILURE;

    // Load HTML file 
    // TODO: maybe we should use some more fancy lib for this...i
    std::string txt("");
    int i=0;//TODO REMOVE THIS VARIABLE
    while(i < 30)
    {
        i++;
        std::string buf = m_connection.recv(1024);
        if (buf.length() == 0)
            break;

        txt += buf;
    }
    //std::cout << txt;
	/*
	//TODO: should this be in getResult() ?
	//<a id="tyda_transR7" href="/search/hey">hey</a>
	//const boost::regex exp("<a id=\"(tyda_transR[^\"]*)\" href=\"[^\"]*\">([^<]*)");

	//<a href="/search/goddag">goddag</a>
	//const boost::regex exp("<a href=\"\\/(search)\\/[^\"]*\">([^<]*)");
	// Find synonyms and translations
    */
	const boost::regex exp("<a (id=\"tyda_transR|href=\"\\/search\\/)[^\"]*\"[^>]*>([^<]*)<");

	int const subs[] = {1, 2};
	boost::sregex_token_iterator itr(txt.begin(), txt.end(), exp, subs);
	boost::sregex_token_iterator end;

	for (;itr != end; ++itr)
    {
        //std::string tmp(itr->first, itr->second);
        //std::cout << " [ " << tmp << " ]" << std::endl;
        //std::cout << " [ " << *itr  << " ] "  << std::endl;

        //TODO: Save results in a nicer format in the result string.
        if (*itr == "href=\"/search/")
            results += std::string("Synonym:     ");
        else if (*itr == "id=\"tyda_transR")
            results += std::string("Translation: ");
        else
            results += *itr + std::string("\n");
	}

    return EXIT_SUCCESS;
}

std::string TydaSearch::getResult()
{
	return results;
}
