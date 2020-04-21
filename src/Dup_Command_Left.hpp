#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "Redirection_Command.hpp"
#include "Parse_Execvp.hpp"
#include <fstream>
using namespace std;


class Dup_Command_Left : public Redirection_Command{

private:
	char* arg;
  
public:
	Dup_Command_Left(){}
	Dup_Command_Left(char* foo);
	~Dup_Command_Left();
	char* getArg(){return this->arg;}
	bool execute(Redirection_Command* foo, int*bar);

};
