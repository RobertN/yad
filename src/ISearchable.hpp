#ifndef SEARCHABLE_HPP
#define SEARCHABLE_HPP

#include <string>

class ISearchable
{
public:
    virtual int search(const int argc, const char *argv[]) = 0;
    virtual std::string getResult() = 0;
    virtual ~ISearchable() {}
};

#endif
