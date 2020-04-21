#pragma once
#include <iostream>
#include "Base_Command.hpp"
#include <string.h>
using namespace std;

class And_Command : public Base_Command{
	private:
		char** arg;
		bool commandSuccess;
	public:
		And_Command(char**);
		And_Command();
		virtual ~And_Command();

		char** getArg();
		void execute(Base_Command*);
		void add(Base_Command*);
		bool commandSucceeded(){return commandSuccess;}
		bool setCommandSucceeded(bool foo){commandSuccess = foo;} 
};
