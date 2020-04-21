#pragma once
#include <iostream>
#include "Base_Command.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

class Semicolon_Command : public Base_Command{
	private:
		char** arg;
		bool commandSuccess;
	public:
		Semicolon_Command(char** foo);
		Semicolon_Command();
		virtual ~Semicolon_Command();

		char** getArg();
		void execute(Base_Command*);
		void add(Base_Command*);
		bool commandSucceeded(){return commandSuccess;}
		bool setCommandSucceeded(bool foo){commandSuccess = foo;}
};
