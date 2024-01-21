#include "the5.h"
#include <iostream>
// do not add extra libraries here
int color[100];
int starttime[100];
int finishtime[100];
int size;
int toplist[100];
int count;
int control_cyclic;

std::vector<std::vector<int>> mytranspose(const std::vector<std::vector<int>> &b)
{
    std::vector<std::vector<int>> trans_vec(b[0].size(), std::vector<int>());

    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            trans_vec[j].push_back(b[i][j]);
        }
    }
    return trans_vec;
}
void topological_order(std::vector<int>& compileOrder)
{
    for(int i=size-1;i>=0;i--)
    {
        compileOrder.push_back(toplist[i]);
    }
    int i=0;
}
void dfs_visit(const std::vector<std::vector<int>>& dependencyMatrix, bool& isCompilable, std::vector<int>& compileOrder, std::vector<std::vector<int>>& cyclicDependencies,int edge)
{
    int vertex_sayisi=dependencyMatrix.size();
    color[edge]=1;
    
    for(int i=vertex_sayisi-1;i>=0;i--)
    {
        if (dependencyMatrix[edge][i]==1 && edge!=i)
        {
            if(color[i]==0)
            {
                dfs_visit(dependencyMatrix,isCompilable,compileOrder,cyclicDependencies,i);
            }
            else if(color[i]==1)
            {
                //cyclic edge
                isCompilable=false;
            }
        }
        else if(dependencyMatrix[edge][i]==1 && edge==i)
        {
            control_cyclic=1;
        }
    }
    color[edge]=2;
    
    toplist[count]=edge;
    count++;
    
    

}
void run(const std::vector<std::vector<int>>& dependencyMatrix, bool& isCompilable, std::vector<int>& compileOrder, std::vector<std::vector<int>>& cyclicDependencies)
{
    control_cyclic=0;
    count=0;
    isCompilable=true;
    int vertex_sayisi=dependencyMatrix.size();
    size=vertex_sayisi;
    //white 0
    //gray 1
    //black 2

    //-1 =no parent
    for(int i=0;i<vertex_sayisi;i++)
    {
        color[i]=0;
    }
    for(int i=vertex_sayisi-1;i>=0;i--)
    {
        if(color[i]==0)
        {
            dfs_visit(dependencyMatrix,isCompilable,compileOrder,cyclicDependencies,i);
        }
    }
    
    topological_order(compileOrder);
    if(!isCompilable)
    {
        int ara;
        for(int i=0;i<vertex_sayisi;i++)
        {
            color[i]=0;
        }
        std::vector<std::vector<int>> result=mytranspose(dependencyMatrix);
        for(int i=0;i<size;i++)
        {
            ara=compileOrder[i];
            if(color[ara]==0)
            {
                count=0;
                control_cyclic=0;
                dfs_visit(result,isCompilable,compileOrder,cyclicDependencies,ara);
                std::vector<int> aradeger;
                if(count==1 && control_cyclic==0)
                {
                    continue;
                }
                for(int i=count-1;i>=0;i--)
                {
                    aradeger.push_back(toplist[i]);
                }
                cyclicDependencies.push_back(aradeger);
            }
        }
    }
}
int main()
{
                                                             
    std::vector<std::vector<int>>matrix= {                                                           
                        {0, 1, 1, 0, 0, 1, 0, 0, 0},                             
                        {0, 0, 1, 0, 0, 0, 0, 0, 0},                             
                        {0, 0, 0, 0, 0, 0, 1, 0, 0},                             
                        {0, 0, 0, 0, 1, 0, 0, 0, 0},                             
                        {0, 0, 0, 0, 0, 1, 0, 0, 0},                             
                        {0, 0, 0, 1, 0, 0, 0, 1, 0},                             
                        {0, 1, 0, 0, 0, 0, 0, 0, 0},                             
                        {0, 0, 1, 0, 0, 0, 0, 0, 1},                             
                        {0, 0, 0, 0, 0, 0, 0, 0, 1},                                
                        }; 
    std::vector<std::vector<int>>depend;     
    bool isCompilable;
    std::vector<int> compileOrder;
    run(matrix,isCompilable,compileOrder,depend);
    return 0;
}