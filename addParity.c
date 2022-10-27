#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "encDec.h"


// 1000001
// 1000011
// 1000011
// 1000010";

int main(int argc,char * argv[])
{
    // argv[1] = "1000001100001110000111000010";
    addParity(argv[1]);
}


int count(char * inData)
{

    int counter =0;
    for (int i = 0; i < 7; ++i)
    {
        if (inData[i] == '1'){
            counter = counter + 1;
        }
    }

    if(counter%2 ==0)
    {
        return 0;
    }
    else{
        return 1;
    }
}

void addParity(char * inData)
{

    int n = 0;
    for (int i = 0; inData[i] != '\0' && inData[i] != '\n'; ++i)
    {
        n = n+1;
    }
    n = n-1;


    int bits = 7;
    char * word = (char*)malloc(sizeof(char) * 9 );
    char * p_frame = (char*)malloc(sizeof(char) * 33 );

    int frame_c = 31;
    word[8] = '\0';
    int total =0;

    while(n>0)
    {
        bits = bits -1;
        word[bits] = inData[n];
        p_frame[frame_c] = inData[n];
        frame_c = frame_c -1;

        if(bits == 0)
        {
            // printf("%d\n",n);
            // printf("%s \n",word);
            // printf("%d \n",frame_c);

            if (count(word)  == 1)
            {
                p_frame[frame_c] = '0';
            }
            else{
                p_frame[frame_c] = '1';
            }

            frame_c = frame_c -1;
            
            bits =7;
            total = total +1;
        }

        n = n-1;
        
    } 

    bits = bits -1;
    word[bits] = inData[n];
    p_frame[frame_c] = inData[n];
    frame_c = frame_c -1;
    
    if (count(word)  == 1)
    {
        p_frame[frame_c] = '0';
    }
    else{
        p_frame[frame_c] = '1';
    }

    printf("%s",p_frame);

}
