#include "Dup_Command_Right2.hpp"

Dup_Command_Right2::Dup_Command_Right2(char* foo){
	this->arg = foo;

}

bool Dup_Command_Right2::execute(Redirection_Command* foo, int*bar){
	pid_t pid, wait_pid;
	int status;
    
	pid = fork();
	if(pid == -1){
	    perror("fork failed.");
		  //commandSuccess = false;
		  exit(EXIT_FAILURE);
	}
	else if(pid == 0){
  
	    int fd = open(getArg(),O_CREAT|O_WRONLY|O_TRUNC, 0644);
	    if(fd < 0){perror("Cannot open file."); return false;}
	    
      string line = "";
			int cd = dup(fd);
		  if(cd < 0){perror("Dup failed."); return false;}

		  ifstream ifs( foo->getArg() );

			while(ifs){
			    getline(ifs, line);
					write(fd, line.c_str(), line.length());
			}
		  close(cd);
			close(fd);
			ifs.close();
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
