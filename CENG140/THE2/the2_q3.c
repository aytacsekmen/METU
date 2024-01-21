#include <stdio.h>

int main() {
    // your code goes here
    int n;
    int m;
    int k;
    int S;
    
    scanf(" %d",&n);
    scanf(" %d",&m);
    scanf(" %d",&k);
    scanf(" %d",&S);
    int array_1[m][n];
    int array_2[k][5];
    int array_3[k][5];
    int reading;
    char reading1;
    int control=1;

    int array_statistics[k][5];
    int total_point;



    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {

            array_1[i][j]=45;
        }
    }
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<5;j++)
        {
            if (control)
            {
                scanf(" %c",&reading1);
                (int) reading1;
                array_2[i][j]=reading1;
                array_3[i][j]=reading1;
                control=0;

            }
            else
            {
            scanf(" %d",&reading);
            array_2[i][j]=reading;
            array_3[i][j]=reading;

            
            }
            

        }
        control=1;
    }
    int temp_array[5];
    for(int a=k-1;a>0;a--)
    {
        for(int i=0;i<a;i++)
        {
            if(array_2[i][4]<array_2[i+1][4])
            {
                for(int b=0;b<5;b++)
                {
                    temp_array[b]=array_2[i+1][b];
                    array_2[i+1][b]=array_2[i][b];
                    array_2[i][b]=temp_array[b];
                }
            }
        }
    }
    int distance;
    int radius_square;
    for(int b=0;b<k;b++)
    {
        
        array_statistics[b][0]=0;
        array_statistics[b][1]=0;
        array_statistics[b][4]=0;
        array_statistics[b][2]=0;
        array_statistics[b][3]=0;
        
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int d=0;d<k;d++)
            {
                distance=(j+1-array_2[d][1])*(j+1-array_2[d][1])+(i+1-array_2[d][2])*(i+1-array_2[d][2]);
                radius_square=(array_2[d][3])*(array_2[d][3]);
                if(distance<=radius_square)
                {
                    for(int b=0;b<k;b++)
                    {
                        if(array_2[d][0]==array_3[b][0])
                        {
                        array_statistics[b][0]+=1;
                        }
                    }
                
                    array_1[i][j]=array_2[d][0];
                }
            }
            //array_1[i][j]="--";
        }
    }
    for(int i=m-1;i>=0;i--)
    {
        for(int j=0;j<n;j++)
        {
            for(int d=0;d<k;d++)
            {
                if(array_1[i][j]==array_3[d][0])
                {
                    array_statistics[d][1]+=1;
                }
            }
            printf("%c",array_1[i][j]);
            printf("%c",array_1[i][j]);
        }
        printf("\n");
    }
    int length;
    int x;
    int radius;
    int radius_square_1;
    int distance_1;
    for(int d=0;d<k;d++)
    {
        length=2*array_3[d][3]+1;
        x=array_3[d][3];
        radius=array_3[d][3];
        for(int i=0;i<length;i++)
        {
            for(int j=0;j<length;j++)
            {
                distance_1=(j-x)*(j-x)+(i-x)*(i-x);
                radius_square_1=(radius)*(radius);
                if(distance_1<=radius_square_1)
                {
                    array_statistics[d][4]+=1;
                
                } 
            }
        }
    }


    //int total_number;
    for(int d=0;d<k;d++)
    {
        //total_number=(array_2[d][3])*(array_2[d][3])+(array_2[d][3]+1)*(array_2[d][3]+1);
        array_statistics[d][2]=array_statistics[d][0]-array_statistics[d][1];
        array_statistics[d][3]=array_statistics[d][4]-array_statistics[d][0];
        if(S==1)
        {
            printf("%d %d %d\n",array_statistics[d][1],array_statistics[d][2],array_statistics[d][3]);

        }
        //printf("%d %d %d\n",array_statistics[d][0],array_statistics[d][1] ,array_statistics[d][2]);
    }
    
    
    return 0;
}