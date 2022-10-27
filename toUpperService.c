#include <stdio.h>
#include <ctype.h>
#include "encDec.h"

int main(int argc,char * argv[])
{
    toUpper(argv[1]);
    printf("%s\n", argv[1]);
}

void toUpper(char * inData)
{

    for (int i = 0; inData[i] != '\0' && inData[i] != '\n'; ++i)
    {
        if ( (int)inData[i] >= 'a' && (int)inData[i] <= 'z' )
        {        
            inData[i] = toupper(inData[i]);
        }
    }
   
}
