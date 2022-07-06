#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
int fun(int x,int y)
{   int z;
    if (x==0&&y==0)
    {
        z=0;
    }
    else
    {
        z=1;
    }
    return z;
}

int main()
{   int sum=0;
srand((unsigned)time(NULL));
    for(int w=0;w<1000;w++)
{

    int i,j,n,m,l,p,c=0,d=0,e=0,f=0,g=0,h=0,k=0;
    n=rand()%10+1;
    cout<<n<<endl;

    int a[n][n],b[n][n];

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
            a[i][j]=m;
        }
    }
     for(l=0;l<n;l++)
    {
        for(i=0;i<n;i++)
        {
            if(a[i][l]==1)
            {
                for (p=0;p<n;p++)
                {
                   a[i][p]=a[i][p]+a[l][p];
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]!=0)
            {
                a[i][j]=1;
            }
            else
            {
              g++;
            }
            b[j][i]=a[i][j];

            cout<<a[i][j];

    }
    cout<<endl;
    }
    cout<<endl;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            b[i][j]=fun(b[i][j],a[i][j]);
            if(b[i][j]==0)
            {
                h++;
            }
            if(b[i][j]==1&&i!=j)
            {
                k++;
            }
            cout<<b[i][j];
        }
        cout<<endl;
    }
    if(g==0)
    {
        c++;
        d++;
    }
    if(h==0)
    {
        e++;
    }
    if(k==n*(n-1))
    {
        f++;
    }
    if(c+d+e+f>0)
    {
        sum++;
    }
cout<<sum<<endl;
cout<<c<<d<<e<<f<<endl;


}
cout<<sum<<endl;
    return 0;
}
