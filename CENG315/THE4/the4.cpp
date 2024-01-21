//#include "the4.h"
#include <iostream>

int array[601][601];
int divide_land(int X, int Y, bool** possible_plots)
{
    
    for(int i=1;i<=X;i++)
    {
        for(int j=1;j<=Y;j++)
        {
            if(possible_plots[i][j])
            {
                array[i][j]=0;
            }
            else
            {
                array[i][j]=i*j;
                int aradeger;
                for(int k=0;k<i;k++)
                {
                    aradeger=array[i-k][j]+array[k][j];
                    if(aradeger<array[i][j])
                    {
                        array[i][j]=aradeger;
                    }
                }
                for(int l=0;l<j;l++)
                {
                    aradeger=array[i][j-l]+array[i][l];
                    if(aradeger<array[i][j])
                    {
                        array[i][j]=aradeger;
                    }
                }
            }
            
        }
    }
    int result=array[X][Y];
	return result;
}

int main()
{
    int X=13;
    int Y=7;
    bool** possible_plots = new bool*[X+1];
    for(int temp=0; temp < X+1; temp++) possible_plots[temp] = new bool[Y+1];
    for(int idx=0; idx < X+1; idx++) for(int idy=0; idy < Y+1; idy++) possible_plots[idx][idy] = false;
    possible_plots[2][2]=true;
    possible_plots[11][6]=true;
    possible_plots[12][5]=true;
    std::string possiblealignment;
    int returnval=divide_land(X,Y,possible_plots);
    return 0;
}