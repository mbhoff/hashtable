/**************************************************************************//**
 * @file
 *****************************************************************************/
#include "hash.h"
#include "tokenize.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>

myhash::myhash()
{
	tableSize = 1009;
	table.resize(tableSize);
	
}

myhash::~myhash()
{
}


/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Opens a csv file to output the rank, frequency and
 * rank * frequency of each word group.
 *
 * @param[in]    inputfile - the file we will be writing to
 *
 * @returns true - csv outputed succesfully
 * @returns false - failed to output csv file
 * 
 *****************************************************************************/


bool myhash::outputcsv(string inputfile)
{

	ofstream fout;
	string outputfile = inputfile;
	
	outputfile.append(".csv");

	int startRank = 1;
	int endRank = 0;
	unsigned int pos = 0;
	int freq = 0;
	int count = 0;

	fout.open(outputfile, ios::out);

	    if (!fout)
	    {
		//if unable to open, print error message
		//and return 0
		cout << outputfile << " failed to open for writing" << endl;
		return 0;

	    }


	//output title, filename, total words, unique words, and data labels.
	fout << endl;
	fout << right << setw(17) << "Zipf\'s Law" << endl;
    	fout << right << setw(17) << "----------" << endl;
    	fout << right << setw(13) << "File: " << inputfile << endl;
    	fout << right << setw(31) <<
		 "Total number of words = " << totalWords << endl;
	fout << right << setw(34) <<
		 "Number of distinct words = " << uniqueElements
		 << endl << endl;

	fout << setw(11) << right << "rank"
		 << setw(11) << right << "freq"
		 << setw(11) << right << "rank*freq" << endl;

	fout << setw(11) << right << "----" 
		<< setw(11) << right << "----" 
		<< setw(11) << right << "---------" << endl;
	

	while (	pos < table.size()) //read til end of file
	{
		freq = table[pos].frequency; //sets current frequency
		
		while (freq == table[pos].frequency) //counts the same freq
		{
			count++;
			pos++;
		}
		
		endRank = startRank + count -1;
		pos = pos - count;
		

		
		fout<< setw(10) << right << fixed << setprecision(1) 
			<<(double)(startRank+endRank)/2 << ","
			 << setw(10) << right;
		fout<< freq << "," << setw(11) << right;
		fout << fixed << setprecision(1) <<
			 freq * ((double)(startRank+endRank)/2) <<endl;	

		pos = pos+count;
		startRank = endRank+1;
		endRank = 0;
		count = 0;
	}


	fout.close();
	return true;
}



/**************************************************************************//** 
 * @author Other team member
 * 
 * @par Description: 
 * This function prints the sorted table in a readable text format
 * 
 * @param[in]	fileName - the name of the file being outputted to      
 * 
 * @returns false - failed to open output file
 * @returns true - the function printed to the file successfully  
 * 
 *****************************************************************************/



