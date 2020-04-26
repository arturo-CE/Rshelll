#include "List_Command.hpp"

List_Command::List_Command(char** bar){
	if(bar == NULL || strlen(bar[0]) < 2){return;}

	string exe = "rshell";
	Parse_Execvp pe;	
	commandSuccess = true;
	arg = bar;
       	
	string temp = pe.charToString(bar);
	
	int scout = temp.find(exe);
	temp = temp.substr(exe.length() + scout + 1);  
	char c;
        string str;
        char** rab;
	stack< pair<char,string> > foo = pe.getCommands(temp); 

	//for(int i = 0; i < foo.size(); i++){
	//	cout << foo.top().second << endl;
	//}        

	while(!foo.empty()){
                c = foo.top().first;
                str = foo.top().second;
		foo.pop();
                switch(c){
                        case '(':
                                add(new List_Command(str));
                                break;
                        case ';':
                                rab = pe.cStringify(str);
                                add(new Semicolon_Command(rab));
                                break;
                        case '&':
                                rab = pe.cStringify(str);
                                add(new And_Command(rab));
                                break;
                        case '|':
                                rab = pe.cStringify(str);
                                add(new Or_Command(rab));
                                break;
                        case '#':
                                return;
                        default:
                                return;
                }
        }
        return;
}

List_Command::List_Command(string input){
	if(input.length() < 2){return;}

	commandSuccess = true;
	Parse_Execvp pe;
	arg = pe.cStringify(input);
	if(pe.isConnectingSymbol(input[0]) ){
		symbol = input[0];
	}
	else symbol = ' ';


	stack< pair<char,string> > foo = pe.getCommands(input);
	
	//for(int i = 0; i < foo.size(); i++){
	//	cout << foo.top().first << " " << foo.top().second << endl;
	//}
  
	char c;
	string str;
	char** rab;
	while(!foo.empty()){
		c = foo.top().first;
		str = foo.top().second;
		foo.pop();
		switch(c){
			case '(':
				add(new List_Command(str));
				break;
			case ';':
				rab = pe.cStringify(str);
				add(new Semicolon_Command(rab));
				break;
			case '&':
				rab = pe.cStringify(str);
				add(new And_Command(rab));
				break;
			case '|':
				rab = pe.cStringify(str);
				add(new Or_Command(rab));
				break;
			case '#':
				return;
			default:
				cout << "reached default." << endl; 
				return;
		}
	}	
	return;
}

List_Command::~List_Command(){
	list<Base_Command*>::iterator it = commandList.begin();

	while(it != commandList.end()){
		delete *it;
		it++;
	}
	return;
}
char** List_Command::getArg(){
	return arg;
}

void List_Command::clearList(){
	list<Base_Command*>::iterator it = commandList.begin();

	while(it != commandList.end()){
		delete *it;
		it++;
	}
}

bool List_Command::isRedirection(char** foo){

	string key = "<>|";
	Parse_Execvp pe;

	string bar = pe.charToString(foo);
	for(int i = 0; i < bar.length(); i++){
		if(key.find(bar[i]) != -1){
			return true;
		}
	}

	return false;
}

void List_Command::execute(Base_Command* foo){
	//if( getArg()[0] == NULL || strlen( getArg()[0]) < 2){return;}
	list<Base_Command*>::iterator it = commandList.begin();
	Base_Command* ptr = foo;
	Execute_Strategy es;
	Parse_Execvp pe;
	string bar = "";
	Redirection_Command_Base *rcb;
	if(foo != NULL){
		if(foo->commandSucceeded() && symbol == '|'){
			clearList();
			return;
		}
		if(!foo->commandSucceeded() && symbol == '&'){
			clearList();
			return;
		}
	}

	while(it != commandList.end()){

		if( (*it)->getArg() != NULL && string( (*it)->getArg()[0] ).find("exit") != -1 && strlen((*it)->getArg()[0] ) == 4){
			exit(0);
		}

		else if( (*it)->getArg() != NULL && string((*it)->getArg()[0]).find("test") != -1 && strlen((*it)->getArg()[0] ) == 4){
			es = Execute_Strategy(*it);
			es.executeTest();
			
		}

		else if( isRedirection( (*it)->getArg() ) ){

			rcb = new Redirection_Command_Base( pe.charToString( (*it)->getArg() ),  this );
			rcb->execute(NULL,NULL);
		}

		else (*it)->execute(ptr);
		
		if( (*it)->commandSucceeded() == false){
			commandSuccess = false;
		}
		it++;
		if(it != commandList.end()){
			ptr = *it;
		}
	}

	return;
}

void List_Command::add(Base_Command* foo){
	commandList.push_back(foo);
	return;
}


bool List_Command::commandSucceeded(){
	return commandSuccess;
}

