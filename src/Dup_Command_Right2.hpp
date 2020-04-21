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
#include <fstream>
#include "Redirection_Command.hpp"
using namespace std;

class Dup_Command_Right2 : public Redirection_Command{

private:
	char* arg;

public:
	Dup_Command_Right2(){}
	Dup_Command_Right2(char* foo);
	~Dup_Command_Right2();
	char* getArg(){return this->arg;}
	bool execute(Redirection_Command* , int*);


};
