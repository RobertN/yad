#include <iostream>
#include "boost/regex.hpp"
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
    
    networkconnection connection();
    connection.establish("tyda.se");
    connection.send( createHTTPMessage(search_string) );
    

    std::string txt = connection.receive();
    
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

    }

    return 0;


}

std::string DummySearch::getResult()
{
	return std::string("results....");
}
