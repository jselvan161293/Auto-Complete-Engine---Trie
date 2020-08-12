/*---------------------------------------------------------------------------------
Autocomplete Engine
Author : Janani Selvan
University of Colorado Boulder
Purpuse: Stateless Summer 2020 Software Engineering Internship

/*---------------------------------------------------------------------------------
Test script for Auto-complete Engine with Google test framework in C++.
----------------------------------------------------------------------------------*/

#include "gtest/gtest.h"
#include "../../src/TrieTree.cpp"
#include "../../inc/TrieNode.h"



/*---------------------------------------------------------------------------------
Test class for Auto-complete engine
-----------------------------------------------------------------------------------*/
class trietreetest : public ::testing::Test {


        
    public:
        TrieTree tt;
        void loadphrases(std::string filename,TrieTree& tt);
        int comparator(vector<std::string> vec1,vector<std::string> vec2);
	    virtual void SetUp() {
        }
        

	virtual void TearDown() {}

};

/*---------------------------------------------------------------------------------
this function loads and inserts the phrases into trie data structure
-----------------------------------------------------------------------------------*/
void trietreetest::loadphrases(std::string filename,TrieTree& tt)
{   
    std::string phrases;
    std::fstream fs;
    fs.open(filename,std::fstream::in);
        if (fs.is_open())
        {   
            while (std::getline(fs, phrases)) 
            {   
                transform(phrases.begin(), phrases.end(), phrases.begin(), ::tolower); 
                tt.set_map(phrases);
                tt.insert_word(phrases);
               
            }
        }
        else
	    {
		    std::cout << "Cannot open the corpus to read the phrases." << std::endl;
		    exit(0);
	    }
	   
}
/*---------------------------------------------------------------------------------
this function compares the actual and expected result
-----------------------------------------------------------------------------------*/
int trietreetest::comparator(vector<std::string> vec1,vector<std::string> vec2) 
{ 

    if(vec1.size() == vec2.size())
    {
        for(int i =0;i<vec1.size();i++)
        {  
            if(vec1[i]!=vec2[i])
            {
                return 0;
            }
        }
    }
    else
    {   

        return 0;
    }

    return 1;
}

/*---------------------------------------------------------------------------------
 Test for query to complete with max_count of 1	 
-----------------------------------------------------------------------------------*/
TEST_F(trietreetest,onemaxcount){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("ba","1");
    EXPECT_EQ(1,comparator({"bat"},tmp));
    ASSERT_NE(1,comparator({"ba"},tmp));
}

/*---------------------------------------------------------------------------------
Test for query to complete with max_count of 2	
----------------------------------------------------------------------------------*/
TEST_F(trietreetest,twomaxcount){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("ba","2");
	EXPECT_EQ(1,comparator({"bat","bark"},tmp));
    ASSERT_NE(1,comparator({"bark"},tmp));

}
/*---------------------------------------------------------------------------------
Test for query to complete with max_count of 2
-----------------------------------------------------------------------------------*/
TEST_F(trietreetest,zeromaxcount){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("b","0");
	EXPECT_EQ(1,comparator({"bat","bark","bar"},tmp));
    ASSERT_NE(1,comparator({"bat","bark"},tmp));

}
/*---------------------------------------------------------------------------------
Test for query to complete when no prefix matches 
-----------------------------------------------------------------------------------*/
TEST_F(trietreetest,nomatch){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("be","1");
	EXPECT_EQ(1,comparator({""},tmp));
    ASSERT_NE(1,comparator({"bat"},tmp));
}

/*---------------------------------------------------------------------------------
Test for query to complete when a phrase is queried
-----------------------------------------------------------------------------------*/
TEST_F(trietreetest,queryphraseone){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("outside t","1");
	EXPECT_EQ(1,comparator({"outside thought"},tmp));
    ASSERT_NE(1,comparator({"outside"},tmp));
}

/*---------------------------------------------------------------------------------
Test for query to complete when a phrase is queried
----------------------------------------------------------------------------------*/
TEST_F(trietreetest,queryphrasetwo){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("outside t","2");
	EXPECT_EQ(1,comparator({"outside thought","outside the"},tmp));
    ASSERT_NE(1,comparator({"outside the"},tmp));
}

/*---------------------------------------------------------------------------------
Test for query to complete for a phrase starting with space
-----------------------------------------------------------------------------------*/
TEST_F(trietreetest,startwithspace){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query(" a","1");
    EXPECT_EQ(1,comparator({" and"},tmp));
    ASSERT_NE(1,comparator({"ate"},tmp));
}

/*---------------------------------------------------------------------------------
Test for query to complete for a word part as phrase as well
-----------------------------------------------------------------------------------*/
TEST_F(trietreetest,phraseandword){
    TrieTree tt;
    loadphrases("../../input/corpus.txt",tt);
	vector<std::string> tmp = tt.parse_query("out","3");
    EXPECT_EQ(1,comparator({"outside thought","outside the","output"},tmp));
    ASSERT_NE(1,comparator({"outside thought"},tmp));
}

/*---------------------------------------------------------------------------------
Gtest main
-----------------------------------------------------------------------------------*/
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}

/*-----------------------------------------------------------------------------------*/