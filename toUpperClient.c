#include <stdio.h>
#include "unistd.h"
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char * readFile(char * filename)
{
    int num;
    FILE * fptr;
    fptr = fopen(filename,"r");
    
    fseek(fptr,0,SEEK_END);
    long length = ftell(fptr);
    fseek(fptr,0,SEEK_SET);
    char * buffer = (char*)malloc((length+1)*sizeof(char));
    if (buffer)
    {
        fread(buffer,sizeof(char),length,fptr);
    }
    fclose(fptr);
    
    buffer[length] = '\0';
    return buffer;
}

int main(int argc,char  argv[])
{
    char * buffer = readFile("a.inpf");
    int c = mkfifo("User",0666);
    int s = mkfifo("Server",0666);

    if(c<0 || s<0)
    {
       printf("Error");
    }

    int writeToServer = open("User",O_WRONLY);      
    int readFromServer = open("Server",O_RDONLY);
    

    int comm1[2],comm2[2],comm3[2];
    pipe(comm1);
    pipe(comm2);
    pipe(comm3);

    pid_t processGrep = fork();
    if(processGrep == 0)
    {
        //pipe 2 completely close
        close(comm2[0]);
        close(comm2[1]);
        //pipe 3 completely close
        close(comm3[0]);
        close(comm3[1]);
        
        
        close(comm1[0]);  // pipe 1 reading close 
        
        //      cout << "writeen to pipe1" << endl;
        
        printf("Writing 1");        
        dup2(comm1[1], 1);   // write to pipe 1

        execl("encService", "encService",buffer, NULL);
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
            
            // cout << "written to pipe2 after reading from pipe1 " << endl;
            // dup2(comm1[0], 0);  //read from pipe1

            char foo[100];
            int nbytes = read(comm1[0], foo, sizeof(foo));
            printf("%s",foo);

            dup2(comm2[1], 1);  //write to pipe2
            execl("addParity","addParity", foo,NULL);    
        }
        else        
        {
            char foo[100];
            int nbytes = read(comm2[0], foo, sizeof(foo));
            foo[nbytes] ='\0';

            char str1[100] = "0001011000010110";
            char str2[] = "00000100";

           
            strcat(str1, str2);

            strcat(str1,foo);

            printf("%s\n",str1);
            

            FILE * file = fopen("a.binf","w+");
            int return_val = fputs(str1,file);
            
            write(writeToServer,&str1,100);
                
            close(writeToServer);
            close(readFromServer);
            
            unlink("User");                 
            unlink("Server");
            close (comm2[1]);   //pipe2 write close
            wait(NULL);
        }

        wait(NULL);            
    }


}





