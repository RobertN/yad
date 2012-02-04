#ifndef SEARCHABLE_HPP
#define SEARCHABLE_HPP

#include <string>

class ISearchable
{
	public:
		virtual int search(std::string search_string) = 0;
		virtual std::string getResult() = 0;
};

#endif
