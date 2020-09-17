#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int lc,mc,rc;
    int prenum;
    int depth;
    int childnum;
    int index;
}Tnode;

Tnode tree[120];
int order=1;

void create_tree(){
    int i,num,child[3],sum=0;
    scanf("%d",&num);
    for(i=0;i<3;i++){
        scanf("%d",&child[i]);
        if(child[i]!=0)
            sum++;
    }
    tree[num].index=num;
    tree[num].lc=child[0];
    tree[num].mc=child[1];
    tree[num].rc=child[2];
    tree[num].childnum=sum;
}

void preorder(int num){
    if(num==0)
        return ;
    if(num!=0)
        tree[num].prenum=order++;
    preorder(tree[num].lc);
    preorder(tree[num].mc);
    preorder(tree[num].rc);
}

void BFS(){
    int front=0,rear=-1;
    int queue[120],t;
    queue[front++]=1;
    tree[1].depth=1;
    while(rear<front-1){
        t=queue[++rear];
        if(tree[t].lc!=0){
            queue[front++]=tree[t].lc;
            tree[tree[t].lc].depth=tree[t].depth+1;
        }
        if(tree[t].mc!=0){
            queue[front++]=tree[t].mc;
            tree[tree[t].mc].depth=tree[t].depth+1;
        }
        if(tree[t].rc!=0){
            queue[front++]=tree[t].rc;
            tree[tree[t].rc].depth=tree[t].depth+1;
        }
    }
}
/*
int cmp(const void*a,const void*b){
    Tnode *a1=(Tnode*)a;
    Tnode *b1=(Tnode*)b;
    if(a1->childnum==b1->childnum){
        if(a1->depth==b1->depth)
            return a1->prenum-b1->prenum;
        return b1->depth-a1->depth;
    }
    return b1->childnum-a1->childnum;
}
*/
int cmp(const void*a,const void*b){
    Tnode *a1=(Tnode*)a;
    Tnode *b1=(Tnode*)b;
    return a1->childnum != b1->childnum
        ? -a1->childnum + b1->childnum
        : a1->depth != b1->depth
        ? -a1->depth + b1->depth
        : a1->prenum - b1->prenum;
}

int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        create_tree();
    }
    preorder(1);
    BFS();
    qsort(tree+1,100,sizeof(Tnode),cmp);
    printf("%d %d\n",tree[1].index,tree[1].prenum);
    for(i=2;i<=100;i++){
        if(tree[i].depth==tree[1].depth&&tree[i].childnum==tree[1].childnum)
            printf("%d %d\n",tree[i].index,tree[i].prenum);
        else break;
    }
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define M 110
// int arr[123][4], deep[123];
// typedef struct node {
//     int num, div;
//     struct node *lchild, *mchild, *rchild;

// } TNode, *TREE;
// TREE p[123];
// int maxd = 0, time = 0, maxdep = 0;
// int DIV(int i, int a[][4]) {
//     return ((a[i][1] != 0) + (a[i][2] != 0) + (a[i][3] != 0));
// }

// void depth(TREE root) {
//     TREE queue[123];
//     int front = 0, back = 0;
//     queue[back++] = root;
//     deep[root->num] = 0;

//     while (front < back) {
//         TREE p = queue[front++];
//         int cur_deep = deep[p->num] + 1;
//         if (p->lchild) {
//             queue[back++] = p->lchild;
//             deep[p->lchild->num] = cur_deep;
//         }
//         if (p->mchild) {
//             queue[back++] = p->mchild;
//             deep[p->mchild->num] = cur_deep;
//         }
//         if (p->rchild) {
//             queue[back++] = p->rchild;
//             deep[p->rchild->num] = cur_deep;
//         }
//     }
// }

// // 遍历的次序
// int idx = 0;
// void preorder(TREE T, int mv, int md) {
//     if (!T) return;

//     idx++;
//     if (T->div == mv && deep[T->num] == md) {
//         printf("%d %d\n", T->num, idx);
//     }
//     preorder(T->lchild, mv, md);
//     preorder(T->mchild, mv, md);
//     preorder(T->rchild, mv, md);
// }

// int main() {
//     int i, n, d, root;
//     TREE T;

//     for (i = 1; i < 123; i++) {
//         p[i] = (TREE)malloc(sizeof(TNode));
//         p[i]->num = i;
//         p[i]->div = 0;
//         p[i]->lchild = p[i]->mchild = p[i]->rchild = NULL;
//     }
//     scanf("%d", &n);
//     scanf("%d", &root);
//     scanf("%d%d%d", &arr[root][1], &arr[root][2], &arr[root][3]);
//     d = DIV(root, arr);
//     p[root]->div = d;
//     n--;
//     while (n--) {
//         scanf("%d", &i);
//         scanf("%d%d%d", &arr[i][1], &arr[i][2], &arr[i][3]);
//         d = DIV(i, arr);
//         p[i]->div = d;
//     }

//     T = p[root];
//     for (i = 1; i <= 100; i++) {
//         if (arr[i][1] != 0) p[i]->lchild = p[arr[i][1]];
//         if (arr[i][2] != 0) p[i]->mchild = p[arr[i][2]];
//         if (arr[i][3] != 0) p[i]->rchild = p[arr[i][3]];
//     }
//     depth(T);

//     int max_div = 0;
//     for (int i = 1; i <= 100; i++) {
//         if (max_div < p[i]->div) max_div = p[i]->div;
//     }
//     int max_depth = 0;
//     for (int i = 1; i <= 100; i++) {
//         if (p[i]->div == max_div && deep[p[i]->num] > max_depth)
//             max_depth = deep[p[i]->num];
//     }
//     preorder(T, max_div, max_depth);

//     return 0;
// }
