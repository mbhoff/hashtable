/**************************************************************************//**
 * @file
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include "tokenize.h"
#include <time.h>


/*************************************************************************//**
 * @file 
 *
 * @mainpage Zipf's Law
 * 
 * @author Mark, Other team member
 * 
 * @section program_section Program Information 
 * 
 * @details This program tests Zipf's Law, which states that
 * The frequency of a word is inversely proportional to its statistical rank
 * in a text. To do this, our program extracts words from a text using
 * tokenize functions and inserts them into a hash table with a hash
 * function.
 * 
 * Our program includes a class myhash, which stores the hash table, and
 * the functions for inserting an item, rehashing the table, sorting
 * the table, finding a value in the table, and deleting a value in the table.
 *
 * The insert function creates a key for each word by summing the ascii values
 * of the words letters, and multiplying them by 37. Then that number
 * is multiplied by the length of the string, multiplied by the
 * ascii value of the first character of the string. If the string length
 * is between 2 and 4, the key is multiplied by the ascii value of the
 * second character in the string. If the string has at least 4 characters,
 * the key is multiplied by the 4th character in the string. Then the key
 * is modded by size of the table. The function then tries to insert
 * the word at the position of the key value.
 * 
 * The insert functions insert the word at the position pos, and uses
 * linear probing to solve collision cases. If the position is filled
 * the function will iterate through the table and insert it at 
 * the next open position in the table.
 * 
 * While inserting the items, if the table becomes 75% full,
 * the rehash function is called, which  creates a new table twice the size
 * of the old table (and rounded up to the nearest prime number).
 * The items in the old table are inserted into the new table by calling
 * the insert function, calling the function multiple times for words that
 * have a frequency more than 1.
 * 
 * After insertitem function has finished inserting all of the items into the
 * table the sort function is called, which sorts the table by frequency, 
 * and then each frequency group by the words alphabetical order.
 * The sort function uses qsort, which sorts the pointers to the nodes
 * in the vector. We use two compare functions, comparefreq and compare alpha
 * which compares two nodes by their frequency value and word order respectively.
 *
 * The tables are then exported to a .csv file which contains the frequency
 * of the words groups, the rank of the word groups, and the rank * frequency,
 * and a .wrd file which contains the average rank of the word group and the
 * frequency of the group, as well as the words in each group in alphabetical
 * order.
 *
 *
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      Compile using gcc, and the makefile provided. If using a different
 *      make file, be sure to include the following flag:
 *      -std=c++11
 *      The program contain findItem and deleteItem functions which
 *      are not called. These functions will only work properly
 *      if called before the sort function is called, as the sort function
 *      will destroy the hash values in the table.
 *      The output functions outputcsv and printtxt will crash
 *       if the delete functions are called
 *      before them.
 * 
 * @par Usage: 
   @verbatim  
   c:\> ./zipf textfile
   d:\> c:\bin\./zipf textfile
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug none
 * 
 * @todo none
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Nov  4, 2015  Added tokenize functions
   Nov  6, 2015  Fixed tokenize, add class declaraction and functions
   Nov  8, 2015  Begin hash function
   Nov  9, 2015  Fixed hash function
   NOv 12, 2015  Find and delete functions
   Nov 13, 2015  Resize function
   Nov 14, 2015  Add frequency and alphabetical sort functions
   Nov 15, 2015  Outputted .wrd and .csv files correctly
   NOv 16, 2015  Documented program
   @endverbatim
 *
 *****************************************************************************/




/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Checks for the correct number of arguements,
 * and creates a variable inputfile to store the name of the file we will be
 * opening. Creates an instance of myhash called h, an ifstream fin, and calls
 * the function readfile which tokenizes and calls functions to hash the words,
 * and insert them into the table. After readFile has finished, we remove the
 * file extention from the inputfile name and call the sort function, which'
 * sorts the list by frequency group and within each frequency group
 * by alphabetical order. Then outputcsv and printTxt are called which output
 * .wrd and .csv files with the frequency and rank of the words. 
 *
 * @param[in]    argc - number of arguements
 * @param[in]    argv - array holding arguements
 * 
 * @returns -1 - invalid usage
 * @returns 0 - program ran successfully
 *****************************************************************************/

// main() function to test tokenizers
int main( int argc, char *argv[] )
{

	clock_t tStart = clock();

	if ( argc < 2 )
    	{
        cerr << "Usage: zipf file.txt\n";
        return -1;
    	}

	string inputfile = argv[1];

	myhash h;
	ifstream fin;
	readFile(inputfile, fin, h);

	int period = inputfile.find('.');
	inputfile = inputfile.erase(period);

	h.sort();
	//h.printfrequency();
	h.outputcsv(inputfile);
	h.printTxt(inputfile);






	cout << "Runtime: " << ((double)(clock() - tStart)/CLOCKS_PER_SEC) * 1000 << " msec" << endl;
	
	return 0;
}

