/**************************************************************************//**
 * @file
 *****************************************************************************/


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "hash.h"
#include "tokenize.h"

using namespace std;



/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Compares frequency values of two nodes a and b. Converts
 * the struct to a node before comparing the frequency values.
 *
 * @param[in]    a - the first node to be compared
 * @param[in]    b - the second node to be compared
 *
 * @returns -1 - node a has greater frequency
 * @returns 0 - frequencies are the same
 * @returns 1 - node b has greater frequency
 *****************************************************************************/


int comparefreq(const void* a, const void* b)
{
	myhash::node *nodeA = (myhash::node *)a;
	myhash::node *nodeB = (myhash::node *)b;
	//cout << nodeA -> frequency;
	//cout << nodeB -> frequency;
		
	if (nodeA -> frequency > nodeB -> frequency)
	{
		return -1;
	}

	if (nodeA -> frequency == nodeB -> frequency)
	{
		return 0;
	}

	else
	{
		return 1;
	}
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Compares the string of two nodes a and b. Converts
 * the structs to nodes before comparing the strings.
 *
 * @param[in]    a - the first node to be compared
 * @param[in]    b - the second node to be compared
 * 
 * @returns -1 - node a comes before node b
 * @returns 0 - nodes have the same order
 * @returns 1 - node b comes before node a
 *****************************************************************************/


int comparealpha(const void* a, const void* b)
{
	//creates nodeA and nodeB sets them
	//equal to structs a and b typecasted as nodes.
	
	myhash::node *nodeA = (myhash::node *)a;
	myhash::node *nodeB = (myhash::node *)b;


	if (nodeA -> word < nodeB -> word)
	{

		return -1;
	}

	if (nodeA -> word == nodeB -> word)
	{
		return 0;
	}

	else
	{
		return 1;
	}


}


/**************************************************************************//** 
 * @author Mark, Other team member, Adapted from Dr. Weiss
 * 
 * @par Description: Converts a string to a vector of tokens, which in this
 * case are words. First the entire string is converted to lowercase. Then
 * int tokenStart is initialized to the first character in the string that
 * is valid. tokenEnd is initialized to the the next character that is not
 * a valid character.
 *
 * @param[in]    str - the str containing all of the text
 * @param[in]    tokens - the vector to store the tokens
 * @param[in]    valid - the string of valid alphabetical characters
 * 
 *****************************************************************************/

void tokenize2( string& str, vector<string>& tokens, const string& valid)
{
	for(int i = 0; str[i] != '\0'; i++)
	str[i]=tolower(str[i]);

    // skip delimiters to start of first token
    int tokenStart = str.find_first_of( valid, 0 );
    // find next delimiter (i.e., end of first token)
    int tokenEnd = str.find_first_not_of( valid, tokenStart );

	if( str[tokenEnd] == '\''  && str[tokenEnd+1] > 96 && str[tokenEnd+1] < 123 )
	{
		tokenEnd = str.find_first_not_of( valid, tokenEnd + 1 );
	}

    // loop through input string
    while ( tokenStart != (signed)string::npos )
    {
        // found a token, add it to the vector
        tokens.push_back( str.substr( tokenStart, tokenEnd - tokenStart ) );
        // skip delimiters to start of next token
        tokenStart = str.find_first_of( valid, tokenEnd );
        // find next delimiter (end of token)
        tokenEnd = str.find_first_not_of( valid, tokenStart );
		
		if( str[tokenEnd] == '\''  && str[tokenEnd+1] > 96 && str[tokenEnd+1] < 123 )
		{
			tokenEnd = str.find_first_not_of( valid, tokenEnd + 1);
		}
	
    }
}



/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Opens the file passed in, and seeks to the beginning.
 * Reads all of the inputfile into str. Initiallizes a vector of strings.
 * Calls the tokenize function, which fills the vector with strings. Calls
 * the vector function insertItem, which hashes the items and inserts them
 * into the hash table.
 * 
 *
 * @param[in]    inputfile - the name of the input file
 * @param[in]    fin - the input file
 * @param[in]    h - the hash class instance
 * 
 * @returns 0 - failed to open file
 * @returns 1 - function ran sucessfully
 *****************************************************************************/


int readFile(string inputfile, ifstream & fin, myhash & h)
{
    //open file for output in trunc mode


    fin.open(inputfile, ios::in);

    if (!fin)
    {
        //if unable to open, print error message
        //and return 0
        cout << inputfile << " failed to open for reading" << endl;
        return 0;

    }

	fin.seekg (0, fin.beg);
	
        string str;

	while (!fin.eof())
	{	

		getline(fin, str);


    
    // test delimiter version
    vector<string> tokens1;
    tokenize2( str, tokens1, VALID);
    for ( auto t :tokens1 ) h.insertItem(t);
    
    
 
}
    return 1;

}

