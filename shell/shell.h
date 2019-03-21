/******************************************************************************************
*Name: Ribash Sharma                                                                     *
*Class: Operating System                                                                  *
*Instructor: Chao Zhao                                                                    *
*Description: The program is for a shell simulator which communicates with kernel to run  *
*             commands                                                                    *
*******************************************************************************************/

#ifndef shell_h
#define shell_h
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;
class shell
	{
 		public:
			char* pPath, *pathes[10], *token, *cmd, *arg , *statement[10];
       			int cnt;
        		pid_t child_pid;
        		char input[80];
                        //***********Variable declaration**********

                        // pPath for storing path
                        // pathes is 2D array toseperate different pathes
                        // token stores strtok() return value
                        // cmd stores command
			// arg stors arguement
			// cnt is counter to track index for path
			// input char array is user input
			// child_pid stores child process id

			//**********Function Declaration*************
		
			shell();
			void start();
			void parse_path();
			void storing_command();
			void pipe_checker();
			void simulation();
			void execution(char * inp);
			void pipe_redirection();        	
			// shell is constructor to initialize variables
			// start function starts the shell simulator
			// parse_path parses path data into 2D array
			// simulation envokes infinite loop
			// execution to create child process and execute command passed by user
			// Pipe_checker cheks wether the command has pipe or not
			// Storing_commandstores the commands on two sides of pipes seperately in a character array called statements
			// Pipe_redirection handles the command consisting pipe
};
#endif

