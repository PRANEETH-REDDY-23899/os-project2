#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "encDec.h"
#include <string.h>


int main(int argc,char * argv[])
{
    encode(argv[1]);
    // printf("%.*s\n",7,);
}

void to_bin(int value,char * bin,int*p)
{
    char base_range[] = "01";
    if ( value >=2 )
    {
        to_bin(value/2,bin,p);
    }
    
    bin[(*p)++] = base_range[value % 2];
}

void encode(char * inData)
{

    int n = 0;
    for (int i = 0; inData[i] != '\0' && inData[i] != '\n'; ++i)
    {
        n = n+1;
    }
    

    char str1[100] = "";
     
    

    int i =0;
    while(i < n)
    {

        int val = (int)(inData[i]);
        char * result = (char*)malloc(sizeof(char) * 32 );
        int j = 0;
        to_bin(val,result,&j);
        result[j] = '\0';
        strcat(str1, result);
        
        i = i+1;
    }
    printf("%s",str1);


}
