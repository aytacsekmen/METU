#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <memory>
#include <iostream>


void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,std::vector<float>& infection_scores)
{
    int size=network.size();
    int distance [size][size];
    int control=0;
    int sub_size;
    int max_value=INT_MIN;
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if(i==j)
            {
                distance[i][j]=0;
                continue;
            }
            distance[i][j]=INT_MAX;
        }
    }
    for (int i = 0; i < size; i++) 
    {
        sub_size=network[i].size();
        for (int j=0;j<sub_size;j++)
        {
            
            distance[i][network[i][j].first]=network[i][j].second;
        }
    }

    for (int k = 0; k < size; k++) 
    {

        for (int i = 0; i < size; i++) 
        {

            for (int j = 0; j < size; j++) 
            {

                if (distance[i][j] > (distance[i][k] + distance[k][j]) && (distance[k][j] != INT_MAX && distance[i][k] != INT_MAX))
                {

                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if(distance[i][j]>max_value&& distance[i][j]!=INT_MAX && i!=j)
            {
                max_value=distance[i][j];
            }
        }
    }
    double toplam=0.0;
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if(i!=j)
            {
                if(distance[i][j]!=INT_MAX)
                {
                    toplam+=distance[i][j];
                }
                else
                {
                    toplam+=max_value+1;
                }
            }
            
            
        }
        double deger=1.0/(toplam/(size-1.0));
        infection_scores.push_back(deger);
        toplam=0.0;
    }
}



int main()
{
                                                             
    std::vector< std::vector<std::pair<int,int> > >matrix={
                                                           { std::make_pair(6,12),std::make_pair(5,11) },                                              
                                                           { std::make_pair(0,8),std::make_pair(7,2),std::make_pair(4,6) },                                              
                                                           { std::make_pair(3,5)},                                              
                                                           { std::make_pair(4,7),std::make_pair(9,14),std::make_pair(6,4) },
                                                           { std::make_pair(7,7)},
                                                           { std::make_pair(2,7),std::make_pair(6,4) },
                                                           { },
                                                           { std::make_pair(6,3) },
                                                           { std::make_pair(9,1),std::make_pair(3,2)},                                              
                                                           { std::make_pair(0,10),std::make_pair(1,9),std::make_pair(3,15) } 
                                                                }; 
    std::vector< float > chain;    
    get_infection_scores(matrix,chain);
    return 0;
}
