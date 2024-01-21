//#include "the3.h"
#include <iostream>
#include <limits>

int max3(int number1,int number2, int number3)
{
    if (number1 >= number2) 
    {
        if (number1 >= number3) 
        {
            return number1;
        }
        else 
        {
            return number3;
        }
    }
    else {
        if (number2 >= number3) 
        {
            return number2;
        }
        else 
        {
            return number3;
        }
    }
}
int max2(int number1,int number2)
{
    if (number1 >= number2) 
    {
        return number1;
    }
    else
    {
        return number2;
    }
}

int array[10001][10001];
int myrecursive(std::string sequence_A, std::string sequence_B,int locA, int locB, int gap, int mismatch, int match, std::string &possible_alignment, int& call_count,int& highest_alignment_score)
{
    int ara_deger4;
    if(locA==0)
    {
        return -locB*gap;
    }
    else if(locB==0)
    {
        return -locA*gap;
    }
    else
    {
        int ara;
        if(sequence_A[locA-1]==sequence_B[locB-1])
        {
            ara=match;
        }
        else
        {
            ara=-mismatch;
        }
        int aradeger1;
        int aradeger2;
        int aradeger3;
        call_count++;
        if(call_count>=1000000)
        {
            possible_alignment="STACK LIMIT REACHED";
            return INT_MIN;
        }
        

        aradeger1=myrecursive( sequence_A,sequence_B, locA-1,locB-1, gap, mismatch,  match,possible_alignment, call_count,highest_alignment_score);
        array[locB-1][locA-1]=aradeger1;
        aradeger1=aradeger1+ara;
        call_count++;
        if(call_count>=1000000)
        {
            possible_alignment="STACK LIMIT REACHED";
            return INT_MIN;
        }
        aradeger2=myrecursive( sequence_A,sequence_B, locA,locB-1, gap, mismatch,  match,possible_alignment, call_count,highest_alignment_score);
        array[locB-1][locA]=aradeger2;
        aradeger2=aradeger2-gap;
        call_count++;
        if(call_count>=1000000)
        {
            possible_alignment="STACK LIMIT REACHED";
            return INT_MIN;
        }
        aradeger3=myrecursive( sequence_A,sequence_B, locA-1,locB, gap, mismatch,  match,possible_alignment, call_count,highest_alignment_score);
        array[locB][locA-1]=aradeger3;
        aradeger3=aradeger3-gap;
        ara_deger4=max3(aradeger1,aradeger2,aradeger3);
        array[locB][locA]=ara_deger4;
        return ara_deger4;
    }


}
int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    int highest_alignment_score;
    int size_A=sequence_A.size();
    int size_B=sequence_B.size();
    int aradeger;
    aradeger=myrecursive(sequence_A,sequence_B,size_A,size_B,gap,mismatch,match,possible_alignment,call_count,highest_alignment_score);

    if (possible_alignment!="STACK LIMIT REACHED")
    {
        //for(int i=0;i<=size_A;i++)
        //{
        //    array[0][i]=0-i*gap;
        //}
        //for(int i=0;i<=size_B;i++)
        //{
        //    array[i][0]=0-i*gap;
        //}
        int i=size_B;
        int j=size_A;
        possible_alignment="";
        while (i > 0 && j > 0) 
        {
            if(sequence_A[j-1]==sequence_B[i-1])
            {
                if(array[i][j]-match==array[i-1][j-1])
                {
                    possible_alignment=sequence_A[j-1]+possible_alignment;
                    i--;
                    j--;
                }
                else if (array[i - 1][j] > array[i][j - 1])
                {
                    possible_alignment="_"+possible_alignment;
                    i--;
                }
                else
                {
                    possible_alignment="."+possible_alignment;
                    j--;
                }


            }
            else
            {
                if(array[i][j]+mismatch==array[i-1][j-1])
                {
                    possible_alignment="!"+possible_alignment;
                    i--;
                    j--;
                }
                else if (array[i - 1][j] > array[i][j - 1])
                {
                    possible_alignment="_"+possible_alignment;
                    i--;
                }
                else
                {
                    possible_alignment="."+possible_alignment;
                    j--;
                }
            }


        }
        while(i>0)
        {
            possible_alignment="_"+possible_alignment;
            i--;
        }
        while(j>0)
        {
            possible_alignment="."+possible_alignment;
            j--;
        }
    }
    
    return aradeger;
}

int arr[10001][10001];
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    int highest_alignment_score;
    int size_A=sequence_A.size();
    int size_B=sequence_B.size();
    
    for(int i=0;i<=size_A;i++)
    {
        arr[0][i]=0-i*gap;
    }
    for(int i=0;i<=size_B;i++)
    {
        arr[i][0]=0-i*gap;
    }
    
    int aradeger;
    for(int i=1;i<=size_B;i++)
    {
        for(int j=1;j<=size_A;j++)
        {
            
            if(sequence_A[j-1]==sequence_B[i-1])
            {
                aradeger=match;
            }
            else
            {
                aradeger=(-mismatch);
            } 

            arr[i][j]=max3(arr[i-1][j-1]+aradeger,arr[i-1][j]-gap,arr[i][j-1]-gap);

        }
    }
    int i=size_B;
    int j=size_A;
    possible_alignment="";
    while (i > 0 && j > 0) 
    {
        if(sequence_A[j-1]==sequence_B[i-1])
        {
            if(arr[i][j]-match==arr[i-1][j-1])
            {
                possible_alignment=sequence_A[j-1]+possible_alignment;
                i--;
                j--;
            }
            else if (arr[i - 1][j] > arr[i][j - 1])
            {
                possible_alignment="_"+possible_alignment;
                i--;
            }
            else
            {
                possible_alignment="."+possible_alignment;
                j--;
            }
            
            
        }
        else
        {
            if(arr[i][j]+mismatch==arr[i-1][j-1])
            {
                possible_alignment="!"+possible_alignment;
                i--;
                j--;
            }
            else if (arr[i - 1][j] > arr[i][j - 1])
            {
                possible_alignment="_"+possible_alignment;
                i--;
            }
            else
            {
                possible_alignment="."+possible_alignment;
                j--;
            }
        }
        
        
    }
    while(i>0)
    {
        possible_alignment="_"+possible_alignment;
        i--;
    }
    while(j>0)
    {
        possible_alignment="."+possible_alignment;
        j--;
    }

    highest_alignment_score=arr[size_B][size_A];
    return highest_alignment_score;    
}


int main()
{
    int gap=10;
    int mismatch=0;
    int match=0;
    int call_count=0;
    std::string stringA="A";
    std::string stringB="Z";
    std::string possiblealignment;
    int returnval=dp_table_alignment(stringA,stringB,gap,mismatch,match,possiblealignment);
    int returnval1=recursive_alignment(stringA,stringB,gap,mismatch,match,possiblealignment,call_count);
    return 0;
}