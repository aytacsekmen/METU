#include <stdio.h>

int main() {
    // your code goes here
    int n;
    int m;
    scanf(" %d",&n);
    scanf(" %d",&m);
    int array_n[n][n];
    int toplam1=0;
    int toplam2=0;
    int control=1;
    int reading;
    int toplam1_size;
    int toplam2_size;
    int toplam1_left_column;
    int toplam2_left_column;
    int toplam1_top_row;
    int toplam2_top_row;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf(" %d",&reading);
            array_n[i][j]=reading;
        }
    }
    //printf("geldim");
    
    for(int i=m;i<=n;i++)
    {
        for(int r=0;r<=n-i;r++)
        {
            for(int c=0;c<=n-i;c++)
            {  
                int r1;
                int c1;
                for (r1=r;r1<r+i;r1++)
                {
                    for (c1=c;c1<c+i;c1++)
                    {  
                        if(control==1)
                        {
                            //printf("okudum");
                            toplam1+=array_n[r1][c1];
                            
                        }
                        else
                        {
                            toplam2+=array_n[r1][c1];
                        }
                    
                    }

                }
                toplam2_left_column=c;
                toplam2_size=i;  
                toplam2_top_row=r;
                if(control)
                {
                toplam1_size=i;
                toplam1_top_row=r;
                toplam1_left_column=c;
                }
                printf("toplam1(%d,%d,%d):%d toplam2(%d,%d,%d):%d \n",toplam1_top_row,toplam1_left_column,toplam1_size, toplam1,toplam2_top_row,toplam2_left_column,toplam2_size, toplam2);
                if(!control)
                {
                    if((toplam2)*(toplam1_size*toplam1_size)>toplam1*(toplam2_size*toplam2_size))
                    {
                        toplam1=toplam2;
                        toplam1_left_column= toplam2_left_column;
                        toplam1_size= toplam2_size;  
                        toplam1_top_row= toplam2_top_row;
                        toplam2=0;
                        control=0;
                    }
                    else if((toplam2)*(toplam1_size*toplam1_size)==toplam1*(toplam2_size*toplam2_size))
                    {
                        if (toplam2_size>toplam1_size)
                        {
                            toplam1_left_column= toplam2_left_column;
                            toplam1_size= toplam2_size;  
                            toplam1_top_row= toplam2_top_row;
                            toplam2=0;
                            control=0;

                        }
                        else if((toplam2_size==toplam1_size) && (toplam1_left_column> toplam2_left_column))
                        {
                            toplam1_left_column= toplam2_left_column;
                            toplam1_size= toplam2_size;  
                            toplam1_top_row= toplam2_top_row;
                            toplam2=0;
                            control=0;
                            
                        }
                        else if(toplam2_size==toplam1_size && toplam1_left_column==toplam2_left_column&&toplam1_top_row >toplam2_top_row)
                        {
                            toplam1_left_column= toplam2_left_column;
                            toplam1_size= toplam2_size;  
                            toplam1_top_row= toplam2_top_row;
                            toplam2=0;
                            control=0;
                        }
                        
                    }
                    else if((toplam2)*(toplam1_size*toplam1_size)<toplam1*(toplam2_size*toplam2_size))
                    {
                        toplam2=0;
                        control=0;
                    }
                }
                toplam2=0;
                control=0;


            }
            
        }
    }


    printf("%d %d %d",toplam1_top_row+1,toplam1_left_column+1,toplam1_size);
    return 0;
    
}
