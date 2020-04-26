#include "Parse_Execvp.hpp"

List_Command* getCommands(string bar){

	stack< pair<char,string> > foo = pe.getCommandText(input);
	List_Command* lc = new List_Command();
	
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
				lc.add(new List_Command(str));
				break;
			case ';':
				rab = pe.cStringify(str);
				lc.add(new Semicolon_Command(rab));
				break;
			case '&':
				rab = pe.cStringify(str);
				lc.add(new And_Command(rab));
				break;
			case '|':
				rab = pe.cStringify(str);
				lc.add(new Or_Command(rab));
				break;
			case '#':
				return;
			default:
				cout << "reached default." << endl; 
				return;
		}
	}	
	return lc;
}

string Parse_Execvp::charToString(char** foo){
	char* bar;
	string ret = "";
	int i = 0;

	while(foo[i] != NULL){

		ret += foo[i];
		i++;
		if(foo[i] != NULL){
			ret += ' ';
		}
	}
	return ret;
}

string Parse_Execvp::removeComments(string foo){
	int scout = foo.find("#");
	if(scout == -1){
		return foo;
	}
	else{
		return foo.substr(0,scout);
	}	
}

stack< pair<char,string> > Parse_Execvp::getCommandText(string foo){
	foo = removeComments(foo);
	stack< pair<char,string> > commands;
	char key = ' ';
	string commandText = "";
	bool ignoreSymbols = false;
	string lc = "";
	int pCount = 0;
	
	if(foo.length() == 0){return stack <pair<char,string> >();}
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
					if(pCount < 0){
						return stack< pair<char,string> >();
					}
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
				lc = trimEdgeSpaces(lc);
				commands.push( make_pair('(', lc) );
				lc = commandText = "";
				if(foo[i] == '&' || foo[i] == '|'){
					i--;
				}
				continue;
			}

			if(commandText.find("test") != -1 && commandText[4] == ' ' && commandText.find("-") == -1){
				commandText = convertTestString(commandText);
			}
			if(foo[i] == '|' && foo[i-1] == ' '){goto JUMP;}
			commandText = trimEdgeSpaces(commandText);

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
		if(commandText.find("test ") != -1 && commandText[4] == ' ' && commandText.find("-") == -1){                                        commandText = convertTestString(commandText);                                             }
		if(lc != ""){
			lc = trimEdgeSpaces(lc);
			commands.push( make_pair('(', lc) );
		}
		else{
			commandText = trimEdgeSpaces(commandText);
			commands.push( make_pair(';', commandText) );
		}
	}
	if(pCount != 0){
		return stack< pair<char,string> >();
	}
	return commands;
}

bool Parse_Execvp::isSurroundingSymbol(char foo){
	string key = "\"()[]";

	if(key.find(foo) != -1){

		return true;
	}
	else return false;
}
bool Parse_Execvp::isConnectingSymbol(char foo){

	string key = "#;&|";

	if(key.find(foo) != -1){

		return true;
	}
	else return false;
}

char** Parse_Execvp::cStringify(string foo){
	if(foo.length() == 0){return NULL;}


	char** ret = NULL;
	string token = "";
	vector<string> toks;
	istringstream iss;
	if(checkForSpaces(foo) == false){
		ret = new char*[2];
		ret[0] = new char[foo.length()+1];
		strcpy(ret[0], foo.substr(0,foo.length()).c_str());
		ret[0][foo.length()-1] = '\0';
		ret[1] = NULL;
		return ret;
	}
	iss.str(foo);

	while(iss >> token){
		toks.push_back(token);
	}
	ret = new char*[toks.size()+1];
	for(int i = 0; i < toks.size(); i++){
		ret[i] = new char[toks[i].length()+1];
		strcpy(ret[i], toks[i].substr(0,toks[i].length()).c_str());

	}
	ret[toks.size()] = NULL;

	return ret;
}
bool Parse_Execvp::checkForSpaces(string foo){
	for(int i = 0; i < foo.length(); i++){
		if(foo[i] == ' '){
			return true;
		}

	}
	return false;
}

string Parse_Execvp::convertTestString(string foo){
	if(foo.length() == 0){return foo;}

	istringstream iss(foo);
	string token;
	vector<string> toks;
	string ret = "test ";
	while(iss >> token){
		toks.push_back(token);
	
	}	
	if(toks.size() == 3){
		return foo;
	}

	if(toks.size() == 1){
		return "test -e " + foo;
	}

	if(toks.size() == 2){
		
		if(toks[0].find("test") != -1){
			ret += "-e " + toks[1];
		}
		else{
			ret += toks[0];
			ret += ' ' + toks[1];

		} 
	}		
	return ret;
}	

string Parse_Execvp::trimEdgeSpaces(string foo){
	string ret = foo;
	
	while(ret.front() == ' '){
		ret = ret.substr(1);
	}
	while(ret.back() == ' '){
		ret = ret.substr(0, ret.length()-1);
	}		
		
	return ret;
}

bool Parse_Execvp::isRedirection(string foo){

	int scout = -1;
	scout = foo.find("<");
	if(scout != -1 && foo[scout] != foo.back()){
		if(foo[scout+1] != '<'){
			return true;
		}
	}

	scout = foo.find("|");
	if(scout != -1 && foo[scout] != foo.back()){
		return true;
	}

	scout = foo.find(">");
	if(scout != -1 && foo[scout] != foo.back()){
		if(foo[scout+2] != '>'){
			return true;
		}
	}

	return false;

}
