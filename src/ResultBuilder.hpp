#ifndef RESULTBUILDER_HPP
#define RESULTBUILDER_HPP

#include <string>
#include <vector>

typedef std::pair< std::string, std::string > ResultEntry;

class ResultBuilder
{
public:
	std::string getResultString() const;
	void addResult(std::string type, std::string value);
	void clear() { m_entries.clear(); }
private:
	std::vector< ResultEntry > m_entries;
};

#endif // RESULTBUILDER_HPP
