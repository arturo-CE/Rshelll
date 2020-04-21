#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <list>
#include <fstream>
#include "Base_Command.hpp"
#include "Parse_Redirection.hpp"
#include "Redirection_Command.hpp"
#include "Dup_Command_Left.hpp"
#include "Dup_Command_Right.hpp"
#include "Dup_Command_Right2.hpp"
#include "Pipe_Command.hpp"
using namespace std;


class Redirection_Command_Base : public Redirection_Command{
private:
	char* arg;
	list<Redirection_Command*> commands;
	Base_Command *base;

	int *p;

public:
	Redirection_Command_Base(){}
	Redirection_Command_Base(string foo, Base_Command*);
	char* getArg(){return this->arg;}
	bool execute(Redirection_Command*, int*);

};
