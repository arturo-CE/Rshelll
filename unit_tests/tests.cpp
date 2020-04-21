#include "gtest/gtest.h"
#include "../src/Base_Command.hpp"
#include "../src/And_Command.hpp"
#include "../src/Execvp_Shell.hpp"
#include "../src/List_Command.hpp"
#include "../src/Or_Command.hpp"
#include "../src/Parse_Execvp.hpp"
#include "../src/Semicolon_Command.hpp"
#include "../src/Dup_Command_Left.hpp"
#include "../src/Dup_Command_Right.hpp"
#include "../src/Dup_Command_Right2.hpp"
#include "../src/Dup_Command_Left.hpp"
#include "../src/Dup_Command_Right.hpp"
#include "../src/Dup_Command_Right2.hpp"
#include "../src/Execute_Strategy.hpp"
//#include "../src/Execvp_Parse.hpp"
#include "../src/Parse_Redirection.hpp"
#include "../src/Pipe_Command.hpp"
#include "../src/Redirection_Command.hpp"
#include "../src/Redirection_Command_Base.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stack>
#include <utility>
using namespace std;

TEST(List_Command, simple_add){ // tests constructor

        List_Command lc;
        lc.add(new Semicolon_Command());
        lc.add(new Or_Command());
        lc.add(new And_Command());
        lc.add(new List_Command());
        EXPECT_EQ(lc.getSize(), 4);
}

TEST(Parse_Execvp, single_parse){

        string singleCommand = "ls";

        Parse_Execvp pe;

        stack< pair<char,string> > foo;
        foo = pe.getCommands(singleCommand);

        EXPECT_EQ(';', foo.top().first);
        EXPECT_EQ("ls", foo.top().second);


}

TEST(Parse_Execvp, single2_parse){

        string twoCommand = "ls -all";
        Parse_Execvp pe;
      stack< pair<char,string> > foo = pe.getCommands(twoCommand);

        EXPECT_EQ(';', foo.top().first);
        EXPECT_EQ("ls -all", foo.top().second);
}

TEST(Parse_Execvp, double_parse){

        string doubleCommand = "ls -all && echo";
        Parse_Execvp pe;
        stack< pair<char,string> > foo = pe.getCommands(doubleCommand);

        EXPECT_EQ(';', foo.top().first);
        EXPECT_EQ("ls -all", foo.top().second);

        foo.pop();

        EXPECT_EQ('&', foo.top().first);
        EXPECT_EQ("echo", foo.top().second);
}

TEST(Parse_Execvp, triple_parse){

        string tripleCommand = "ls -all && echo hello || git pull";
        Parse_Execvp pe;
        stack< pair<char,string> > foo = pe.getCommands(tripleCommand);

        EXPECT_EQ(';', foo.top().first);
        EXPECT_EQ("ls -all", foo.top().second);

        foo.pop();

        EXPECT_EQ('&', foo.top().first);
        EXPECT_EQ("echo hello", foo.top().second);

        foo.pop();

        EXPECT_EQ('|', foo.top().first);
        EXPECT_EQ("git pull", foo.top().second);

}

TEST(Parse_Execvp, perenth_parse){

        string perenthCommand = "(echo a && echo b) && (echo c && echo d)";
        Parse_Execvp pe;
        stack< pair<char,string> > foo = pe.getCommands(perenthCommand);

        EXPECT_EQ('(', foo.top().first);
        EXPECT_EQ("echo a && echo b", foo.top().second);

        foo.pop();

        EXPECT_EQ('(', foo.top().first);
        EXPECT_EQ("&echo c && echo d", foo.top().second);

}

TEST(Parse_Execvp, nested_perenth_parse){

        string nestedCommand = "(echo a && (echo b || echo c) ) && echo d";
        Parse_Execvp pe;
        stack< pair<char,string> > foo = pe.getCommands(nestedCommand);

        EXPECT_EQ('(', foo.top().first);
        EXPECT_EQ("echo a && (echo b || echo c)", foo.top().second);
}

