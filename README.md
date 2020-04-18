# Software Construction: Programming Project
**Project Information:**<br/>

Fall 2019<br/>
- Arturo Alvarado 
- Patrick Fenn 

## **Introduction:**<br/>

This project's main goal is to develop a command shell. This command shell will be able to accomplish the following:<br/>
1. Print a prompt.
1. Capturing user input.
1. Execute commands based on the connecting symbols. 

Printing the prompt and capturing the user input can be grouped together since capturing an input is dependent on displaying the user a prompt. The inputs will be captured using bash scripts that call our classes and pass along the user input. In order to execute the commands passed, the string will be parsed into Command objects and placed into a list provided by the STL. The list will then be passed to the execute function in the Execp_Shell class which will have a List_Command serving as the head of the command chain. The Execvp_Shell will then call on the List_Command to use Parse_Execvp to parse the commands. List_Command will then use the execute(Base_Command*) function to execute the commands that it has in its commandList. To accomplish this, the List_Command will use the fork,execvp, and waitpid functions to execute the command. We will use the composite design pattern to code the shell.

## **Diagram:**<br/>

![image](https://user-images.githubusercontent.com/61763318/79528241-531cec00-801e-11ea-8a40-006eb3449bfc.png)

## **Classes:**<br/> 
  * **Execvp_Shell** : Responsible for displaying the '$' prompt and capturing the user's input. It will then utilize the **Parse_Execvp** class to parse the input into char** that can be fed into the execvp function. It owns one **List_Command** object which serves as the head of the command chain.
    * **Parse_Execvp** : Implements a specific strategy to parse the data.
  * **Base_Command** : Abstract base class for the various types of commands that the Execvp suite will be interacting with.
    * **And_Command** : Represents the commands that follow the '&' connector. This class will need a bool type parameter that states whether the command successfully executed.
    * **Or_Command** : Represents the commands that follow the '|' connector. This class will need a bool type parameterthat states whether the command successfully executed.
    * **Semicolon_Command** : Represents the commands that follow the ';' connector. This class will execute regardless if the previous command successfully executed or not. Additionally can be used for the first command that is parsed.
    * **List_Command** : Represents a list of commands, which can be made up of **And_Command**, **Or_Command**, **Semicolon_Commmand**, and possibly other **List_Commands**. It is responsible for iterating through its' command chain and calling their respective execute() functions.It is also responsible for parsing user inputs into appropriate Base Commands and Redirection Commands._
  * **Execute_Strategy** : Takes a Base_Command pointer and executes a specific strategy for the TEST commands. Which are not executed by execvp and need to be processed differently.
     * **executeTest** : Function will have a return type bool. It will get arguments from its private member variable. It will contain a char** of size 3. It will check arg[1] for intended flags and unintended flags. It will check arg[2] to make sure desired path exists.
  * **Parse_Redirection** : Will implement a parse "getCommands" that that takes in a string and handle input and output redirection.
  * **Redirection_Command**: Sets the interface for the functions that will handle the redirection and piping. It will declare a pure virtual function "execute" that each child must implement based on its logic.
     * **Dup_Command_Left** : Class will handle input redirection. Changing the file descriptor to read from a desired file instead of stdin. 
     * **Dup_Command_Right** : Class will handle output redirection. Changing the file descriptor to write to desired file instead of stdout. Function changes the contents of the desired file.
     * **Dup_Command_Right2** : Class will also handle output redirection. Changing the file descriptor to write to desired file instead of stdout.Function appends output to the end of the file instead of replacing its contents. 	
     * **Pipe_Command** : Class will be able to take the outputs of one program and pass it in as an input to another program. Must be able to handle multiple pipe calls.
     * **Redirection_Command_Base** : Class will use functionality from the Parse_Redirection class and have its own execute function of type bool.

## **Prototypes/Research:**<br/>
<br/>

<addr>

	//Owned by the Parse_Execvp class.
	
	stack< pair<char,string> > getCommands(string foo){

	stack< pair<char,string> > commands;
	char key = ' ';
	string commandText = "";
	bool ignoreSymbols = false;
	string lc = "";
	int pCount = 0;

	//hit from the back because each command dependant on the previous symbol.
	for(int i = foo.size() -1; i >= 0; i--){
	
		if(isSurroundingSymbol(foo[i])){
			switch(foo[i]){
				case ')':
					pCount++;
					if(pCount > 1){
						commandText = foo[i] + commandText;
					}
					ignoreSymbols = true;
					key = '(';
					break;

				case '(':
					pCount--;
					if(pCount == 0){
						ignoreSymbols = false;
						lc = commandText;
						key = ' ';
					}
					else{
						commandText = foo[i] + commandText;
					}
					lc = commandText;
					break;

				case '\"':
					if(key == ' '){
						ignoreSymbols = true;
						key = '\"';
					}
					else{
						ignoreSymbols = false;
						key = ' ';
					}
					break;

				case ']': 
					ignoreSymbols = true;
					key = '[';
					break;

				case '[':
					ignoreSymbols = false;
					key = ' ';
					commandText = convertTestString(commandText);
					break;
					
				default:
					break;
			}

			continue;
		}
		if(!ignoreSymbols && isConnectingSymbol(foo[i])){
			if(lc != ""){
			
				lc = foo[i] + lc;
				commands.push( make_pair('(', lc) );
				lc = commandText = "";
				if(foo[i] == '&' || foo[i] == '|'){
					i--;
				}
				continue;
			}
			switch(foo[i]){
				case '|':
					//mark the |, and subtract 1 for the extra symbol

					commands.push( make_pair(foo[i], commandText) );
					i--;
					break;

				case '&':
					//mark the and, and subtract 1 for the extra symbol
					commands.push( make_pair(foo[i], commandText) );
					i--;
					break;

				case ';':
					//mark the ;
					commands.push( make_pair(foo[i], commandText) );
					break;
					
				default:
					break;
			}
			commandText = "";
			continue;
		}
		JUMP:		
		commandText = foo[i] + commandText;
	}
	if(commandText.length() > 1){
		if(lc != ""){
			commands.push( make_pair('(', lc) );
		}
		else commands.push( make_pair(';', commandText) );
	}
	return commands;
	}
	
<addr/>

This function parses a command string into a stack of pairs, each pair made up of the associated connecting symbol and its command string. Starting from the end of the string was essential because each command relies on the previous connecting symbol. Two separate switch statements were utilized to discern between connecting symbols ";&|" and surrounding symbols "()"[]". The resulting stack's objects are then passed into the cStringify() to convert it into something compatible with execvp. One difficulty was tracking the nested parenthesis, which was accomplished by using a counter.

<br/>

---

<addr>
	
	//Owned by each object that inherits from Base_Command.

	void execute(Base_Command *foo){
	
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

<addr/>

Here is a simple function that uses **fork()** to create a child process. Then it uses **execvp()** to exectute a command on the child process. **Waitpid()** is used to check if the command executed successfully. Re-using the above logic, we can create further logic to determine when to call the next command based on the connecting symbols and the use of waitpid(). 

<br/>

---
<addr>	
	
	bool executeTest(){
		char** command = foo->getArgs();
		
		struct stat rightarg;

		if(stat(command[2], &rightarg) == -1 ){
			cout << "(False)" << endl;
			return false;
		}
		else if(command[1] == "d"){
			if(S_ISDIR(rightarg.st_mode) == true){
				cout << "(True)" << endl;
				return true;
			}
			else{
				cout << "(False)" << endl;
				return false;
			}
		else{
			cout << "(False)" << endl;
			return false;		
		}
	}

<addr/>

Here is a simple function that uses the **stat()** function as well as the **S_ISDIR** function. It first checks to see if the path is valid using the stat() command. If it does not return a -1 the command will then be checked using the S_ISDIR function to see if it is an existing directory. Using the above logic, we can extend the flag check to include a check for the "-f" and "-e" flags. We will be adding another function **S_ISREG** that will allow us to check to see if it a regular file. 


