#include <iostream>
#include <sstream>
#include "boost/regex.hpp"
#include "ISearchable.hpp"
#include "GoogleTranslateSearch.hpp"
#include "QueryBuilder.hpp"
#include "ResultBuilder.hpp"
#include "NetworkConnection.hpp"

GoogleTranslateSearch::GoogleTranslateSearch()
{
}

GoogleTranslateSearch::~GoogleTranslateSearch()
{
}

int GoogleTranslateSearch::makeSearchRequest(std::string search_string)
{
	GoogleTranslateQueryBuilder builder;
	builder.setSearchKey(search_string);
	if (m_connection.send(builder.generateQuery()) > 0)
		return 1;
	else
		return -1;
}

std::string GoogleTranslateSearch::retrieveSearchResponse()
{
	std::stringstream buffer;
	while (m_connection.connected() && buffer.str().length() < 1024*30)
	{
		buffer << m_connection.recv(1024);
	}
	return buffer.str();
}

int GoogleTranslateSearch::search(std::string search_string)
{
	if (!m_connection.establish("translate.google.se", 80))
	{
		std::cerr << "Failed to establish connection to: translate.google.se" << std::endl;
		return EXIT_FAILURE;
	}

	if (!makeSearchRequest(search_string))
	{
		std::cerr << "Failed to perform search request" << std::endl;
		return EXIT_FAILURE;
	}

	std::string txt = retrieveSearchResponse();

    const boost::regex exp(">([^<^:]+)<(b|/div)");//TODO: regex sometimes get ">></div"
    //TODO: FIX THIS UGLY ARRAY and regex!
	int const subs[] = {1, 2};
	boost::sregex_token_iterator itr(txt.begin(), txt.end(), exp);
	boost::sregex_token_iterator end;
	m_result_builder.clear();

    //TODO: This is just copied from TydaSearch.cpp, and should be modified!
	for (;itr != end; ++itr)
	{
        std::cout << "# " << *itr << "\n";
//		if (*itr == "href=\"/search/")
//		{
//			if (++itr != end)
//				m_result_builder.addResult("Synonym", *itr);
//		}
//		else if (*itr == "id=\"tyda_transR")
//		{
//			if (++itr != end)
//				m_result_builder.addResult("Translation", *itr);
//		}
	}
	return EXIT_SUCCESS;
}

std::string GoogleTranslateSearch::getResult()
{
	return m_result_builder.getResultString();
}

std::string GoogleTranslateQueryBuilder::generateHeaders()
{
	std::string headers;
	headers  = "Host: translate.google.se\r\n";
	headers += "Connection: close\r\n";
	headers += "\r\n";
	return headers;
}

std::string GoogleTranslateQueryBuilder::generateRequestLine()
{
    //TODO: How to select language from program argument?
    // ex: ./a.out -g --sv2en hej
    // But what to do when we want to search on both Tyda and GoogleTranslate
	std::string request_line;
	request_line  = "GET /m?hl=en&sl=sv&tl=en&ie=UTF-8&prev=_m&q=";
	request_line += getSearchKey();
	request_line += " HTTP/1.1";
	request_line += "\r\n";

    return request_line;
}
