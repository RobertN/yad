#include <iostream>
#include <unistd.h>
#include "NetworkConnection.hpp"
#include "TydaSearch.hpp"
#include "GoogleTranslateSearch.hpp"
#include "DummySearch.hpp"
#include "debug.hpp"

#define VERSION 0.2

using std::cout;
using std::endl;

void help(const std::string& name)
{
    cout << "Usage:\t" << name << " -[tgd] Search_word" << endl
               << "\t" << name << " Search_word" << endl
               << "\t" << name << " -g \"Sentence\"" << endl
               << "\t" << name << " -g From_lang_code To_lang_code \"Sentence\"" << endl
               << "\t" << name << " -[vhl]" << endl << endl
         << "Use flag \"l\" for display language codes: " << name << " -l" << endl << endl;
}

void doSearch(ISearchable *searchable, int argc, char *argv[])
{
    int exitCode = searchable->search(argc, const_cast<const char **>(argv));
    if (exitCode == 0)
        cout << searchable->getResult();
    else
        std::cerr << "Error: Search exited with exit code: " << exitCode << endl;

    delete searchable;
}

void parseCommandLineAndSearch(int argc, char *argv[])
{
    int ch;
    ISearchable *searchable = 0;
    bool search = true;
    while ((ch = getopt(argc, argv, "tghlVva")) != -1) {
        switch (ch) {
            case 't':
                searchable = new TydaSearch;
                break;
            case 'g':
                searchable = new GoogleTranslateSearch;
                break;
            case 'h':
                help(argv[0]);
                break;
            case 'l':
                GoogleTranslateSearch::printLangHelp();
                search = false;
                break;
            case 'V':
            case 'v':
                cout << "YAD version: " << VERSION << endl;
                break;

            default:
                std::cerr   << "Error: Flag "
                    << "\"" << ch << "\""
                    << " does not exist!" << endl;
                return;
        }
    }

    if (searchable && search) {
        doSearch(searchable, argc, argv);
    } else if (!searchable && search) {
        // Default option if no other search database has been selected.
        doSearch(new TydaSearch, argc, argv); 
    }
}

int main(int argc, char *argv[])
{
    debug("Starting YAD");

    if (argc < 2)
    {
        help(argv[0]);
        return -1;
    }

    parseCommandLineAndSearch(argc, argv);

    debug("Ending YAD");
    return 0;
}
