#pragma once
#include <iostream>
#include <list>
#include "Base_Command.hpp"
#include "Semicolon_Command.hpp"
#include "And_Command.hpp"
#include "Or_Command.hpp"
#include "Parse_Execvp.hpp"
#include "Execute_Strategy.hpp"
#include "Redirection_Command_Base.hpp"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stack>
using namespace std;
class List_Command : public Base_Command{
	private:
		char** arg;
		list<Base_Command*> commandList;
		bool commandSuccess;
		char symbol;
	public:
		List_Command(){}
		List_Command(char**);
		List_Command(string);
		virtual ~List_Command();

		char** getArg();			//returns unparsed argv 
		void add(Base_Command* );
		void execute(Base_Command*);
		bool commandSucceeded();
		int getSize(){return commandList.size();}
		list<Base_Command*> getList(){return commandList;}
		bool setCommandSucceeded(bool foo){commandSuccess = foo;}
		char getSymbol(){return symbol;}
		void clearList();
		void setSymbol(char foo){symbol = foo;}
		bool isRedirection(char** foo);
};
