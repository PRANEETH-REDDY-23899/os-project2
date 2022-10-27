#include <stdio.h>
#include "unistd.h"
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


int main(int argc,char  argv[])
{

    int readFromUser = open("User",O_RDONLY);           
    int writeToUser = open("Server",O_WRONLY);
    

    int comm1[2],comm2[2],comm3[2],comm4[0];
    pipe(comm1);
    pipe(comm2);
    pipe(comm3);
    pipe(comm4);

    pid_t processGrep = fork();
    if(processGrep == 0)
    {
        //pipe 2 completely close
        close(comm2[0]);
        close(comm2[1]);

        //pipe 3 completely close
        close(comm3[0]);
        close(comm3[1]);
        
        //pipe 4 completely close
        close(comm4[0]);
        close(comm4[1]);
        
        
        close(comm1[0]);  // pipe 1 reading close 
        
        
        char Buffer[100];
        read(readFromUser,&Buffer,sizeof(Buffer));
              
        dup2(comm1[1], 1);   // write to pipe 1
        printf("%s",Buffer);

    }
    else
    {
            
        close(comm1[1]);   // pipe1 write close
        
        pid_t processSort = fork();
        if( processSort == 0 )
        {
            close (comm2[0]);   //pipe2 read close
            close (comm3[0]);   //pipe3 read close
            close (comm3[1]);   //pipe3 read close
            //pipe 4 completely close
            close(comm4[0]);
            close(comm4[1]);
            char foo[100];
            int nbytes = read(comm1[0], foo, sizeof(foo));
            foo[nbytes] ='\0';

            char encoded[35] = "";

            for (int i = 24,j =0; i < nbytes ; ++i,j++)
            {
               encoded[j] = foo[i];
            }
        


            dup2(comm2[1], 1);  //write to pipe2
            execl("remParity","remParity", encoded,NULL);    
        }
        else        
        {
            close (comm2[1]);   //pipe2 write close


            pid_t processSum = fork();      
            if( processSum == 0 )
            {
                close (comm3[0]);   //pipe3 read close
                close (comm1[0]);   //pipe1 read close
                close (comm1[1]);   //pipe1 write close
                
    
                //read from pipe2 
                char foo[100];
                int nbytes = read(comm2[0], foo, sizeof(foo));
                foo[nbytes] ='\0';

                dup2(comm3[1], 1);  //write to pipe3 
                execl("decService", "decService",foo, NULL);
            }
            else
            {
                close (comm3[1]);   //pipe3 write close
                                
                pid_t processWc = fork();       
                if( processWc == 0 )
                {
                    char foo[100];
                    int nbytes = read(comm3[0], foo, sizeof(foo));
                    foo[nbytes] ='\0';

                    printf("%s\n",foo); 
                    // execl("toUpperService", "toUpperService",foo, NULL);
                }
                else
                {
                    close(comm3[0]);
                    close(comm2[1]);
                    close(comm2[0]);
                    close(comm1[1]);
                    close(comm1[0]);
                    
                    wait(NULL);
                    wait(NULL);
                    
                }
            }
        }        

        wait(NULL);            
    }


}





