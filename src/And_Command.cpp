#include "And_Command.hpp"
And_Command::And_Command(char** foo){
	arg = foo;
	commandSuccess = true;
	return;
}

And_Command::And_Command(){
	arg = NULL;
	commandSuccess = true;
	return;
}

And_Command::~And_Command(){
	return;
}

char** And_Command::getArg(){
	return arg;
}

void And_Command::execute(Base_Command* foo){

	pid_t pid,wait_pid;
	int status;
	if(foo->commandSucceeded()){
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
	}
	return;

}	
void And_Command::add(Base_Command* foo){
	return;
}
