#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <ctype.h>
#include <stack>
#include <sstream>
using namespace std;

class Parse_Redirection{
	public:
		char** cStringify(string);
		string charToString(char**);
		vector<char**> getArgs();
		stack< pair<char,string> > getCommands(string);
		bool isConnectingSymbol(char);
		bool isSurroundingSymbol(char);
		bool checkForSpaces(string);
		string removeComments(string foo);
		string convertTestString(string);
		string trimEdgeSpaces(string);
		string getFirstWord(string foo);
};
