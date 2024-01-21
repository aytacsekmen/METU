#include "the6.h"
#include <iostream>


int find_structure(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) 
{
    int vertex_sayisi=bond_energies.size();
    int parent[vertex_sayisi];
    int key[vertex_sayisi];
    
    // 0 = in queue
    // 1 = not in queue
    int queuechecker[vertex_sayisi];

    std::vector<std::pair<int,int> > thing;
    for(int i=1;i<vertex_sayisi;i++)
    {
        key[i]=INT_MAX;
        parent[i]=-1;
        queuechecker[i]=0;
    }
    
    parent[0]=-1;
    queuechecker[0]=0;
    key[0]=0;
    int control_first=1;
    int total_weight=0;
    int sizedeneme=vertex_sayisi;
    while (sizedeneme!=0)
    {
        int parent_vertex;
        int minkey=INT_MAX;
        for(int i=0;i<vertex_sayisi;i++)
        {
            if(key[i]<minkey &&queuechecker[i]==0)
            {
                minkey=key[i];
                parent_vertex=i;
            }
        }
        if (control_first==0)
        {
            
            int parent_index=parent[parent_vertex];
            int sub_size=bond_energies[parent_index].size();
            int weight;
            for(int i=0;i<sub_size;i++)
            {
                if(bond_energies[parent_index][i].first==parent_vertex)
                {
                weight=bond_energies[parent_index][i].second;
                }
            }
            
            lowest_energy_structure[parent_index].push_back(std::make_pair(parent_vertex,weight));
            total_weight+=weight;
            lowest_energy_structure[parent_vertex].push_back(std::make_pair(parent_index,weight));    
        }
        else
        {
            control_first=0;
        }
        
        
        queuechecker[parent_vertex]=1;
        sizedeneme--;
        int sub_size=bond_energies[parent_vertex].size();

        for(int i=0;i<sub_size;i++)
        {
            int child_vertex=bond_energies[parent_vertex][i].first;
            int child_vertex_weight=bond_energies[parent_vertex][i].second;
            if(queuechecker[child_vertex]==0 && child_vertex_weight<key[child_vertex])
            {
                parent[child_vertex]=parent_vertex;
                key[child_vertex]=child_vertex_weight;
            }
        }
    }
    return total_weight;
    
    
}
int control;
std::pair<int,int> bfs(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain,int vertex)
{
    int vertex_sayisi=molecule_structure.size();
    int color[vertex_sayisi];
    int distance[vertex_sayisi];
    int parent[vertex_sayisi];
    //white 0
    //gray 1
    //black 2

    //-1 =no parent
    for(int i=0;i<vertex_sayisi;i++)
    {
        color[i]=0;
        distance[i]=INT_MAX;
        parent[i]=-1;
    }
    std::queue<int> myqueue;
    color[vertex]=1;
    distance[vertex]=1;
    myqueue.push(vertex);
    int parent_vertex;
    while(!myqueue.empty())
    {
        parent_vertex=myqueue.front();
        myqueue.pop();   
        int sub_size=molecule_structure[parent_vertex].size();
        for(int i=0;i<sub_size;i++)
        {
            int child_vertex=molecule_structure[parent_vertex][i].first;
            if(color[child_vertex]==0)
            {
                color[child_vertex]=1;
                distance[child_vertex]=distance[parent_vertex]+1;
                parent[child_vertex]=parent_vertex;
                myqueue.push(child_vertex);
            }
        }
        color[parent_vertex]=2;
    }
    int maxDis = 0;
    int nodeId;
    for (int i = 0; i < vertex_sayisi; i++)
    {
        if (distance[i] > maxDis)
        {
            maxDis = distance[i];
            nodeId = i;
        }
    }
    if(control==1)
    {
        while (parent[nodeId]!=-1)
        {
            chain.push_back(nodeId);
            nodeId=parent[nodeId];
        }
        chain.push_back(nodeId);
    }
    std::pair<int,int>  returnvalue= std::make_pair(nodeId,maxDis);
    return returnvalue;
}
int find_longest_chain(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain)
{
    int longest_chain_size;
    int vertex=0;
    control=0;
    std::pair<int,int> returnvalue1=bfs(molecule_structure,chain,0);
    control=1;
    std::pair<int,int> returnvalue2=bfs(molecule_structure,chain,returnvalue1.first);
    
    return returnvalue2.second;
}

int main()
{
                                                             
    std::vector< std::vector<std::pair<int,int> > >matrix={
                                                           { std::make_pair(4,1) },                                              
                                                           { std::make_pair(2,1) },                                              
                                                           { std::make_pair(1,1),std::make_pair(3,1),std::make_pair(4,1) },                                              
                                                           { std::make_pair(2,1) },                                              
                                                           { std::make_pair(0,1),std::make_pair(2,1) } 
                                                                }; 
    std::vector< int > chain;    
    int returnval=find_longest_chain(matrix,chain);
    return 0;
}