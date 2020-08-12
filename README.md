### Autocomplete Challenge

### Author : Janani Selvan
### University of Colorado Boulder
### Purpose: Stateless Summer 2020 Software Engineering Internship
```
Aim: Auto-complete engine that suggests phrases based on the most commonly occurring phrases
in the corpus using efficient Data Structures -Trie and Priority Queue to auto-complete query prefixes. 
```

#### Programming Language : C++
#### Testing Framework    : GoogleTest (GTEST)
#### Platform             : Linux


### Input :
Reads in a corpus of text/dictionary whose name is passed as a command line argument to the autocomplete engine.
### Output :
Suggests a list of the max_count most-frequently-occurring phrases in the corpus that start with or exactly match prefix.
### Query format :
complete, phrase, max_count 

where 

prefix    :the prefix to autocomplete

max_count :the maximum number of autocomplete results to return

### Build Infrastructure for program execution:
Follow the below steps to execute the Makefile commands by navigating to the mak folder on the terminal under 
"auto-complete engine/mak" directory.
* To install g++ compiler:
make install-g++

* To compile the auto-complete engine:
make compile

* To run the auto-complete engine:
make run

### Build Infrastructure for program testing:
Follow the below steps to execute the Makefile commands by navigating to the mak folder on the terminal under 
"auto-complete engine/tests/src/mak".
* To install gtest framework:
make install

* To run the positive and negative test cases:
navigate to "auto-complete engine/tests/src/" and execute the below commands

cmake CMakeLists.txt

make

./executeTests

### Thought Process
### Files and Code Description:

### Input File:
* Auto-complete engine will accept file name of the corpus present at input/corpus.txt as command line argument(input parameter).
* The input file has a list of phrases, with one phrase per line containing A-Z,a-z and space. Therefore having a character set of 27

### Output Format:
Auto-complete engine will output the results of each query as a comma-separated list of phrases to stdout.

Cases of max_count :
* Case count is 0 :contain all keys that start with prefix.
* Case suggested list is less than max_count then all the valid phrases available starting with or matching prefix are listed.
* Case Output as many as max_count number of matched prefixes.
* Case when the max_count is greated than the matched set of prefixes then output all the matched prefixes

### Description of Solution: 

### Design Choices and Data Structure Rationale:

### Trie Data Structure:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

Trie data structure is a perfect fit to implement auto-complete engine efficient in terms of memory and time with time complexity of [O(length of string)].TRIE Data Structure also known as the Prefix Tree or Radix Tree is as an excellent Data Structure for processing and storing the phrases and is primarily used for word retrieval. The nodes in the TRIE Data Structure are used for storing the associate keys of strings and values that are being stored in the TRIE.

* Each node in TRIE has pointers to the 27(a-z,space) different alphabets of English Language.
The advantage of using TRIE Data Structure:
* No Collision of different Keys in a TRIE Data Structure make it an effective Data Structure for storing lexicographic words found in a input corpus.
* The Best Case Time Complexity is O(1), Average and Worst Case is O(Length-Of-Key).
  
### STL Map:
STL Maps are efficient to store the number of occurances of the phrases in the input corpus with lookup complexity of O(1) in order to auto-complete phrases that most-commonly occured in the input corpus.
                                                                                                                                                                                                                                                          
### Priority Queue:
As the expectation was to output max_count number of most commonly occuring phrases,I chose to use Priority Queue where every element recived priority based on the phrase frequncy.Therefore the phrase that matched the query prefix and havinf the higest phrase frequecny will be dequeued before the element with low priority.
Time complexity: O(n * log(n)) where n is the number of items added to the queue i.e the auto-complete suggestion result in chronological order.

### Overal Algorithmic Efficiency

O(Length-Of-Key) + O(1) + O(n * log(n))

where n is the number of chronologically matched prefix phrases to the input queries from the input corpus.

### Testing procedure for quality:

The Auto-complete engine is tested for the list of suggestions using Gtest unint testing framework for C++.
Overall 8 positive and 8 negative input test cases has been added to test the result of search_query logic of Auto-complete engine.Use the Build infrastructure to excecute the test cases.

### Scope of Improvement:

* Resize the Priority Queue based on the size of max_count to maintain a queue as a cache size of max_count with only most-commonly-occuring phrases in memory.
* Incorporating the frequency of the phrase in the node of the Trie Tree data structure.(extening the Trie node implentation)

### Important Assumptions:
* Input corpus has reapeated phrases or words.
* Important assumption is that the corpus can contain words and phrases like "bat" and "outside the" thereby the input file has a list of phrases, with one phrase per line containing A-Z,a-z and space. Therefore having a character set of 27.
* It is also assumed that the expectation is to output the list of max_count of "most-commonly occuring" or "most-frquently occuring" that starts or exactly match the prefix of the query.
* Comparisons between the provided prefix and the corpus of phrases all in lower case(case insensitively).
* In case of a tie to recommend matched prefix, followed to output any of the most-frequently-occurring phrases.
* The outputted list does not follow any particular order.
* Case when the max_count is greated than the matched set of prefixes then output all the matched prefixes


### Result
Auto-complete engine that suggests phrases based on the most commonly occurring phrases in the corpus to user queries.

### Submission Checklist:
* Autocomplete Engine Code in C++
* Test assets using Gtest
* Makefile
* README

### Submission format:
tarball






