#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector> 
#include <ctype.h>
#include <stack>
#include <sstream>
using namespace std;

class Execvp_Parse : public Base_Parse{
	public:
	
		List_Command* getListCommand(string);
		list<Base_Command*> getCommands(string);
		
	protected:
		char** cStringify(string);
		string charToString(char**);
		vector<char**> getArgs();
		stack< pair<char,string> > parse(string);
		bool isConnectingSymbol(char);
		bool isSurroundingSymbol(char);
		bool checkForSpaces(string);
		string removeComments(string);
		string convertTestString(string);
		string trimEdgeSpaces(string);
		bool isRedirection(string);
};

