/**************************************************************************//**
 * @file
 *****************************************************************************/

#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "hash.h"

using namespace std;

/// valid characters used to find words with the tokenize function
#define VALID "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"


int comparefreq(const void* a, const void* b);
int comparealpha(const void* a, const void* b);
void tokenize2( string& str, vector<string>& tokens, const string& valid);
int readFile(string inputfile, ifstream & fin, myhash & h);


#endif
