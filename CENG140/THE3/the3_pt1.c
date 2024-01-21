#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//satır satır okumaya yarıyor
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

//void printJaggedArray(char *jaggedArray)
//{
//    
//    //for (int i = 0; i < 99; i++)
//    //{
//    //    for (int j = 0; j < 99; j++)
//    //    {
//            printf("%s", jaggedArray);
//    //    }
//
//    //    printf("\n");
//    //}
//}

//void command_writing(char* command,char** commands,int count)
//{
//    char temp[100]={0};
//    for(int i=0;i<=strlen(command);i++)
//    {
//        temp[i]=command[i];
//    } 
//    commands[count]=temp;
//
//
//}
void goback_function(char** variables, int* variable_values,int variable_count,char ** commands, int line_togo,int line_of_goback)
{

}
int main()
{
    //printf("Enter some text, line by line:\n");
 
    //// Allocate the top-level pointer array.
    //char **commands = malloc(sizeof(char *[count]));
    //
    //// Create a float array to represent each row individually. Store the
    //// addresses of these arrays in the top-level array.
    //for (int i = 0; i < count; i++)
    //{
    //    // Allocate the ith row.
    //    commands[i] = malloc(sizeof(char[1]));
    //}

    char** commands=malloc(sizeof(char *[100]));
    for (int i = 0; i < 100; i++)
    {
        // Allocate the ith row.
        commands[i] = malloc(sizeof(char[100]));
    }
    
    int count=0;
    char variables[100][100]={0};
    int variable_values[100]={0};
    int variable_count=0;
    //for(int i=0;i<100;i++)
    //{
    //    for (int j=0;i<100;i++)
    //    {
    //        
    //    }
    //}
    
    while(1)
    {
        //char copy1[100];
        //char buf[100];
        
        int rv = readLine(commands[count], 100);
        //memcpy(copy1,buf,100);

        if (rv == 0)
        {
            return 0; //error
        }
        //int length=strlen(buf);
        //command_writing(buf,commands,count);
        //commands[count]=copy1;
        //char **commands1 = malloc(sizeof(char *[rowcount]));

        // Create a float array to represent each row individually. Store the
        // addresses of these arrays in the top-level array.
        
        // Allocate the ith row.
        //commands1[count] = malloc(sizeof(char[length]));
        
        //for(int i=0;i<count;i++)
        //{
        //    //printf("Your line: %s\n", *commands1[i]);
        //    printJaggedArray(commands[i]);
        //}

        
        if(strcmp(commands[count],"exit")==0)
        {
            break;
        }
        count++;
        
        
       // for (int i = 0; i < count; i++)
       // {
       //     // Allocate the ith row.
       //     commands[i] = realloc(commands,sizeof(char[strlen(buf)]));
       // }
       // int i;
       // for(i=0;1;i++)
       // {
       //     if(*commands[i]==0)
       //     {
       //         break;
       //     }
       //     printf("Your line: %s\n", *commands[i]);
       //     
       //}
        if (rv == -1)
        {
            //printf("This was the last line. Exiting...\n");
            break;
        }

    }
    int control_goto=1;
    int goback_start=0;
    
    char** copy1=malloc(sizeof(char *[100]));
    for (int i = 0; i < 100; i++)
    {
        // Allocate the ith row.
        copy1[i] = malloc(sizeof(char[100]));
    }
    label11:;
    for(int i=0;i<count;i++)
    {
        strcpy(copy1[i],commands[i]);
    }
    //char* splitted;
    //char cpy[100]={0};
    char command[100]={0};
    int line=0;
    char variable1[100]={0};
    char variable2[100]={0};
    int value=0;
    int control=1;
    //sıkıntı goback'te
    for(int loop_pos=goback_start;loop_pos<count;loop_pos++)
    {
                
        
        sscanf( copy1[loop_pos],"%s ",command);// i get command here

        //splitted=strtok(copy1[i]," "); //command name
        if (strcmp(command,"set")==0)
        {

             //printing each token
            //splitted = strtok(NULL, " "); //var name
            sscanf( copy1[loop_pos],"%s %s %d",command, variable1,&value);
            if( variable_count==0)
            {
                strcpy(variables[variable_count],variable1);
                //splitted = strtok(NULL, " "); //value
                //int temp=atoi(splitted);
                variable_values[variable_count]=value;
                variable_count++;
            }
            else
            {
                for(int i=0;i<variable_count;i++)
                {
                    if(strcmp(variables[i],variable1)==0)
                    {
                        control=0;
                        //splitted = strtok(NULL, " ");
                        variable_values[i]=value;
                        break;
                    }
                }
                if(control==1)
                {
                    strcpy(variables[variable_count],variable1);
                    //splitted = strtok(NULL, " ");
                    variable_values[variable_count]=value;
                    variable_count++;

                }
                control=1;
            }
            
        }
        else if(strcmp(command,"add")==0)
        {
            sscanf( copy1[loop_pos],"%s %s %s",command, variable1,variable2);
            int control=1;
            int var1_name_order;
            int var2_name_order;
            //splitted = strtok(NULL, " "); //1st var name
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable1)==0)
                {
                    control=0;
                    var1_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable1);
                variable_values[variable_count]=0;
                
                var1_name_order=variable_count;
                variable_count++;
            }
            control=1;
            //splitted = strtok(NULL, " "); //2nd var name
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable2)==0)
                {
                    control=0;
                    var2_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable2);
                variable_values[variable_count]=0;
                var2_name_order=variable_count;
                variable_count++;

            }
            control=1;
            //I have checked whether it is previously defined variable or not

            if ((variable_values[var1_name_order]+variable_values[var2_name_order])>99)
            {
                variable_values[var1_name_order]=99;
            }
            else
            {
            variable_values[var1_name_order]+=variable_values[var2_name_order];
            }
        }
        else if(strcmp(command,"sub")==0)
        {
            sscanf( copy1[loop_pos],"%s %s %s",command, variable1,variable2);
            int control=1;
            int var1_name_order;
            int var2_name_order;
            //splitted = strtok(NULL, " "); //1st var name
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable1)==0)
                {
                    control=0;
                    var1_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable1);
                variable_values[variable_count]=0;
                
                var1_name_order=variable_count;
                variable_count++;
            }
            control=1;
            //splitted = strtok(NULL, " "); //2nd var name
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable2)==0)
                {
                    control=0;
                    var2_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable2);
                variable_values[variable_count]=0;
                
                var2_name_order=variable_count;
                variable_count++;
            }
            control=1;
            //I have checked whether it is previously defined variable or not

            if ((variable_values[var1_name_order]-variable_values[var2_name_order])<0)
            {
                variable_values[var1_name_order]=0;
            }
            else
            {
            variable_values[var1_name_order]-=variable_values[var2_name_order];
            }
        }
        else if(strcmp(command,"show")==0)
        {
            sscanf( copy1[loop_pos],"%s %s",command, variable1);
            int control=1;
            int var1_name_order;
            //splitted = strtok(NULL, " "); //1st var name
            
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable1)==0)
                {
                    control=0;
                    var1_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable1);
                variable_values[variable_count]=0;
                
                var1_name_order=variable_count;
                variable_count++;
            }
            char* print_var_name;
            int value=variable_values[var1_name_order];
            print_var_name=variables[var1_name_order];
            printf("%s = %d\n",print_var_name,value);
        }
        else if(strcmp(command,"goback")==0)
        {
            sscanf( copy1[loop_pos],"%s %d %s %s",command,&line, variable1,variable2);
            //splitted = strtok(NULL, " ");
            int line_togo=line;
            int control=1;
            int var1_name_order;
            int var2_name_order;
            //splitted = strtok(NULL, " "); //1st var name
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable1)==0)
                {
                    control=0;
                    var1_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable1);
                variable_values[variable_count]=0;
                
                var1_name_order=variable_count;
                variable_count++;
            }
            control=1;
            //splitted = strtok(NULL, " "); //2nd var name
            for(int i=0;i<variable_count;i++)
            {
                if(strcmp(variables[i],variable2)==0)
                {
                    control=0;
                    var2_name_order=i;
                    break;
                }
            }
            if(control==1)
            {
                strcpy(variables[variable_count],variable2);
                variable_values[variable_count]=0;
                
                var2_name_order=variable_count;
                variable_count++;
            }
            
            control=1;
            //I have checked whether it is previously defined variable or not

            if(variable_values[var1_name_order]>=variable_values[var2_name_order])
            {
                continue;
            }
            goback_start=loop_pos- line_togo;
            control_goto=0;
            break;

        }
    }
    if (control_goto==0)
    {
        control_goto=1;
        goto label11;
    }
    
    return 0;
}