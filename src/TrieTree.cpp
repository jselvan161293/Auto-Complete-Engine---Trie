/*---------------------------------------------------------------------------------
Business logic of Auto-complete Engine
-----------------------------------------------------------------------------------*/
#include <bits/stdc++.h>
#include <iostream>
#include "../inc/TrieTree.h"
#include "../inc/TrieNode.h"
using namespace std;

/*-----------------------------------------------------------------------------------
Helper Function:
Convert character to integer to obtain the pointer of child node.
-----------------------------------------------------------------------------------*/

int c2i(char c)
{
	if (c ==' ')
	{
		return 26;
	}
	else return static_cast<int>(c - 'a');
}

/*-----------------------------------------------------------------------------------
Helper Function:
Max Heap (Priority Queue) ordered by second element in the pair
-----------------------------------------------------------------------------------*/

struct comparator {
    template<typename T, typename U>
    bool operator()(T const& lhs, U const& rhs) const {
        return lhs.second < rhs.second;
    }
};


/*---------------------------------------------------------------------------------
This method inserts words into the trie dictionary to build the tree 
	* case 1:character exists : just traverses
	* case 2:character does not exists : creates new node
	* Marks end of word in both the cases 
-----------------------------------------------------------------------------------*/
void TrieTree::insert_word(std::string word) 
{
	TrieNode* current = root;
	int iptr = 0;	
	for (int i = 0; i < word.length(); i++)
	{   
		iptr = c2i(word[i]);	
		if (current->children[iptr] == NULL) 
		{
			current->children[iptr] = new TrieNode(); 
			current = current->children[iptr];
			current->set_letter(word[i]); 
		}
		else
		{			
			current = current->children[iptr];	
		}	
	}
	current->set_end_of_word(true); 
}


/*---------------------------------------------------------------------------------
 This fucntion builds key map to track the frequency of input phrases
----------------------------------------------------------------------------------*/
void TrieTree::set_map(std::string word)  {
      
        if (this->phrase_freq_map.find(word)!= this->phrase_freq_map.end())
		{
			this->phrase_freq_map[word] = this->phrase_freq_map[word] + 1 ;
		} 
        else
		{
                this->phrase_freq_map.insert(std::make_pair(word, 1));
		}
    }

/*---------------------------------------------------------------------------------
This function validates the result of autocompletion engine and prints max_count of 
most-commonly occuring phrases
    * Case count is 0 :contain all phrases that start with ​prefix 
	* Case suggested list is less than max_count then all the valid phrases available 
	  starting with or matching prefix are listed.
	* Case Output as many as max_count number of matched prefixes.
	* Case max_count greater than search result, then output all the suggestions.
----------------------------------------------------------------------------------*/
std::vector<std::string> TrieTree::parse_query(std::string prefix,std::string max_count)
{
	vector<std::string> search_result;
	vector<std::string> result;
	pair<std::string, int> top;
	priority_queue<pair<std::string,int>,
                   std::vector<pair<std::string,int> >,
                   comparator > pq; 
	
	int count = std::stoi(max_count);

	// Results of search operation from Trie for the prefix.
	search_result = this->search_word(prefix);
	// If results exits
	if(search_result.size()!=0)
	{
		// Obtain the frquency of the matched phrases from the input corpus.
		for(int i=0;i<search_result.size();i++)
		{
			pq.push(make_pair(search_result[i], this->phrase_freq_map[search_result[i]])); 
		}

		if(count == 0)
		{	
			while(!pq.empty())
			{
				top = pq.top(); 
				pq.pop();
				result.push_back(top.first);
			}
		}
		if(count <= search_result.size())
		{
			while(count>0)
			{   
    			top = pq.top(); 
				result.push_back(top.first);
				pq.pop();
				count--;
			}  
		}
		else
		{
			int size = search_result.size();
			while(size>0)
			{   
    			top = pq.top(); 
				result.push_back(top.first);
				pq.pop();
				size--;
			} 
			
		}
		
	}
	else
	{
		result.push_back("");
	}
	return result;
}

/*---------------------------------------------------------------------------------
This methods forms the basis of auto-completion engine.
	* Traverses through the phrase and checks if prefix exits
	* Notifies when it fails to find the prefix or when there is character mismatch
	* auto suggests for the given prefix 
----------------------------------------------------------------------------------*/
vector<std::string> TrieTree::search_word(std::string word) 
{	
	TrieNode* current = root;
	int iptr = 0;
	int n = word.length();
	std::vector<std::string> tmp = {};
	try
	{
		for (int i = 0; i < n; i++) 
		{   
			iptr = c2i(word[i]);
			if (current->children[iptr] != NULL)
			{
				current = current->children[iptr];			
			}
			else if (current->get_letter() != word[i])
			{			
				return tmp;	
			}
			else if (current->children[iptr] == NULL)
			{
				return tmp;

			}
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Phrase not found." << std::endl;
	}
	std::string query = word; 
	return auto_complete(current, word, query);
}

/*---------------------------------------------------------------------------------
This function is the checks the tree to provide suggestions based on query to complete the query
	Traverse through the character set to check if the character has a matched next character
	When a child is found the matched character is recorded to complete the prefix until
	the prefix word completes to form a word/phrase as present in corpus.This continues.
----------------------------------------------------------------------------------*/
vector<std::string> TrieTree::auto_complete(TrieNode* root, std::string query, std::string word) 
{   
	vector<std::string> search_result;
	for (int i = 0; i < ALPHABETS; i++) 
	{
		TrieNode *current = root;
		if (current->children[i] != NULL) 
		{
			current = current->children[i]; 
			word = this->append_match(current,word);
			if (current->get_end_of_word()) 
			{
				search_result.push_back(word);
			}
			auto_complete_util(current, word,search_result); 
		}
		word = query; 
	}
	return search_result;
}

/*---------------------------------------------------------------------------------
This function starts completing the prefix from matched chracters obtianed from the 
trie on search operation to form a meaning word which matchs the word or begin with 
query prefix.
----------------------------------------------------------------------------------*/
std::string TrieTree::append_match(TrieNode* root,std::string word)
{
	return  word + root->get_letter(); 
}

/*---------------------------------------------------------------------------------
This function is a utility function to find suggestion in the subtree for the 
recursive search operation in the trie data structure.
----------------------------------------------------------------------------------*/
void TrieTree::auto_complete_util(TrieNode* root, std::string word,vector<std::string>& search_result) 
{
	std::string query = word;
	for (int i = 0; i < ALPHABETS; i++)
	{
		TrieNode *current = root;
		if (current->children[i] != NULL)
		{
			current= current->children[i];
			word = this->append_match(current,word);
			if (current->get_end_of_word())
			{
				search_result.push_back(word);
			}
			auto_complete_util(current, word,search_result);
		}
		word = query;
	}
}

/*---------------------------------------------------------------------------------
This function Suggests a list of max_count most-frequently-occurring phrases in the 
corpus that start with or exactly match prefix of query.
-----------------------------------------------------------------------------------*/
void TrieTree::print_suggestions(vector<std::string>& auto_complete_result)
{
	for (auto iter = auto_complete_result.begin(); iter != auto_complete_result.end(); iter++) 
    {     
        if (iter != auto_complete_result.begin()) 
        {
            std::cout << ", ";
		}
        std::cout << *iter;      
    }
}

/*-----------------------------------------------------------------------------------*/
