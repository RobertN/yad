#ifndef RESULTBUILDER_HPP
#define RESULTBUILDER_HPP

#include <string>
#include <vector>
using std::string;
using std::vector;
using std::pair;

typedef pair< int, string > ResultEntry;

class ResultBuilder
{
public:
	/**
	 * Generates a string from the results that has been
	 * added to the builder.
	 */
	string getResultString() const;

	/**
	 * Adds a new result to the builder.
	 *
	 * @param type Defines what the type of the result is.
	 * @param value The value for the result.
	 */
	void addResult(int type, const string& value);

	/**
	 * Removes all results.
	 */
	void clear() { m_entries.clear(); }

	/**
	 * Since a search can generate different kinds of responses
	 * the user of the ResultBuilder can create a new type for
	 * each kind of response that should be saved.
	 *
	 * @param description Description for the new response type.
	 * @return Returns ID for the newly created response type.
	 */
	int addResultType(const string& description);

private:
	vector< ResultEntry > m_entries;
	vector< string > m_result_types;
};

#endif // RESULTBUILDER_HPP
