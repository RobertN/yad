#include "ResultBuilder.hpp"

#include <iostream>
#include <sstream>

std::string ResultBuilder::getResultString()
{
	std::vector< ResultEntry >::iterator it = m_entries.begin();
	std::stringstream result_stream;
	for ( ; it != m_entries.end(); it++)
		result_stream << (*it).first << ": " << (*it).second << std::endl;
	return result_stream.str();
}

void ResultBuilder::addResult(std::string type, std::string value)
{
	m_entries.push_back(make_pair(type, value));
}
