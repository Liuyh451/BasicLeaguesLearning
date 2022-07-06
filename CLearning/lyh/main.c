#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    printf("Enter num:\n");
    scanf("%d",&num);
    if(num<0)
        num=-num;


    printf("%d\n",num);
    system("pause");

    return 0;
}
