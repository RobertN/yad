#include "ResultBuilder.hpp"

#include <iostream>
#include <sstream>
using std::string;
using std::endl;
using std::vector;
using std::stringstream;

string ResultBuilder::getResultString() const
{
	vector< ResultEntry >::const_iterator it = m_entries.begin();
	stringstream result_stream;

    bool first = true;
    for (int i = 0; i < m_result_types.size(); i++)
    {
        result_stream << m_result_types[i] << ": ";
        for (it = m_entries.begin(); it != m_entries.end(); it++)
        {
            if ((*it).first == i)
            {
                if (first)
                {
                    result_stream << " " << (*it).second;
                    first = false;
                }
                else
                    result_stream << ", " << (*it).second;
            }
        }
        result_stream << endl;
        first = true;
    }
	return result_stream.str();
}

void ResultBuilder::addResult(int type, const string& value)
{
	m_entries.push_back(make_pair(type, value));
}

int ResultBuilder::addResultType(const string& description)
{
    m_result_types.push_back(description);
    return m_result_types.size() - 1;
}
