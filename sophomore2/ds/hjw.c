#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20
int t1, t2;
typedef struct node {
    char name[M];
    struct node *lchild, *rchild;

} BTNode, *BTNodeptr;
BTNodeptr pos;
BTNodeptr stack1[M], stack2[M];
int top1 = -1, top2 = -1;
void find(BTNodeptr t, char name[]) {
    if (t != NULL) {
        if (strcmp(t->name, name) == 0) {
            pos = t;
            return;
        }

        if (t->lchild != NULL) find(t->lchild, name);
        if (t->rchild != NULL) find(t->rchild, name);
    }
}
BTNodeptr insert(BTNodeptr root, char name1[], char name2[], char name3[]) {
    BTNodeptr p, t;
    if (root == NULL) {
        p = (BTNodeptr)malloc(sizeof(BTNode));
        strcpy(p->name, name1);
        p->lchild = p->rchild = NULL;
        root = p;
        if (strcmp(name2, "NULL") != 0) {
            p = (BTNodeptr)malloc(sizeof(BTNode));
            strcpy(p->name, name2);
            p->lchild = p->rchild = NULL;
            root->lchild = p;
        }
        if (strcmp(name3, "NULL") != 0) {
            p = (BTNodeptr)malloc(sizeof(BTNode));
            strcpy(p->name, name3);
            p->lchild = p->rchild = NULL;
            root->rchild = p;
        }
    } else {
        find(root, name1);
        t = pos;
        if (strcmp(name2, "NULL") != 0) {
            p = (BTNodeptr)malloc(sizeof(BTNode));
            strcpy(p->name, name2);
            p->lchild = p->rchild = NULL;
            t->lchild = p;
        }
        if (strcmp(name3, "NULL") != 0) {
            p = (BTNodeptr)malloc(sizeof(BTNode));
            strcpy(p->name, name3);
            p->lchild = p->rchild = NULL;
            t->rchild = p;
        }
    }
    return root;
}

void preorder1(char name[], BTNodeptr t) {
    if (t != NULL) {
        stack1[++top1] = t;
        if (strcmp(t->name, name) == 0) {
            t1 = top1;
            return;
        }
        preorder1(name, t->lchild);
        preorder1(name, t->rchild);
        top1--;
    }
    printf("top1: %d\n", top1);
}
/*void preorder2(char name[],BTNodeptr t){
if(t!=NULL){
    stack2[++top2]=t;
    if(strcmp(t->name,name)==0){

        t2=top2;
        return ;
    }
    preorder2(name,t->lchild);
    preorder2(name,t->rchild);
    top2--;

}


}*/
int main() {
    BTNodeptr root = NULL;
    char name1[M], name2[M], name3[M];
    int n, i;
    scanf("%d", &n);
    while (n--) {
        scanf("%s%s%s", name1, name2, name3);
        root = insert(root, name1, name2, name3);
    }
    char name_1[M], name_2[M];
    scanf("%s%s", name_1, name_2);
    preorder1(name_1, root);
    // preorder2(name_2, root);
    printf("top1-main: %d", top1);
    /*if(t1==t2){
    for(i=t1-1;i>=0;i--)
    if(strcmp(stack1[i]->name,stack2[i]->name)==0){
            printf("%s %s %d\n",stack1[i]->name,name_1,t1-i);
            printf("%s %s %d\n",stack1[i]->name,name_2,t1-i);
    break;
    }
    }*/

    return 0;
    /*
    6
    wangliang wangguoping wangguoan
    wangguoping wangtian wangguang
    wangguoan wangxiang wangsong
    wangtian wangqinian NULL
    wangxiang wangping NULL
    wangsong wanglong NULL
    wangping wanglong*/
}
