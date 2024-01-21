#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    TODO: Declare any global variables here
*/
int readLine(char *buffer, unsigned bufferSize)
{
    unsigned nextIndex = 0;

    while (1)
    {
        if (nextIndex == bufferSize)
        {
            return 0; // Out of buffer. Indicate error.
        }

        char c;
        int rv = scanf("%c", &c);

        if (rv == EOF)
        {
            buffer[nextIndex] = '\0';
            return -1; // Indicate that the end of the input was hit.
        }

        if (rv != 1) // Some other unknown error. Unlikely to happen.
        {
            return 0; // Indicate error.
        }

        // Successfully read ``c'' at this point.

        if (c == '\n')
        {
            buffer[nextIndex] = '\0';
            return +1; // Indicate that a newline was hit.
        }
        else
        {
            buffer[nextIndex] = c;
            nextIndex++;
        }
    }
}
int countOccurrences(char * str, char * toSearch)
{
    int i, j, found, count;
    int stringLen, searchLen;

    stringLen = strlen(str);      // length of string
    searchLen = strlen(toSearch); // length of word to be searched

    count = 0;

    for(i=0; i <= stringLen-searchLen; i++)
    {
        /* Match word with string */
        found = 1;
        for(j=0; j<searchLen; j++)
        {
            if(str[i + j] != toSearch[j])
            {
                found = 0;
                break;
            }
        }

        if(found == 1)
        {
            count++;
        }
    }

    return count;
}
char *multi_tok(char *input, char *delimiter) {
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
        return string;

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}
int main() {
    
    char** array=malloc(sizeof(char *[3]));
    for (int i = 0; i < 3; i++)
    {
        // Allocate the ith row.
        array[i] = malloc(sizeof(char[300]));
    }
    for(int i=0;i<300;i++)
    {
        array[2][i]=0;
    }
    
    for(int i=0;i<3;i++)
    {
        if (i!=2)
        {
        int rv = readLine(array[i], 300);


            if (rv == 0)
            {
                return 0; //error
            }
            if (rv == -1)
            {
                break;
            }
        }
        if (i==2)
        {
            char c;
            int character_count=0;
            for (int j=0;j<300;j++)   
            {     
                c = getc(stdin);

                if(c==-1)
                {
                    break;
                }
                if(c==10)
                {
                    
                }
                else
                {
                array[2][character_count]=c;
                character_count++;
                }

                

            }
        }
    }
    int count_delimiter=countOccurrences(array[2],array[0]);


    char** array_delimiter1=malloc(sizeof(char *[count_delimiter+1]));
    for (int i = 0; i < count_delimiter+1; i++)
    {
        // Allocate the ith row.
        array_delimiter1[i] = malloc(sizeof(char[300]));
    }
    char** array_delimiter2=malloc(sizeof(char *[2*count_delimiter]));
    for (int i = 0; i < 2*count_delimiter; i++)
    {
        // Allocate the ith row.
        array_delimiter2[i] = malloc(sizeof(char[300]));
    }
    //okumayı yaptım




    char* token;
    int count_delimit=0;

    token = multi_tok(array[2], array[0]);

    
   
    /* walk through other tokens */
    while( token != NULL ) {
        
        strcpy(array_delimiter1[count_delimit],token);
        count_delimit++;
        token = multi_tok(NULL, array[0]);

       
    }
    //ilk delimiter'e göre split yaptım.

    int count_delimit_1=0;
    int array_lengths[count_delimiter][2];
    int length_delimited;
    for(int i=1;i<count_delimiter+1;i++)
    {
        char* token;

        token = multi_tok(array_delimiter1[i], array[1]);

        /* walk through other tokens */
        while( token != NULL ) {
            
            strcpy(array_delimiter2[count_delimit_1],token);

            count_delimit_1++;
            token = multi_tok(NULL, array[1]);
        }
    }
    //ikinci delimiter'e göre split yaptım.

    int counting=0;
    for (int i=0;i<2*count_delimiter;i=i+2)
    {
        length_delimited= strlen(array_delimiter2[i]);
        array_lengths[counting][0]=i;
        array_lengths[counting][1]=length_delimited;
        counting++;

    }

    //sort yapmak

    int temp_array[2];
    
    for (int i = 0; i < count_delimiter-1; i++) 
    {
      for (int j = 0; j < count_delimiter-1-i; j++)
        {
          if (array_lengths[j][1]>array_lengths[j+1][1]) 
            {
                for(int x=0;x<2;x++)
                {
                    temp_array[x]=array_lengths[j][x];
                    array_lengths[j][x]=array_lengths[j+1][x];
                    array_lengths[j+1][x]=temp_array[x];
                }
            }
      }
    }


    //printlemek
    for(int i=0;i<count_delimiter;i++)
    {
        printf("%s\n",array_delimiter2[array_lengths[i][0]]);
    }
    printf("%s",array_delimiter1[0]);
    for(int i=0;i<2*count_delimiter;i++)
    {
        printf("%s",array_delimiter2[i]);
    }
    printf("\n");
    
      
    //ikinci delimiter'e göre split ettim.

    //int array1[2][50];
    //int count=0;
    //for (int i=0;i<100;i++)
    //{
    //    if(strcmp(array[2][i],array[0])==0)
    //    {
    //        array[count][0]=i;
    //        for(int b=i+1;b<100;b++)
    //        {
    //            if(strcmp(array[2][i],array[1])==0)
    //            {

    //            }
    //        }
    //    }
    //}
    

    

    return 0;
}