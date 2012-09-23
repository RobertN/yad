#include <iostream>
#include <sstream>
#include <boost/regex.hpp>
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
    std::string fromLang("auto");
    std::string toLang("en");

    if (argc == 3)
        search_string = argv[2];
    else if (argc == 4)
    {
        fromLang = argv[1];
        toLang = argv[2];
        search_string = argv[3];
    }
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

void GoogleTranslateSearch::printLangHelp()
{
    std::cout << ""
        << "\t" << "Code" << "\t" << "Language\n"
        << "\t" << "auto" << "\t" << "Detect language\n"
        << "\t" << "af" << "\t" << "Afrikaans\n"
        << "\t" << "sq" << "\t" << "Albanian\n"
        << "\t" << "ar" << "\t" << "Arabic\n"
        << "\t" << "hy" << "\t" << "Armenian\n"
        << "\t" << "az" << "\t" << "Azerbaijani\n"
        << "\t" << "eu" << "\t" << "Basque\n"
        << "\t" << "be" << "\t" << "Belarusian\n"
        << "\t" << "bn" << "\t" << "Bengali\n"
        << "\t" << "bg" << "\t" << "Bulgarian\n"
        << "\t" << "ca" << "\t" << "Catalan\n"
        << "\t" << "zh-CN" << "\t" << "Chinese\n"
        << "\t" << "hr" << "\t" << "Croatian\n"
        << "\t" << "cs" << "\t" << "Czech\n"
        << "\t" << "da" << "\t" << "Danish\n"
        << "\t" << "nl" << "\t" << "Dutch\n"
        << "\t" << "en" << "\t" << "English\n"
        << "\t" << "eo" << "\t" << "Esperanto\n"
        << "\t" << "et" << "\t" << "Estonian\n"
        << "\t" << "tl" << "\t" << "Filipino\n"
        << "\t" << "fi" << "\t" << "Finnish\n"
        << "\t" << "fr" << "\t" << "French\n"
        << "\t" << "gl" << "\t" << "Galician\n"
        << "\t" << "ka" << "\t" << "Georgian\n"
        << "\t" << "de" << "\t" << "German\n"
        << "\t" << "el" << "\t" << "Greek\n"
        << "\t" << "gu" << "\t" << "Gujarati\n"
        << "\t" << "ht" << "\t" << "HaitianCreole\n"
        << "\t" << "iw" << "\t" << "Hebrew\n"
        << "\t" << "hi" << "\t" << "Hindi\n"
        << "\t" << "hu" << "\t" << "Hungarian\n"
        << "\t" << "is" << "\t" << "Icelandic\n"
        << "\t" << "id" << "\t" << "Indonesian\n"
        << "\t" << "ga" << "\t" << "Irish\n"
        << "\t" << "it" << "\t" << "Italian\n"
        << "\t" << "ja" << "\t" << "Japanese\n"
        << "\t" << "kn" << "\t" << "Kannada\n"
        << "\t" << "ko" << "\t" << "Korean\n"
        << "\t" << "lo" << "\t" << "Lao\n"
        << "\t" << "la" << "\t" << "Latin\n"
        << "\t" << "lv" << "\t" << "Latvian\n"
        << "\t" << "lt" << "\t" << "Lithuanian\n"
        << "\t" << "mk" << "\t" << "Macedonian\n"
        << "\t" << "ms" << "\t" << "Malay\n"
        << "\t" << "mt" << "\t" << "Maltese\n"
        << "\t" << "no" << "\t" << "Norwegian\n"
        << "\t" << "fa" << "\t" << "Persian\n"
        << "\t" << "pl" << "\t" << "Polish\n"
        << "\t" << "pt" << "\t" << "Portuguese\n"
        << "\t" << "ro" << "\t" << "Romanian\n"
        << "\t" << "ru" << "\t" << "Russian\n"
        << "\t" << "sr" << "\t" << "Serbian\n"
        << "\t" << "sk" << "\t" << "Slovak\n"
        << "\t" << "sl" << "\t" << "Slovenian\n"
        << "\t" << "es" << "\t" << "Spanish\n"
        << "\t" << "sw" << "\t" << "Swahili\n"
        << "\t" << "sv" << "\t" << "Swedish\n"
        << "\t" << "ta" << "\t" << "Tamil\n"
        << "\t" << "te" << "\t" << "Telugu\n"
        << "\t" << "th" << "\t" << "Thai\n"
        << "\t" << "tr" << "\t" << "Turkish\n"
        << "\t" << "uk" << "\t" << "Ukrainian\n"
        << "\t" << "ur" << "\t" << "Urdu\n"
        << "\t" << "vi" << "\t" << "Vietnamese\n"
        << "\t" << "cy" << "\t" << "Welsh\n"
        << "\t" << "yi" << "\t" << "Yiddish\n"
        << std::endl;
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
