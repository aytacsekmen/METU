#include <stdio.h>

int main()
{
    double real_number;
    int degree;
    int derivative;

    scanf("%lf",&real_number);
    scanf(" %d",&derivative);
    scanf(" %d",&degree);

    int i=degree;
    double coefficient=1;
    double result=0;
    double current_coefficient;
    for (i;i>-1;i=i-1)
    {
        int b=i;
        scanf(" %lf",&current_coefficient);
        coefficient=coefficient*current_coefficient;
        for(b;b>i-derivative;b=b-1)
        {
            coefficient=coefficient*b;
        }
        int c=0;
        for(c;c<i-derivative;c++)
        {
            coefficient=coefficient*real_number;
        }
        result=result+coefficient;
        coefficient=1;
    }
    printf("%.3f",result);
    return 0;
}
