#include <iostream>
#include "NetworkConnection.hpp"
#include "TydaSearch.hpp"
#include "DummySearch.hpp"


int main(int argc, char *argv[])
{

    ISearchable *searchable;

	// TODO: Check what site we should search from
    if (argc == 2){
        //TODO Standard search
        //TODO: should we really have dynamic allocation???
        searchable = new TydaSearch();
        searchable->search(argv[1]);
        std::cout << searchable->getResult() << std::endl;
        delete searchable;

    }
    else if (argc == 3){
        //TODO Check flags for search options
        if (argv[1][0] != '-'){
            //TODO error message
            std::cout << "Error: Too many arguments or no flags!" << std::endl;
            return 1;
        }
        int i = 1;
        while (argv[1][i] != '\0')
        {
            switch(argv[1][i])
            { //TODO: should we really have dynamic allocation???

                case 't' : searchable = new TydaSearch();
                           break;
                case 'd' : searchable = new DummySearch();
                           break;
                default : //TODO error message
                          std::cout << "Error: Flag " 
                              << "\"" << argv[1][i] << "\""
                              << " dose not exist!" << std::endl;
                          return 1;
            }
            std::cout << "flag: " << argv[1][i] << " word: " << argv[2] << std::endl;

            searchable->search(argv[2]);
            std::cout << searchable->getResult() << std::endl;
            delete searchable;
            i++;
        }
        if (i == 1){
            //TODO error message
            std::cout << "Error: No flags!" << std::endl;
        }
    }
    else
    {
        //TODO error message
        std::cout << "Error: Too many or no arguments!" << std::endl;
        return 1;
    }


    return 0;
}
