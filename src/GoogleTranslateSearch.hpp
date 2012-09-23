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

    int search(const int argc, const char *argv[]);
    std::string getResult();
    static void printLangHelp();

private:
    bool makeSearchRequest(std::string search_string, std::string fromLang, std::string toLang);
    std::string retrieveSearchResponse();

    std::string m_results;
    NetworkConnection m_connection;
    ResultBuilder m_result_builder;
};

class GoogleTranslateQueryBuilder: public QueryBuilder
{
public:
    void setFromLang(std::string fromLang){ m_fromLang = fromLang; }
    void setToLang(std::string toLang){ m_toLang = toLang; }

protected:
    std::string getToLang() const { return m_toLang; }
    std::string getFromLang() const { return m_fromLang; }

private:
    virtual std::string generateHeaders();
    virtual std::string generateRequestLine();

    std::string m_fromLang;
    std::string m_toLang;
};

#endif
