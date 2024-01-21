#include <stdio.h>

int main()
{
    double first;
    double second;
    char character;
    scanf("%lf",&first);
    scanf(" %c",&character);
    scanf(" %lf",&second);

    if(character==42){
        double result=first*second;
        printf("%.3f",result);
    }
    if(character==43){
        double result=first+second;
        printf("%.3f",result);
    }
    if(character==47){
        double result=first/second;
        printf("%.3f",result);
    }
    if(character==45){
        double result=first-second;
        printf("%.3f",result);
    }

    return 0;
}
