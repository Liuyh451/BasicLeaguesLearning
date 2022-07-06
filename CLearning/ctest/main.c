#include <stdio.h>
#include <stdlib.h>

int main()
{   int a,b;
    double fx;
    scanf("%d%d",&a,&b);
    for(int i=a;i<=b;i++)
    {
        fx=i*i*i/2.0;
        printf("%f\n",fx);
    }

    return 0;
}