TEST( Test_Command, e_flag_true){

        string test_command = "test -e src/main.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());


}
TEST( Test_Command, e_flag_true2){

        string test_command = "test -e integration_tests/exit_command_tests.sh";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());


}

TEST( Test_Command, e_flag_true3){

        string test_command = "test -e prototype/execute.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}

TEST( Test_Command, e_flag_false1){

        string test_command = "test -e src/main4134124.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


}
TEST( Test_Command, e_flag_false2){

        string test_command = "test -e integration_tests/exit124341_command_tests.sh";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


}

TEST( Test_Command, e_flag_false3){

        string test_command = "test -e prototypes/execute1231.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());

}

TEST( Test_Command, d_flag_true){

        string test_command = "test -d src";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());


}
TEST( Test_Command, d_flag_true2){

        string test_command = "test -d integration_tests";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());


}

TEST( Test_Command, d_flag_true3){

        string test_command = "test -d prototype";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}

TEST( Test_Command, d_flag_false1){

        string test_command = "test -d src1231";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


}
TEST( Test_Command, d_flag_false2){

        string test_command = "test -d integra";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


}

TEST( Test_Command, d_flag_false3){

        string test_command = "test -d prototypess";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());

}

TEST( Test_Command, f_flag_true){

        string test_command = "test -f src/And_Command.hpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());


}
TEST( Test_Command, f_flag_true2){


        string test_command = "test -f integration_tests/precedence_tests.sh";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());


}

TEST( Test_Command, f_flag_true3){

        string test_command = "test -f prototype/getCommands.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}
TEST( Test_Command, f_flag_false1){

        string test_command = "test -f src";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


}
TEST( Test_Command, f_flag_false2){

        string test_command = "test -f integraion_tests";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


}

TEST( Test_Command, f_flag_false3){

        string test_command = "test -f prototype";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());


TEST( Test_Command , full_paths){


        string test_command = "test -e ../assignment-patrick_art/src/main.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}
TEST( Test_Command , full_paths2){


        string test_command = "test -f ../assignment-patrick_art/src/main.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}

TEST( Test_Command , full_paths3){


        string test_command = "test -d ../assignment-patrick_art/src/main.cpp";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());

}
TEST( Test_Command , full_paths4){


        string test_command = "test -d ../assignment-patrick_art/src";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}

TEST( Test_Command , full_paths5){


        string test_command = "test -f ../assignment-patrick_art/src/";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());

}
TEST( Test_Command , full_paths6){


        string test_command = "test -e ../assignment-patrick_art";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}

TEST( Test_Command , full_paths7){


        string test_command = "test -d ../assignment-patrick_art";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(true, sc->executeTest());

}
TEST( Test_Command , full_paths8){


        string test_command = "test -f ../assignment-patrick_art";
        Parse_Execvp pe;
        char** bar = pe.cStringify(test_command);
        Semicolon_Command* passin = new Semicolon_Command(bar);
        Execute_Strategy* sc = new Execute_Strategy(passin);

        EXPECT_EQ(false, sc->executeTest());

}


TEST(Dup_right, Construction){
        char* testvalue = "cat < names.txt";

        Dup_Command_Right* con = new Dup_Command_Right(testvalue);

        bool succ = false;

        if(con->getArg() != nullptr){
                succ = true;
        }

        EXPECT_EQ(true, succ);

}
TEST(Dup_left, Construction){
        char* testvalue = "cat < names.txt";

        Dup_Command_Left* con = new Dup_Command_Left(testvalue);

        bool succ = false;

        if(con->getArg() != nullptr){
                succ = true;
        }

        EXPECT_EQ(true, succ);

}

TEST(Dup_right2, Construction){
        char* testvalue = "cat < names.txt";

        Dup_Command_Right2* con = new Dup_Command_Right2(testvalue);

        bool succ = false;

        if(con->getArg() != nullptr){
                succ = true;
        }

        EXPECT_EQ(true, succ);

}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