bool myhash::printTxt(string fileName)
{
	int startRank = 1;
	int endRank = 0;
	unsigned int pos = 0;
	int freq = 0;
	int count = 0;
	ofstream tout;  //output file
	tout.open(fileName.append(".wrd"), ios::out);

	if(!tout)
	{
		cout <<"Text output file failed to open"<<endl;
		return false;
	}

	tout << "Zipf's Law\n----------\nFile: "<<fileName <<endl;
	tout << "Total number of words = "<< totalWords <<endl;
	tout << "Number of distinct words = "<< uniqueElements <<endl;
	tout << "Word Frequencies\t\t\tRanks\t\tAvg Rank" <<endl;
	tout << "----------------\t\t\t-----\t\t--------"<< std::left <<endl;

	while (	pos < table.size()) //read til end of file
	{
		freq = table[pos].frequency;  //sets current frequency
		
		while (freq == table[pos].frequency) //counts the same freq
		{
			count++;
			pos++;
		}
		
		endRank = startRank + count -1;
		pos = pos - count;
		
		tout << "Words occuring "<< setw(2) <<freq << setw(24) <<" times:";
	
		if (endRank == startRank)      //decides how to print the rank
			tout<< setw(18) << endRank;
		else
			tout<< startRank<< "-" << setw(16) << endRank;
		
		tout<<(double)(startRank+endRank)/2<<endl; //computes average rank

		
		int line = 0;

		for(unsigned int i = pos; i < (pos + count); i++)
		{
			line++;
			tout << setw(16) << table[i].word;
			if(line % 5 == 0)	//prints five words per line
			{
				tout<<endl;
				line = 0;
			}
		}
		if(line != 0) //doesnt print two new lines
		{
			tout<<endl;
		}		


		tout << endl;		

		pos = pos+count;
		startRank = endRank+1;
		endRank = 0;
		count = 0;
	}


	tout.close();
	return true;
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: 
 * This function sorts the hash table. The hash table is first sorted by
 * frequency in decending order using qsort. The hash table is then broken into
 * the words of the same frequency. Qsort is then used to sort the vector 
 * into alphabetical order.The process is repeated for all frequencies.
 * 
 * @returns true - The function sorted successfully
 * *****************************************************************************/


bool myhash::sort()
{
		//sorts the vector based on decending frequency
	qsort(((void *)&table[0]), tableSize, sizeof(node), comparefreq);
	

	vector<node> samefreq;
	int maxfreq = table[0].frequency;
	int count = 0;
	int i = 0;
	int start = 0;
	
	while (maxfreq != 0)  //continues alphabetical sort til empty
	{	
					//counts words with same frequency
		while ( maxfreq == table[i].frequency && maxfreq != 0)
		{
			count++;
			i++;
		}
		
			//sorts the vector alphabetically
		qsort(((void *)&table[start]), count, sizeof(node), comparealpha);

		start += count;
	
			//updates to the next frequency
		maxfreq = table[i].frequency;
	
		count = 0;
	
	}

	table.resize(uniqueElements);	//compresses vector

	return true;


}
/**************************************************************************//** 
 * @author Mark, Other team member
 *
 * @par Description: 
 * This function prints the word and frequency of the final vector
 * 
 * @returns 0 function printed successfully.
 * 
 *****************************************************************************/

int myhash::printfrequency()
{

	for(unsigned int i = 0; i < table.size(); i++)
	{	
		if (table[i].frequency != 0)
		{
			cout << table[i].word << endl;
			cout << table[i].frequency << endl;
		}
	}

	return 0;
}
/**************************************************************************//** 
 * @author Mark, Other team member
 * @par Description: 
 * This function is used to rehash the hash table. The hash table is expanded
 * to the next prime that is roughly double the current size. Then copying the
 * contents to a new vector. The new vector is traversed and the insert function
 * is called to move the contents to the original resized vector.
 * 
 * @returns true - function rehashed successfully
 * *****************************************************************************/

bool myhash::rehash()
{

	totalWords = 0;
	vector<node> oldtable;  //stores values in a temp vector
	table.swap(oldtable);
		
	int divisor = 2;
	int num = tableSize * 2; //doubles current table size

	while (divisor <= num/2) //find the next prime number
	{
		if (num % divisor == 0)
		{
			num++;
			divisor =2;
		}

		else
		{
			divisor++;
		}
	}

	
	tableSize = num; 
	table.resize(tableSize); //resizes original table

	cout << "Rehashing: Table size is now " << tableSize <<endl;

	uniqueElements = 0;
	for(unsigned int i = 0; i<oldtable.size(); i++) //reinserts each item
	{	
		if (oldtable[i].frequency != 0)
		{
				//reinserts all words of same frequency
			while( oldtable[i].frequency > 0)
			{
				insertItem(oldtable[i].word);
				oldtable[i].frequency --;
			}
		}
	}
	
	

	return true;
}
/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: 
 * This function inserts a word into the hash table. A position is generated
 * for the word and the word is inserted at that position or the next available
 * position. If the word is already in the list the frequency is incremented
 * 
 * @param[in]      item - the string being inserted in the hash table
 * 
 * @returns true - The item is successfully inserted in the table.
 * 
 *****************************************************************************/
bool myhash::insertItem(string item)
{
		//checks table size and rehashes if necessary
	if (uniqueElements >= .75 * tableSize)
	{
		rehash();
	}


	node temp;
	temp.word = item;
	temp.frequency = 1;

	unsigned int pos = 0;
		//computes a position to hash to
	for (unsigned int i = 0; i<item.length(); i++)
	{
		pos += item[i];
		pos *= 113;	
	}
	
	pos = pos * item.length();

	pos = pos * item[0];

	if (item.length() > 2 && item.length() < 4)
		pos = pos / item[1];

	
	if (item.length() > 4)
	{
		pos = pos * item[3];
	}

	
	pos = pos % tableSize;
	

		//linear probes to find an open spot	
	while (table[pos].frequency != 0)
	{
		if (table[pos].word == temp.word)
		{
			table[pos].frequency ++;
			totalWords++;
			return true;

		}
		
			//sends position to beginning of vector
		if (pos >= table.size()-1)
		{
			pos = -1;
		}
		
		pos++;
				
 	}
		
		//inserts in an empty spot in the vector
	if (table[pos].frequency == 0)
	{

		table[pos] = temp;
		uniqueElements++;
		totalWords++;
	}

	return true;
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: 
 * This function searches the hash table for a value. The hash function is used
 * to generate a position in the table to check. If the word isnt at the position
 * the table is traversed until the word is found or an empty space is encountered
 * 
 * @param[in]      item - the word being searched for
 * 
 * @returns pos - the position the word is at in the table
 * @returns -1  - the word is not in the table
 * 
 *****************************************************************************/
int myhash::findItem(string item)
{


	unsigned int pos = 0;

		//uses hash function to find initial position to check	
	for (unsigned int i = 0; i<item.length(); i++)
	{
		pos += item[i];
		pos *= 113;
	}
	
	pos = pos * item.length();

	pos = pos * item[0];

	if (item.length() > 2 && item.length() < 4)
		pos = pos / item[1];

	if (item.length() > 4)
	{
		pos = pos * item[3];
	}

	pos = pos % tableSize;

		//linear probes until item is found or an open space is reached
	while(table[pos].word != item)
	{
		if( table[pos].frequency == 0 )
		{
			return -1;
		}

		pos++;
		
		if (pos >= table.size()-1)
		{
			pos = 0;
		}
	}

	return pos;
}
/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: 
 * This function searches for a word and deletes all instances of it
 * 
 * @param[in]	value - the word being deleted.      
 * 
 * @returns false - the word is not in the table
 * @returns true  - the word has been deleted
 * *****************************************************************************/
bool myhash::deleteItem(string value)
{		
		//finds position of value
	int pos = findItem(value);
		//returns is value isnt in the vector
	if (pos == -1)
	{
		return false;
	}

		//if found deletes all instances of value
	if (table[pos].frequency > 0)
	{
		table[pos].frequency = 0;
		table[pos].word = "";
	}	
		
	return true;

}
