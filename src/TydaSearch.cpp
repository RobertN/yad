#include <sstream>
#include <iostream>
#include "boost/regex.hpp"
#include "ISearchable.hpp"
#include "TydaSearch.hpp"
#include "QueryBuilder.hpp"
#include "ResultBuilder.hpp"
#include "NetworkConnection.hpp"

TydaSearch::TydaSearch()
{
}

TydaSearch::~TydaSearch()
{
}

int TydaSearch::makeSearchRequest(std::string search_string)
{
	TydaQueryBuilder tyda_builder;
	tyda_builder.setSearchKey(search_string);
	if (m_connection.send(tyda_builder.generateQuery()) > 0)
		return 1;
	else
		return -1;
}

std::string TydaSearch::retrieveSearchResponse()
{
	std::stringstream buffer;
	while (m_connection.connected() && buffer.str().length() < 1024*30)
	{
		buffer << m_connection.recv(1024);
	}
	return buffer.str();
}

int TydaSearch::search(std::string search_string)
{
	if (!m_connection.establish("tyda.se", 80))
	{
		std::cerr << "Failed to establish connection to: tyda.se" << std::endl;
		return EXIT_FAILURE;
	}

	if (!makeSearchRequest(search_string))
	{
		std::cerr << "Failed to perform search request" << std::endl;
		return EXIT_FAILURE;
	}

	std::string txt = retrieveSearchResponse();

	/* Find synonyms and translations
     *
     * <a id="tyda_transR7" href="/search/hey">hey</a>
     * const boost::regex exp("<a id=\"(tyda_transR[^\"]*)\" href=\"[^\"]*\">([^<]*)");
     *
     * <a href="/search/goddag">goddag</a>
     * const boost::regex exp("<a href=\"\\/(search)\\/[^\"]*\">([^<]*)");
     *
	 */
    const boost::regex exp("(<a href=\"\\/search\\/[^\"]*\">|<span class=\"tyda_assoc_word\">)([^<]+)<");
	int const subs[] = {1, 2};
	boost::sregex_token_iterator itr(txt.begin(), txt.end(), exp, subs);
	boost::sregex_token_iterator end;
	m_result_builder.clear();
    int type_synonym = m_result_builder.addResultType("Synonym");
    int type_translation = m_result_builder.addResultType("Translation");

	for (;itr != end; ++itr)
	{
		if (*itr == "<span class=\"tyda_assoc_word\">")
		{
			m_result_builder.addResult(type_translation, *++itr);
		}
        else 
		{
			m_result_builder.addResult(type_synonym, *++itr);
		}
	}
	return EXIT_SUCCESS;
}

std::string TydaSearch::getResult()
{
	return m_result_builder.getResultString();
}

std::string TydaQueryBuilder::generateHeaders()
{
	std::string headers;
	headers  = "Host: tyda.se\r\n";
	headers += "Connection: close\r\n";
	headers += "\r\n";
	return headers;
}

std::string TydaQueryBuilder::generateRequestLine()
{
	std::string request_line;
	request_line  = "GET /search?form=1&w=";
	request_line += getSearchKey();
	request_line += "&w_lang=&x=0&y=0 HTTP/1.1";
	request_line += "\r\n";
	return request_line;
}
