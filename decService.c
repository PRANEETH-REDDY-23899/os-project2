#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "encDec.h"
#include <string.h>





unsigned long binaryToDecimal(char *binary, int length)
{
    int i;
    unsigned long decimal = 0;
    unsigned long weight = 1;
    binary += length - 1;
    weight = 1;
    for(i = 0; i < length; ++i, --binary)
    {
        if(*binary == '1')
            decimal += weight;
        weight *= 2;
    }
    
    return decimal;
}

void binaryToText(char *binary, int binaryLength, char *text, int symbolCount)
{
    int i,j=0;
    char * byte = (char*)malloc(sizeof(char) * 8 );
    for(i = 0; i < binaryLength; i++)
    {
        byte[j] = binary[i];
        j++;

        if(i == 6 || i == 13 || i==20 || i==27)
        {
            byte[7] = '\0';
            *text++ = binaryToDecimal(byte, 7);

            byte = (char*)malloc(sizeof(char) * 8 );
            j=0;   
        }
        
        
    }
    text -= symbolCount;
}



int main(int argc,char * argv[])
{

    decode(argv[1]);
    
}

void decode(char binary[])
{
    int binaryLength;
    binaryLength = strlen(binary);
    
    int symbolCount = binaryLength / 7 + 1;
    char *text = malloc(symbolCount + 1);

    if(binaryLength % 7 == 0)
    {
        --symbolCount;
    }

   

    binaryToText(binary, binaryLength, text, symbolCount);
    printf("%s",text);
}



