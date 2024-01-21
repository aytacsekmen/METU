#include <stdio.h>

int main()
{
    /* WRITE YOUR CODE HERE */

    int first;
    int second;
    int third;
    int fourth;
    char character;
    int last;
    scanf("%d",&first);
    scanf(" %d",&second);
    scanf(" %d",&third);
    scanf(" %d",&fourth);
    scanf(" %c",&character);
    scanf(" %d",&last);

    int result;

    if (last==1){

        printf("%d",first);
    }
    else if(last==2){
        printf("%d",second);
    }
    else if(last>2){

        for(int i=2;i<last;i++){

            if(character==45){
                result=first*third-second*fourth;
                first=second;
                second=result;
            }

            if(character==43){
                result=first*third+second*fourth;
                first=second;
                second=result;
            }
        }

    }
    printf("%d",result);

    return 0;
}
