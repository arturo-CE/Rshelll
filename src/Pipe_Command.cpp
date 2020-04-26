#include "Pipe_Command.hpp"

Pipe_Command::Pipe_Command(char *foo) {
	this->arg = foo;

}

char* Pipe_Command::getArg() {
	return this->arg;
}

bool Pipe_Command::execute(Redirection_Command* foo, int*bar) {
	int SIZE = 100;
	Parse_Redirection pr;
	char buf[SIZE];

	int fd;
	pid_t pid, wait_pid;
	int status, chars;

	int p1[2];

	if (pipe(p1)) {
		perror("pipe failed.");
		return false;
	}
  pid = fork();
  
	if (pid == -1) {
		perror("fork failed.");
		return false;
		exit (EXIT_FAILURE);
	} 
  else if (pid == 0) {
		//child executes here
	} 
  else {
		wait_pid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
		if (wait_pid == -1) {
			perror("wait_pid");
			exit (EXIT_FAILURE);
		} 
    else {
			while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
				wait_pid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			}
		}
	}
	return true;
}
