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

bool GoogleTranslateSearch::makeSearchRequest(std::string search_string, std::string fromLang, std::string toLang)
{
	GoogleTranslateQueryBuilder builder;
	builder.setSearchKey(search_string);
    builder.setFromLang(fromLang);
    builder.setToLang(toLang);

	if (m_connection.send(builder.generateQuery()) > 0)
		return true;
	else
		return false;
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

int GoogleTranslateSearch::search(const int argc, const char *argv[])
{
    std::string search_string;
    std::string fromLang("sv");
    std::string toLang("en");

    if (argc == 3)
        search_string = argv[2];
    else if (argc == 5)
    {
        fromLang = argv[2];
        toLang = argv[3];
        search_string = argv[4];
    }
    else
        return 1;

    std::replace(search_string.begin(), search_string.end(), ' ', '+');
	
    if (!m_connection.establish("translate.google.se", 80))
	{
		std::cerr << "Failed to establish connection to: translate.google.se" << std::endl;
		return 2;
	}

	if (!makeSearchRequest(search_string, fromLang, toLang))
	{
		std::cerr << "Failed to perform search request" << std::endl;
		return 3;
	}

	std::string txt = retrieveSearchResponse();

    const boost::regex exp("(<br>|<div dir=\"ltr\" class=\"t0\">)([^<:]+)(<br>|<\\/div>)");
	int const subs[] = {1, 2};
	boost::sregex_token_iterator itr(txt.begin(), txt.end(), exp, subs);
	boost::sregex_token_iterator end;
	m_result_builder.clear();

	int type_translation = m_result_builder.addResultType("Translation");

	for (;itr != end; ++itr)
	{
		m_result_builder.addResult(type_translation, *++itr);
	}
	return 0;
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

	std::string request_line;
	request_line  = "GET /m?hl=en&sl=";
    request_line += getFromLang();
    request_line += "&tl=";
    request_line += getToLang();
    request_line += "&ie=UTF-8&prev=_m&q=";
	request_line += getSearchKey();
	request_line += " HTTP/1.1";
	request_line += "\r\n";

    return request_line;
}
