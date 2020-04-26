#pragma once
#include <iostream>
#include "Base_Command.hpp"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
using namespace std;

class Or_Command : public Base_Command{
	private:
		char** arg;
		bool commandSuccess;
	public:
		Or_Command(char**);
		Or_Command();
		virtual ~Or_Command();

		char** getArg();
		void execute(Base_Command*);
		void add(Base_Command*);
		bool commandSucceeded(){return commandSuccess;}
		bool setCommandSucceeded(bool foo){commandSuccess = foo;} 
};
