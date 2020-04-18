CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)
	ADD_EXECUTABLE(rshell
			src/main.cpp
			src/And_Command.cpp
			src/Or_Command.cpp
			src/Semicolon_Command.cpp
			src/Parse_Execvp.cpp
			src/List_Command.cpp
			src/Execvp_Shell.cpp
			src/Execute_Strategy.cpp
			src/Parse_Redirection.cpp
			src/Dup_Command_Right.cpp
			src/Dup_Command_Right2.cpp
			src/Dup_Command_Left.cpp
			src/Redirection_Command_Base.cpp
			src/Pipe_Command.cpp
		      )

	ADD_EXECUTABLE(test
			unit_tests/tests.cpp
			src/And_Command.cpp
			src/Or_Command.cpp
			src/Semicolon_Command.cpp
			src/Parse_Execvp.cpp
			src/List_Command.cpp
			src/Execvp_Shell.cpp
			src/Execute_Strategy.cpp
			src/Parse_Redirection.cpp
			src/Dup_Command_Right.cpp
			src/Dup_Command_Right2.cpp
			src/Dup_Command_Left.cpp
			src/Redirection_Command_Base.cpp
			src/Pipe_Command.cpp
		      )
TARGET_LINK_LIBRARIES(test gtest)

TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
