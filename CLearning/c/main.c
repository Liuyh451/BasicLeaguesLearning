#include <stdio.h>
#include <stdlib.h>
typedef  int Position;
typedef  int ElementType;
typedef  struct SNode *PtrToSNode;
struct  SNode {
ElementType  *Data;   /* 存储元素的数组 */
Position  Top;        /* 栈顶指针 */
int  MaxSize;         /* 堆栈最大容量 */
};
typedef  PtrToSNode  Stack;

int IsFull( Stack S )    /* 判断栈是否满 */
{   return (S->Top ==S->MaxSize-1); }

int IsEmpty( Stack S )   /* 判断栈是否空 */
{  return (S->Top ==-1);  }
Stack CreateStack(int MaxSize){
    Stack S;

    S=(Stack)malloc(sizeof(struct SNode));
    S->Data=(ElementType*)malloc(MaxSize*sizeof(ElementType));
    S->Top=-1;
    S->MaxSize=MaxSize;

    return S;
}
void Push(Stack S,ElementType X){
    S->Data[++(S->Top)]= X;

}
ElementType Pop(Stack S){
    int y;
    y=S->Data[(S->Top)--];
       return y;

}

/***********  CreateStack(int MaxSize) 函数 *************/
/***********  Push(Stack S,ElementType x) 函数 ********/
/*****************  Pop(Stack S) 函数 *********************/

int main()    /*  主函数 */
{ Stack S;
  int n,m,i=0,len;
  ElementType x;
  S=CreateStack(5);   /* 栈初始化 */
  while(i<5){
      scanf("%d",&n);

      Push(S,n);
      i++;
  }
  while(i<5){

      printf("%d",Pop(S));

  }

  return 0;
}
