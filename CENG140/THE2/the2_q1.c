#include <stdio.h>

int main() {
    // your code goes here
    int n;
    int m;
    scanf(" %d",&n);
    scanf(" %d",&m);
    int reading;
    int array_n[n];
    int array_m[m];
    for(int i=0;i<n;i++)
    {
        scanf(" %d",&reading);
        array_n[i]=reading;
    }
    for(int i=0;i<m;i++)
    {
        scanf(" %d",&reading);
        array_m[i]=reading;
    }
    int length=n-m;
    int sum=0;
    for(int i=0;i<length+1;i++)
    {
        for(int b=0;b<m;b++)
        {
            sum=sum +array_m[b]*array_n[b+i];
        }
        printf("%d ",sum);
        sum=0;
    }




    return 0;
}