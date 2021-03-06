#ifndef TYDASEARCH_HPP
#define TYDASEARCH_HPP

#include "QueryBuilder.hpp"
#include "ISearchable.hpp"
#include "NetworkConnection.hpp"
#include "ResultBuilder.hpp"

class TydaSearch: public ISearchable
{
public:
    TydaSearch();
    ~TydaSearch();

    int search(const int argc, const char *argv[]);
    std::string getResult();

private:
    bool makeSearchRequest(std::string search_string);
    std::string retrieveSearchResponse();

    std::string m_results;
    NetworkConnection m_connection;
    ResultBuilder m_result_builder;
};

class TydaQueryBuilder
    : public QueryBuilder
{
private:
    virtual std::string generateHeaders();
    virtual std::string generateRequestLine();
};

#endif
