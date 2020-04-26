#include "Execvp_Shell.hpp"
Execvp_Shell::Execvp_Shell(char** argv){

	head = new List_Command(argv);
	head->execute(NULL);
	delete head;
	return;
}

Execvp_Shell::Execvp_Shell(){

	while(1){	
		string input = string(captureCommand());
		head = new List_Command(input);
		head->execute(NULL);	
		delete head;
	}
	return;
}  

char* Execvp_Shell::captureCommand(){
	const int MAX_LIMIT = 300;
	char* str = new char[MAX_LIMIT];

	cout << "$ " ;
	fgets(str, MAX_LIMIT, stdin);

	return str;
}

void Execvp_Shell::start(){
	return;
}


