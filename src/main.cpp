/*---------------------------------------------------------------------------------
Autocomplete Engine
Author : Janani Selvan
University of Colorado Boulder
Purpose: Stateless Summer 2020 Software Engineering Internship

Aim: Auto-complete engine that suggests phrases based on the most commonly occurring phrases
in the corpus using efficient Data Structures -Trie and priority Queue to auto-complete query prefixes.
-----------------------------------------------------------------------------------*/
/* Includes Section */
#include <bits/stdc++.h>
#include <fstream>
#include "../inc/TrieNode.h"
#include "../inc/TrieTree.h"
#include <iostream>
using namespace std;

/*-----------------------------------------------------------------------------------
Helper Function:
Tokenize the input query based on comma as the delimeter.
-----------------------------------------------------------------------------------*/
vector<string> split(const string &s) {
    std::stringstream ss(s);
    std::string word;
    vector<std::string> tokens;
    while (std::getline(ss, word, ',')) {

        tokens.push_back(word);
    }
    return tokens;
}
/*---------------------------------------------------------------------------------
Main function of the Auto-complete Engine
Input :
Reads in the corpus name as command line argument to the autocomplete engine.
Output :
Results of suggestion for the list of queries performed on autocomplete engine.
Query Format :
complete, phrase, max_count 
-----------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    std::string phrases;
    std::string query;
    std::fstream fs;
    std::string q;
    std::vector <std::string> tokens;
    std::vector <std::string> auto_complete_result;
    stringstream ss(query);
    TrieTree suggestion;
    
    std::cout << "Opening the file." << std::endl;
    //Lets assume argv[1] is a filename to open

    try
    {
        fs.open(argv[1],std::fstream::in);
        // check to see if file opening succeeded
        if (fs.is_open())
        {   
            while (std::getline(fs, phrases)) 
            {   
                //Reads the phrases from the input and populates the map and trie data structures.
                transform(phrases.begin(), phrases.end(), phrases.begin(), ::tolower); 
                suggestion.set_map(phrases);
                suggestion.insert_word(phrases);
            }
        }
        else
	    {
		    std::cout << "Cannot open the corpus to read the phrases." << std::endl;
		    return 0; 
	    }
    }
    catch(const std::exception& e)
    {
		std::cerr << "Cannot open the corpus to read the phrases." << std::endl;
        fs.close();
        return 0;
    }

    //file is closed here
    fs.close();

    std::cout<< "Corpus parsed successfully."<< std::endl ;

    std::cout << "Query section start" << std::endl; 
       
    while(1)
    {   
        std::cout << "Enter query of the format complete, prefix, max_count" << std::endl;
        std::getline(std::cin, query);

        transform(query.begin(), query.end(), query.begin(), ::tolower);
        // Validate the query
        
        try
        {   
            tokens = split(query); 
            if(tokens[0]=="complete")
            {   
                // Obtains the suggestions from autocomplete engine
                auto_complete_result = suggestion.parse_query(tokens[1],tokens[2]);
                //print suggestions as comma seperated on stdout as result
                suggestion.print_suggestions(auto_complete_result);
            }
            else
            {
                std::cout << "Invalid query format" << std::endl;
                //continue; 
            }      
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Invalid query format" << std::endl; 
        }
        std::cout << "\nDo you want to continue? Enter No to exit!" << std::endl;  
        std::cin >> q ;
        transform(q.begin(), q.end(), q.begin(), ::tolower);
        if(q == "no")
        {
            break;
        }
        else
        {
            std::cin.ignore( 256, '\n' ) ;
        }
        
    }

    return 0;
}

/*----------------------------------------------------------------------------------*/
