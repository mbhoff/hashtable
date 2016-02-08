/**************************************************************************//**
 * @file 
 *****************************************************************************/

/**
*	@class myhash
*	@brief myhash includes functions that insert items to the table,
*   rehash the table, sort the table, find and delete items, output the table
*   information to csv and wrd files.
*
*
*	@author Mark
*	@author Other team member
*/



#ifndef _HASH_H_
#define _HASH_H_
#include <vector>
#include <string>


using namespace std;

///hash class
class myhash
{
	private:

        /// node stores each word and its frequency
		struct node
		{
            /// word
 			string word;
            /// frequency of the word
  			int frequency = 0;
		};
		
        /// the vector table stores the words and their frequency
		vector<node> table;
        /// size of the table
		int tableSize;
        /// function to rehash the table
		bool rehash();
        ///unique words
		int uniqueElements = 0;
        /// total words
		int totalWords = 0;
	
	public:

        /// constructor sets tableSize to 1009
		myhash();

        /// deconstructor
		~myhash();

        /// hashes the words and inserts them in the table
		bool insertItem(string item);

        /// finds a specific word in the table
		int findItem(string item);

        /// deletes a specific word in the table
		bool deleteItem(string item);

        /// prints the frequency of all words in the console
		int printfrequency();

        /// outputs the rank, frequency and rank*frequency to a csv file
		bool outputcsv(string inputfile);

        /// outputs the average rank, and frequency of each word group and lists words in each group
		bool printTxt(string fileName);

        /// frequency compare function for qsort
		friend int comparefreq(const void* a, const void* b);

        /// alphabeticcal compare function for qsort
		friend int comparealpha(const void* a, const void* b);

        /// function to sort the table by frequency and each frequency group by alphabetical order
		bool sort();


};

#endif

