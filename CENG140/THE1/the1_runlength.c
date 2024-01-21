#include <stdio.h>

int main()
{
    char input;
    char character1;
    int number=0;
    int control;
    control=1;
    for (int i=0;1;i++)
    {
        scanf("%c",&input);

        if(input==10)
        {
            printf("%d",number);
            printf("%c",character1);
            break;
        }
        if (control==1)
        {
            character1=input;
            number++;
            control=0;
            continue;

        }
        if(input==character1)
        {
            number++;
            continue;
        }
        if (input!=character1)
        {
            printf("%d",number);
            printf("%c",character1);
            character1=input;
            number=1;
            continue;
        }
    }
    return 0;
}
