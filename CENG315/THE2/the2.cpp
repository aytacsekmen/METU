#include <iostream>

void maxlength(std::string* arr,int size,int& length)
{
    for(int i=0;i<size;i++)
    {
       if (int(arr[i].size())>length)
       {
            length=arr[i].size();
       }
       
    }
}

void myRadixSort(std::string* arr, int size, bool ascending, int& iteration_count,int& element)
{
    std::string B[size];
    int* C=new int[27];
    for(int i=0;i<27;i++)
    {
        
        C[i]=0;
    }
    for(int j=0;j<size;j++)
    {
        if(int(arr[j].size())-1>=element)
        {
            iteration_count++;
            C[int(arr[j][element])-64]=C[int(arr[j][element])-64]+1;
        }
        else{
            C[0]=C[0]+1;
            iteration_count++;
        }
    }
    for(int i=1;i<27;i++)
    {
        C[i]=C[i]+C[i-1];
        iteration_count++;
    }
    for(int j=size-1;j>=0;j--)
    {
        if(int(arr[j].size())-1>=element)
        {
            iteration_count++;
            B[C[int(arr[j][element])-64]-1]=arr[j];
            C[int(arr[j][element])-64]=C[int(arr[j][element])-64]-1;
        }
        else{
            iteration_count++;
            B[C[0]-1]=arr[j];
            C[0]=C[0]-1;
        }
        
    }
    if(!ascending &&element==0)
    {
        for(int h=0;h<size;h++)
        {
            iteration_count++;
            arr[size-1-h]=B[h];
        }
        
    }
    else
    {
        for(int h=0;h<size;h++)
        {
            iteration_count++;
            arr[h]=B[h];
        }
    }
    delete C;
}
int radix_string_sort(std::string* arr, int size, bool ascending)
{
    int length=0;
    int iteration_count=0;
    maxlength(arr,size,length);
    for(int i=length-1;i>=0;i--)
    {
    myRadixSort(arr,size,ascending,iteration_count,i);
    }
    
    return iteration_count;
}


int main()
{
    bool ascending=0;
    int size=4;
    std::string aytac[4]={"ALHAJOTH", "ALGOL", "ARCTURUS", "ASTERION"};
    int returnval=radix_string_sort(aytac,size,ascending);
    return 0;
}
