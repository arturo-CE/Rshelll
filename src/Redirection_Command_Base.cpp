#include "Redirection_Command_Base.hpp"

Redirection_Command_Base::Redirection_Command_Base(string foo, Base_Command *bar){
	this-> base = bar;
	Parse_Redirection pr;
	stack< pair<char,string> > cmds = pr.getCommands(foo);
	this->arg = const_cast<char*>( pr.getFirstWord(foo).c_str() );
	cmds.pop();

	while(!cmds.empty()){

		switch(cmds.top().first){
		    case '<':
			    commands.push_back( new Dup_Command_Left( const_cast<char*>( cmds.top().second.c_str() ) ) );
			    break;

		    case '>':
			      commands.push_back( new Dup_Command_Right( const_cast<char*>( cmds.top().second.c_str() ) ) );
			      break;
            
		    case '2':
			      commands.push_back( new Dup_Command_Right2( const_cast<char*>( cmds.top().second.c_str() ) ) );
			      break;

		    case '|':
			      commands.push_back( new Pipe_Command( const_cast<char*>( cmds.top().second.c_str() ) ) );
			      break;
		}

		cmds.pop();
	}
}

bool Redirection_Command_Base::execute(Redirection_Command* foo, int*bar){
	list<Redirection_Command*>::iterator it = commands.begin();
	char* prevArg = this->arg;
	Redirection_Command* prev = this;
	int *p = new int[2];

	while(it != commands.end()){

		if((*it)->execute(prev,p) == false){
			return false;
	  }
	  prev = (*it);
	  it++;
  }
	return true;
}
