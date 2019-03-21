/******************************************************************************************
*Name: Ribash Sharma                                                              *
*Class: Operating System                                                                  *
*Instructor: Chao Zhao                                                                    *
*Description: The program is for a shell simulator which communicates with kernel to run  *
*             commands                                                                    *
*******************************************************************************************/

//*******************************Including Variables**************************************
#include <string.h>
#include <stdlib.h>     
#include <stdio.h>     
#include <unistd.h>
#include <wait.h>
#include <iostream>
#include <sys/types.h>
using namespace std;


//**************************************************************************************
void execution(char * inp, char * pathes[10], int cnt)
{
        char *cmd;      //storing the command
        char *arg;      //storing the argument


        if( fork() == 0)        //child process
        {
                cmd = strtok(inp, " "); //parses the input and stores the command into cmd variable
                arg = strtok(NULL, " ");        //parses the input and stores the argument into arg
			
                for(int i = 0; i < cnt; i++)//go through all pathes if need
                {
                        char real[strlen(pathes[i])+1+strlen(cmd)]; //declaring a newcharacter array for storing the path with command
                        strcpy(real,pathes[i]); //copies path into character array real
                        strcat(real,"/");       //appends "/" with path stored in a character array called real
                        strcat(real, cmd);      //appends the cmd with path stored in a character array called real
                        execl(real,cmd,arg,0);  //system call for executing the command and argument passed by the user in the provided path

                }
 
               cout<<"Command  not Found"<<endl;       //check all the path in an array and exits out for loop and prints the statement
                exit(0);        //stops child process

        }

        else
        {

                wait(NULL);     //makes the parent process to wait

        }


}
//*************************************************************************************************************
int main ()
{	

  
	char * statement[10];
  	char input[80];	//char array for storing user input
        char* pPath;    //storing variables
        char *pathes[10];       //storing the value of data parsed
        char *token;    //storing the value return from strtok

        int cnt = 0;    //indexing for the pathes array
        pPath = getenv ("PATH");

        token = strtok(pPath, ":");
        while (token != NULL)
        {
                pathes[cnt] = token;
                cnt++;
                token = strtok(NULL, ":");
        }
  
 
  for(;;)	//infinite for loop
  {
 
	cout<<" > ";
	fgets(input, 80, stdin);
	input[strlen(input)-1] = '\0';
		if(strcmp(input,"exit") == 0 || strcmp(input, "quit") == 0)//copmaring string for exit function
    		{
     			cout<<"\nThank you!\n";
			exit(0);
    		}
       		else if(strchr(input, '|') == NULL)
    		{       		
		execution(input, pathes, cnt);
  	
		}
		else
		{
                	statement[0] = strtok(input, "|"); //parses the input and stores the command into cmd variable
               		 statement[1] = strtok(NULL, "|");        //parses the input and stores the argument into arg
		        int filedes[2];
        		int pid,  f1, f2, status;
        		pipe(filedes);

        		if((f1 = fork())==0)
        		{
	        	        close(1);
		                dup(filedes[1]);
                		close(filedes[0]);
                		execution(statement[0], pathes,cnt);
                		_exit(0);

        		}

        		if((f2=fork())==0)
        		{
		                close(0);
                		dup(filedes[0]);
                		close(filedes[1]);
                		execution(statement[1],pathes,cnt);
                		_exit(0);

        		}

        	close(filedes[0]);
        	close(filedes[1]);

        	do{
                	pid =wait(&status);
                	if(pid == f1)
                	{
                        	f1 = 0;
                	}
                	if(pid == f2)
                	{
                        f2 = 0;
                	}
        	} while(f1 != f2 && pid!= -1);

	}
    }	
  return 0;
}
