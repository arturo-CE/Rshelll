#pragma once
#include "Base_Command.hpp"
#include "List_Command.hpp"
#include "Semicolon_Command.hpp"
#include "And_Command.hpp"
#include "Or_Command.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Execvp_Shell{
private:
  Base_Command *head;
public:

  Execvp_Shell();
  Execvp_Shell(char**);
  virtual ~Execvp_Shell();
  void start();


protected:
  char* captureCommand();
};  
