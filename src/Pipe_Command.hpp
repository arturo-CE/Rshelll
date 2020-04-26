#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "Redirection_Command.hpp"
#include "Parse_Redirection.hpp"

using namespace std;

class Pipe_Command : public Redirection_Command{

	private:
		char* arg;
		int* p;
    
	public:
		Pipe_Command();
		Pipe_Command(char* foo);
		~Pipe_Command();
		bool execute(Redirection_Command* , int*);
		char* getArg();
};
