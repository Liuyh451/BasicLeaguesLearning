#include <stdio.h>
// n个数的组合和全排列
int n = 10;
int cnt = 0;         //组合的全部个数
int A[5] = {0};      //要求A容量大于k
int visit[99] = {0}; //要求visit容量大于n
void sort(int A[n], int i, int k)//i初始一律为0，k为n的几组合（挑几个数）
{
    if (i == k)
    {
        for (int j = 0; j < k; j++)
        {
            printf("%d ", A[j]);
        }
        printf("\n");
        cnt++;
        return;
    }
    else
    {
        for (int x = 1; x <= n; x++)
        {
            int m;
            if (i == 0)
            {
                m = 0;
            }
            else
            {
                m = i - 1;
            }
            if (visit[x] == 0 && x >= A[m])//把后面的那个条件去掉就是全排列
            {
                A[i] = x;
                visit[x] = 1;
                sort(A, i + 1, k);
                visit[x] = 0;
            }
        }
    }
}

int main()
{
    /*  Write C code in this online editor and run it. */
    sort(A, 0, 3);
    printf("%d", cnt);

    return 0;
}