#ifndef QUERYBUILDER_HPP
#define QUERYBUILDER_HPP

#include <string>

class QueryBuilder
{
public:
    virtual void setSearchKey(std::string search_key) { m_search_key = search_key; }

    std::string generateQuery();

protected:
    std::string getSearchKey() const { return m_search_key; }

private:
    virtual std::string generateHeaders();
    virtual std::string generateRequestLine() = 0;

    std::string m_search_key;
};

#endif // QUERYBUILDER_HPP
