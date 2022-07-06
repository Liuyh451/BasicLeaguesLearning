#include<stdio.h>
#include <stdbool.h>
#include <time.h>
int max,n,depth=0;
#define max 25
int G[max][max];
bool vis[max]={false};
int main()
    {int sum=0;
    double p;
   srand((unsigned)time(NULL));
   for(int w=0;w<10000;w++)
   {

        void dfs(int u,int depth);

     int i,j;

    int n,m;
    n=rand()%10+1;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {   m=rand();
        if(m%2==0)
        {
            m=0;
        }
        else
        {
            m=1;
        }

            G[i][j]=m;
        if(i==j)
        {
            G[i][j]=0;
        }
             printf("%d", G[i][j]);
        }
         printf("\n");

    }
    dfs(1,1);
    int k=0;
    for(i=1;i<=n;i++)
        {
		if(vis[i]==false)k=1;
        }
	if(k)
    {
        printf("这个图是不连通的\n");

    }
	else
    {
        printf("这个图是连通的\n");
        sum++;
    }
   }
   p=sum/10000.0;
   printf("%d\n",sum);
     printf("连通的概率为%.3f\n", p);
	return 0;
}

void dfs(int u,int depth)
{
	vis[u] = true;
	for(int v=1;v<=n;v++)
        {
		if(vis[v]==false&&G[u][v]==1)dfs(v,depth++);
	}
}


