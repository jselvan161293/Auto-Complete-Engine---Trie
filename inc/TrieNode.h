/*---------------------------------------------------------------------------------
The header file of the Node of Trie data structure describing the node with
setter and getter methods.
-----------------------------------------------------------------------------------*/

#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
// Alpahbet size (a-z,space) all lower case.
#define ALPHABETS (27) 

/*---------------------------------------------------------------------------------
This class represesnts the node of the trie tree data structure used as dictionary
    * Has a pointer to next node for each alphabet (a-z and space) in the character set.
    * end_of_word is true if the trie node represents the word end.
-----------------------------------------------------------------------------------*/
class TrieNode 
{
	friend class TrieTree;
private:
	char letter;
	bool end_of_word; 
    TrieNode *children[ALPHABETS];
public:
	TrieNode() // constructor
    {  
        for (int i = 0; i < ALPHABETS; i++)
		    this->children[i] = NULL;
	    this->set_end_of_word(false);
        this->set_letter('\0');	    
    } 
	~TrieNode() //destructor
    {
        for (int i = 0; i < ALPHABETS; i++)
		    this->children[i] = NULL;
	    this->set_end_of_word(false);
        this->set_letter('\0');
    }
    // setter functions
	void set_end_of_word(int word) 
    {
        this->end_of_word = word;
    } 
    void set_letter(char ch) 
    {
        this->letter = ch;
    }
    // getter functions
	bool get_end_of_word() 
    {
        return this->end_of_word;
    }
	char get_letter() 
    {
        return this->letter;
    }
};

#endif

/*----------------------------------------------------------------------------------*/