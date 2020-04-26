#pragma once
#include <iostream>
#include "Execvp_Shell.hpp"
#include "Base_Command.hpp"
#include "And_Command.hpp"
#include "Execvp_Shell.hpp"
#include "List_Command.hpp"
#include "Or_Command.hpp"
#include "Parse_Execvp.hpp"
#include "Semicolon_Command.hpp"

using namespace std;

int main(int argv, char** argc){
	Execvp_Shell *es;
	if(argv == 1){
		es = new Execvp_Shell();
	}
	else{
		es = new Execvp_Shell(argc);
	}
	delete es;	
	return 0;
}
