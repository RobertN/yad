#include "ResultBuilder.hpp"

#include <iostream>
#include <sstream>

std::string ResultBuilder::getResultString() const
{
	std::vector< ResultEntry >::const_iterator it = m_entries.begin();
	std::stringstream result_stream;
	for ( ; it != m_entries.end(); it++)
		result_stream << m_result_types[(*it).first] << ": " << (*it).second << std::endl;
	return result_stream.str();
}

void ResultBuilder::addResult(int type, const std::string& value)
{
	m_entries.push_back(make_pair(type, value));
}

int ResultBuilder::addResultType(const std::string& description)
{
    m_result_types.push_back(description);
    return m_result_types.size() - 1;
}
