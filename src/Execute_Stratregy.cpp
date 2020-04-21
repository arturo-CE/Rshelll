#include "Execute_Strategy.hpp"

bool Execute_Strategy::executeTest(){
    /*Declare struct*/
    struct stat rightarg;
    /* Makes sure it exists or else return false no matter what*/
    char** args = foo->getArg();
    bool err = false;
    //const char* leftarg = &args[2];
    
	  if(stat(args[2],&rightarg) != -1){
	
		/*Flags*/
	
		    if(string(args[1]) == "-f"){
			      if(S_ISREG(rightarg.st_mode) == true){
                // already set to true
                cout << "(True)" << endl;
                return true;
             }	
             else{
                foo->setCommandSucceeded(err);
                cout << "(False)" << endl;
				        return false;
             }			
			  }
		
		   else if (string(args[1]) == "-d"){
			    if(S_ISDIR(rightarg.st_mode) == true){
				      cout << "(True)" << endl;
				      return true;
			    }
			    else{
				    foo->setCommandSucceeded(err);
				    cout << "(False)" << endl;
				    return false;
			    }
		  }
	
		  else if(string(args[1]) == "-e"){
			    cout << "(True)" << endl;
			    return true;
		  }

		  else{	/*any  other flags*/
			    foo->setCommandSucceeded(err);
			    cout << "(False)" << endl;
			    return false;
		  }	
	  }
	else{ 
	    cout << "(False)" << endl;
      foo->setCommandSucceeded(err);
      return false;	
	}
}
