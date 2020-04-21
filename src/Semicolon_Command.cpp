#include "Semicolon_Command.hpp"

Semicolon_Command::Semicolon_Command(char** foo){
	arg = foo;
	commandSuccess = true;	
	return;
}

Semicolon_Command::Semicolon_Command(){
	arg = NULL;
	commandSuccess = true;
	return;
}

char** Semicolon_Command::getArg(){
	return arg;
}

void Semicolon_Command::execute(Base_Command *foo){
	pid_t pid, wait_pid;
	int status;

	pid = fork();
	if(pid == -1){
		perror("fork failed.");
		commandSuccess = false;
		exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		execvp(arg[0],arg);
	}
  
	else{
		wait_pid = waitpid(pid,&status,WUNTRACED | WCONTINUED);
		if(wait_pid == -1){
			perror("wait_pid");
			exit(EXIT_FAILURE);
		}
		else{
			while(!WIFEXITED(status) && !WIFSIGNALED(status)){
				wait_pid = waitpid(pid,&status, WUNTRACED | WCONTINUED);
			
			}
		}
	}
	return;
}

void Semicolon_Command::add(Base_Command* foo){
	return;
}

