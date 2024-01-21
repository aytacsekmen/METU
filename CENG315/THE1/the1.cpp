//#include "the1.h"

#include <iostream>

using namespace std;

void myswap(unsigned short* arr, int index1,int index2,long& swap, 
double& avg_dist, double& max_dist)
{
    if(index2<index1)
    {
        int temp=index2;
        index2=index1;
        index1=temp;
    }
    unsigned short temp=arr[index1];
    arr[index1]=arr[index2];
    arr[index2]=temp;

    avg_dist=(avg_dist*swap+index2-index1)/(swap+1);
    
    if(index2-index1>max_dist)
    {
        max_dist=index2-index1;
        
    }
    swap++;
}

//You may write your own helper functions here
int hoare_partitioning(unsigned short* arr,int first, int last, long& swap, 
double& avg_dist, double& max_dist, bool hoare, bool median_of_3,int& call_number)
{
    int size=last-first+1;
    int med=(size-1)/2+first;
    unsigned short pivot_value;
    if(median_of_3 && size>2)
    {
        if (arr[last]>arr[first])
        {
            if(arr[first]>arr[med])
            {
                myswap(arr,med,first,swap,avg_dist,max_dist);
            }
            else if (arr[last]<arr[med])
            {               
                myswap(arr,last,med,swap,avg_dist,max_dist);
            }            
        }
        else if (arr[last]<arr[first])
        {
            if(arr[med]<arr[last])
            {
                myswap(arr,med,last,swap,avg_dist,max_dist);
            }
            
            else if (arr[med]>arr[first])
            { 
                myswap(arr,first,med,swap,avg_dist,max_dist);
            }
        }
    }
    pivot_value=arr[med];
    int big=first-1;
    int small=last+1;
    while (true)
    {

        do { 

            small--;

        } while (arr[small] < pivot_value); 

        do { 
            if(big<last)
            {
            big++;
            } 
        } while ( arr[big] > pivot_value); 
  
        if (big >= small) 
        {
            return small; 
        }

        myswap(arr, big, small,swap,avg_dist,max_dist);
    }

}

int lomuto_partitioning(unsigned short* arr,int first, int last, long& swap, 
double& avg_dist, double& max_dist, bool hoare, bool median_of_3,int& call_number)
{
    int size=last-first+1;
    int med=(size-1)/2+first;
    unsigned short pivot_value;
    if(median_of_3 && size>2)
    {
        if (arr[med]>arr[first])
        {
            if(arr[first]>arr[last])
            {
                myswap(arr,last,first,swap,avg_dist,max_dist);
            }
            else if (arr[last]>arr[med])
            {               
                myswap(arr,last,med,swap,avg_dist,max_dist);
            }            
        }
        else if (arr[med]<arr[first])
        {
            
            if(arr[first]<arr[last])
            {
                myswap(arr,first,last,swap,avg_dist,max_dist);
            }
            else if (arr[med]>arr[last])
            { 
                myswap(arr,last,med,swap,avg_dist,max_dist);
            }
        }
        
    }
    pivot_value=arr[last];
    int big=first-1;
    int small=first;
    for(;small<last;small++)
    {
        if(arr[small]>=pivot_value)
        {
            big++;
            
            myswap(arr,big,small,swap,avg_dist,max_dist);
        }
    }
    
    
    myswap(arr,last,big+1,swap,avg_dist,max_dist);
    return big+1;
}
void myQuickSort(unsigned short* arr,int first, int last, long& swap, 
double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int& call_number)
{
    if(first<last)
    {
        if (hoare)
        {
            int mid_index=hoare_partitioning(arr,first,last,swap,avg_dist,max_dist,hoare,median_of_3,call_number);
            myQuickSort(arr,first,mid_index,swap,avg_dist,max_dist,hoare,median_of_3,call_number);
            call_number++;
            myQuickSort(arr,mid_index+1,last,swap,avg_dist,max_dist,hoare,median_of_3,call_number);
            call_number++;
        }
        else
        {
            int mid_index=lomuto_partitioning(arr,first,last,swap,avg_dist,max_dist,hoare,median_of_3,call_number);
            myQuickSort(arr,first,mid_index-1,swap,avg_dist,max_dist,hoare,median_of_3,call_number);
            call_number++;
            myQuickSort(arr,mid_index+1,last,swap,avg_dist,max_dist,hoare,median_of_3,call_number);
            call_number++;
        }
    }
}

int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){

    int rec_call_number=0;
    swap=0;
    max_dist=0;
    avg_dist=0;
	myQuickSort(arr,0,size-1,swap,avg_dist,max_dist,hoare,median_of_3,rec_call_number);
    rec_call_number++;
    return rec_call_number;
    
}

int main()
{
    unsigned short arr[256]={56090, 61859, 8313, 15142, 54102, 32800, 27732, 25168, 42256, 29073, 57450, 24776, 7481, 37428, 20848, 34825, 16835, 35038, 20576, 61529, 47200, 13079, 22050, 8491, 1427, 6453, 52177, 51590, 19096, 12468, 16837, 42419, 41559, 57918, 57561, 62894, 25183, 19759, 22527, 34671, 16064, 47209, 59447, 23545, 51869, 14760, 25602, 35937, 17031, 46178, 31931, 64231, 59257, 21214, 7187, 27916, 27667, 26596, 46738, 13996, 6296, 63576, 56415, 15087, 23191, 48441, 12446, 48374, 2665, 2206, 17510, 51496, 16647, 44190, 9506, 2982, 58950, 35108, 6151, 43213, 48518, 38082, 41909, 42240, 26528, 16328, 37388, 54196, 42924, 18592, 2657, 49220, 49400, 59072, 31540, 7056, 9210, 43986, 22662, 44643, 13424, 7404, 30604, 30072, 51594, 40111, 286, 12242, 42451, 6437, 55455, 25435, 11751, 31830, 34907, 38280, 48158, 39528, 26941, 58315, 58120, 62365, 9232, 9217, 23134, 40772, 49040, 32344, 19224, 6167, 44219, 65415, 13571, 9289, 29952, 32398, 16632, 30238, 44640, 59083, 3907, 1792, 51750, 15659, 33622, 53890, 21171, 49013, 60650, 15344, 9025, 20467, 44941, 18257, 29684, 2540, 59030, 13189, 2116, 45486, 52123, 46336, 45366, 32926, 22857, 42551, 65324, 39489, 7254, 11661, 269, 43929, 13454, 19252, 26820, 47076, 40374, 47991, 63321, 35489, 30567, 6811, 55956, 9973, 57836, 52872, 12513, 51331, 526, 47396, 64049, 19881, 60964, 11112, 52807, 18286, 53663, 52597, 57775, 60918, 64258, 25277, 39312, 12177, 44529, 33364, 26486, 52135, 15820, 57039, 22089, 46387, 31083, 45277, 56360, 23384, 32614, 36105, 41947, 372, 50733, 40461, 20253, 46163, 51573, 7525, 64449, 6934, 60122, 23922, 2317, 26078, 49199, 8861, 38255, 60960, 42225, 31973, 47560, 25277, 23478, 36881, 38896, 54561, 16623, 62488, 45177, 49237, 290, 21589, 49609, 51023, 29282, 4327, 31651, 48087};
    int size=256;


    bool hoare=false;
    bool median_3=false;
    long swap=0; 
    double avg_dist=0;
    double max_dist=0;
    quickSort(arr,swap,avg_dist,max_dist,hoare,median_3,size);

	cout<<"Number of Swaps: " << swap <<endl;
}