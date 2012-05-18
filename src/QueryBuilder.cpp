#include "QueryBuilder.hpp"

std::string QueryBuilder::generateQuery()
{
	std::string request = generateRequestLine();
	std::string headers = generateHeaders();

	return request + headers;
}

std::string QueryBuilder::generateHeaders()
{
	return "Connection: close\r\n\r\n";
}
