#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *deletem( struct ListNode *L, int m );
void printlist( struct ListNode *L )
{
     struct ListNode *p = L;
     while (p) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("\n");
}

int main()
{
    int m;
    struct ListNode *L = readlist();
    scanf("%d", &m);
    L = deletem(L, m);
    printlist(L);

    return 0;
}

struct ListNode *deletem( struct ListNode *L, int m )
{
    struct ListNode *p=NULL, *q=NULL,*head=L;
    for(q,p=L;p;q=p,p=p->next){
        if(p->data==m){
            if(q){
                q->next=p->next;
                if(q->data==m){
                    head=q->next;
                }
                p=q;
            }else{
                head=p->next;
            }
        }
    }
    return head;
}
