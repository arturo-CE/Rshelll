#include "Dup_Command_Left.hpp"

Dup_Command_Left::Dup_Command_Left(char* foo){
	this->arg = foo;

}

bool Dup_Command_Left::execute(Redirection_Command* foo, int*bar){
	pid_t pid, wait_pid;
		int status;
		const int SIZE = 100;
		Parse_Execvp pe;

		string temp = "", temp2 = "";
		char* ptr;
		char** cmd;
		int check;

		pid = fork();
			if(pid == -1){
				perror("fork failed.");
				//commandSuccess = false;
				exit(EXIT_FAILURE);
			}
			else if(pid == 0){

				temp = string(foo->getArg());
				temp2 = string(this->arg);

				cmd = pe.cStringify(temp + ' ' + temp2 );

				check = execvp(cmd[0], cmd);
				if(check < 0){
					perror("execvp failed.");
					return false;
				}

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
		return true;
}
