#include <iostream>
#include "NetworkConnection.hpp"
#include "TydaSearch.hpp"
#include "GoogleTranslateSearch.hpp"
#include "DummySearch.hpp"
#include "debug.hpp"

#define VERSION 0.2

using std::cout;
using std::endl;

void help(std::string pName)
{
	cout << "Usage:\t" << pName << " -[tgd] Search_word" << endl
	           << "\t" << pName << " Search_word" << endl
	           << "\t" << pName << " -g \"Sentence\"" << endl
	           << "\t" << pName << " -g From_lang_code To_lang_code \"Sentence\"" << endl
	           << "\t" << pName << " From_lang_code To_lang_code \"Sentence\"" << endl
	           << "\t" << pName << " -[vhl]" << endl << endl
         << "Use flag \"l\" for display language codes: " << pName << " -l" << endl << endl;
}

void doSearch(ISearchable *searchable, int argc, char *argv[])
{
    int exitCode = searchable->search(argc, const_cast<const char **>(argv));
    if (exitCode == 0)
        cout << searchable->getResult() << endl;
    else
        std::cerr << "Error: Search exited with exit code: " << exitCode << endl;

    delete searchable;
}

int main(int argc, char *argv[])
{
	debug("Starting yad");

	if (argc < 2)
	{
        help(argv[0]);
		return -1;
	}

    if (argv[1][0] != '-')
    {   // Without flags
        if (argc == 4)
            doSearch(new GoogleTranslateSearch(), argc, argv);  // ./yad sv en hej
        else
            doSearch(new TydaSearch(), argc, argv);             // ./yad hej
    }
    else
    {   // With flags
        char *flags = argv[1];
        int i = 1;
        while (flags[i] != '\0')
        {
            switch(flags[i])
            {
                case 't':
                    doSearch(new TydaSearch(), argc, argv);
                    break;

                case 'g':
                    doSearch(new GoogleTranslateSearch(), argc, argv);
                    break;

                case 'd':
                    doSearch(new DummySearch(), argc, argv);
                    break;

                case 'h':
                    help(argv[0]);
                    break;

                case 'l':
                    GoogleTranslateSearch::printLangHelp();
                    break;

                case 'V':
                case 'v':
                    cout << "yad version: " << VERSION << endl;
                    break;

                default:
                    std::cerr   << "Error: Flag "
                                << "\"" << flags[i] << "\""
                                << " dose not exist!" << endl;
                    return -1;
            }
            i++;
        }
    }

	debug("Ending yad");

	return 0;
}
