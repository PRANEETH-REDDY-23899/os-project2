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
    remParity(argv[1]);
}



void remParity(char * inData)
{
    int n = 0;
    for (int i = 0; inData[i] != '\0' && inData[i] != '\n'; ++i)
    {
        n = n+1;
    }

    char rem[100] = "";
    int j =0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || i == 8 || i == 16 || i == 24)
        {
            
        }
        else{
            rem[j] = inData[i];
            j++;
        }
        
    }
    rem[j] = '\0';

    printf("%s",rem);
}
