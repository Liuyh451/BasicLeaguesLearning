#include <stdio.h>
#include <stdlib.h>
typedef  int Position;
typedef  int ElementType;
typedef  struct SNode *PtrToSNode;
struct  SNode {
ElementType  *Data;   /* �洢Ԫ�ص����� */
Position  Top;        /* ջ��ָ�� */
int  MaxSize;         /* ��ջ������� */
};
typedef  PtrToSNode  Stack;

int IsFull( Stack S )    /* �ж�ջ�Ƿ��� */
{   return (S->Top ==S->MaxSize-1); }

int IsEmpty( Stack S )   /* �ж�ջ�Ƿ�� */
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

/***********  CreateStack(int MaxSize) ���� *************/
/***********  Push(Stack S,ElementType x) ���� ********/
/*****************  Pop(Stack S) ���� *********************/

int main()    /*  ������ */
{ Stack S;
  int n,m,i=0,len;
  ElementType x;
  S=CreateStack(5);   /* ջ��ʼ�� */
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
