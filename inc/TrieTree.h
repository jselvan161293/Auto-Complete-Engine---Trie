/*---------------------------------------------------------------------------------
The header file of the Trie data structure viewed as a tree 
for processing and storing the phrases and is primarily used for word retrieval as
the list of suggestion for phrases that start or match the query prefix.

-----------------------------------------------------------------------------------*/

#ifndef TRIETREE_H
#define TRIETREE_H

#include <bits/stdc++.h>
#include <iostream>
#include "TrieNode.h"
using namespace std;

/*---------------------------------------------------------------------------------
This class facilitates the creation and query process of auto-completion engine.
    * Insert Function: This method inserts words into the trie dictionary to build the tree.
    * Search and Auto Complete Function: This methods forms the basis of auto-completion engine.
    * Append Match Function: Buiding the matched phrase chracter by chracter.
    * Parse Query Function: To validate the query and suggest list of most-commonly occuring prefix
    * Set Map Function: To keep the record of frequency of the phrases.
    * Print Suggestions Function: Helper function to output the final suggestion.
-----------------------------------------------------------------------------------*/
class TrieTree
{
    friend class TrieNode;
private:
	TrieNode* root;
    std::map<std::string, int> phrase_freq_map;
public:
	TrieTree() 
    {
        root = this->get_node(); 
    }
	~TrieTree() {}

    TrieNode* get_node()
    {
        return new TrieNode();
    }
	
	void insert_word(std::string word); 
	std::vector<std::string> search_word(std::string word); 
    std::string append_match(TrieNode* root,std::string word);
    std::vector<std::string> parse_query(std::string prefix,std::string max_count);
    void set_map(std::string word);
	std::vector<std::string> auto_complete(TrieNode* root, std::string query, std::string word); 
    void auto_complete_util(TrieNode* root, std::string query,vector<std::string>& result); 
    void print_suggestions(vector<std::string>& auto_suggestions_result);
};

#endif

/*----------------------------------------------------------------------------------*/
