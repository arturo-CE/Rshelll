#include "Parse_Redirection.hpp"

string Parse_Redirection::charToString(char **foo) {
	char *bar;
	string ret = "";
	int i = 0;

	while (foo[i] != NULL) {
		ret += foo[i];
		i++;
		if (foo[i] != NULL) {
			ret += ' ';
		}
	}
	return ret;
}

string Parse_Redirection::removeComments(string foo) {
	int scout = foo.find("#");
	if (scout == -1) {
		return foo;
	} 
  else {
		return foo.substr(0, scout);
	}
}

bool Parse_Redirection::isConnectingSymbol(char foo) {

	string key = "<>|";

	if (key.find(foo) != -1) {
		return true;
	} 
  else
		return false;
}

char** Parse_Redirection::cStringify(string foo) {
	if (foo.length() == 0) {
		return NULL;
	}

	char **ret = NULL;
	string token = "";
	vector < string > toks;
	istringstream iss;
	
  if (checkForSpaces(foo) == false) {
		ret = new char*[2];
		ret[0] = new char[foo.length() + 1];
		strcpy(ret[0], foo.substr(0, foo.length()).c_str());
		ret[0][foo.length() - 1] = '\0';
		ret[1] = NULL;
		return ret;
	}
  
	iss.str(foo);

	while (iss >> token) {
		toks.push_back(token);
	}
  
	ret = new char*[toks.size() + 1];
	for (int i = 0; i < toks.size(); i++) {
		ret[i] = new char[toks[i].length() + 1];
		strcpy(ret[i], toks[i].substr(0, toks[i].length()).c_str());
	}
  
	ret[toks.size()] = NULL;
	return ret;
}

bool Parse_Redirection::checkForSpaces(string foo) {
	for (int i = 0; i < foo.length(); i++) {
		if (foo[i] == ' ') {
			return true;
		}
	}
	return false;
}

string Parse_Redirection::trimEdgeSpaces(string foo) {
	string ret = foo;

	while (ret.front() == ' ') {
		ret = ret.substr(1);
	}
	while (ret.back() == ' ') {
		ret = ret.substr(0, ret.length() - 1);
	}

	return ret;
}

string Parse_Redirection::getFirstWord(string foo){
	string key = "<>|";

	for(int i = 0; i < foo.length(); i++){
		if(key.find(foo[i]) != -1){
			return foo.substr(0,i-1);
		}
	}
	return foo;
}

stack<pair<char, string> > Parse_Redirection::getCommands(string foo) {
	//foo = removeComments(foo);
	stack < pair<char, string> > commands;
	char key = ' ';
	string commandText = "";

	if (foo.length() == 0) {
		return stack<pair<char, string> >();
	}
	//hit from the back because each command dependant on the previous symbol.
	for (int i = foo.size() - 1; i >= 0; i--) {

		if (isConnectingSymbol(foo[i])) {

			commandText = trimEdgeSpaces(commandText);

			switch (foo[i]) {
				case '<':
					//mark the |, and subtract 1 for the extra symbol

					commands.push(make_pair(foo[i], commandText));
					break;

				case '>':
					//mark the and, and subtract 1 for the extra symbol
					if (foo[i - 1] == '>') {
						commands.push(make_pair('2', commandText));
						i--;
					} else {
						commands.push(make_pair(foo[i], commandText));

					}
					break;

				case '|':
					//mark the ;
					commands.push(make_pair(foo[i], commandText));
					break;

				default:

					break;
			}
			commandText = "";

			continue;
		}
		commandText = foo[i] + commandText;
	}
	if (commandText.length() > 1) {
		commandText = trimEdgeSpaces(commandText);
		commands.push(make_pair(';', commandText));
	}
	return commands;
}
