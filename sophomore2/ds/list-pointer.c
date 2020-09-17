//锟侥硷拷压锟斤拷-Huffman实锟斤拷
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 32

struct tnode {  // Huffman锟斤拷锟结构
    char c;
    int weight;  //锟斤拷锟节碉拷权锟截ｏ拷叶锟节碉拷为锟街凤拷锟斤拷锟斤拷锟侥筹拷锟街达拷锟斤拷
    struct tnode *left, *right;
};
int Ccount[128] = {
    0};  //锟斤拷锟矫匡拷锟斤拷址锟斤拷某锟斤拷执锟斤拷锟斤拷锟斤拷锟紺count[i]锟斤拷示ASCII值为i锟斤拷锟街凤拷锟斤拷锟街达拷锟斤拷
struct tnode *Root = NULL;  // Huffman锟斤拷锟侥革拷锟节碉拷
char HCode[128][MAXSIZE] = {
    {0}};  //锟街凤拷锟斤拷Huffman锟斤拷锟诫，锟斤拷HCode['a']为锟街凤拷a锟斤拷Huffman锟斤拷锟诫（锟街凤拷锟斤拷锟斤拷式锟斤拷
int Step = 0;  //实锟介步锟斤拷
FILE *Src, *Obj;

void statCount();  //锟斤拷锟斤拷1锟斤拷统锟斤拷锟侥硷拷锟斤拷锟街凤拷频锟斤拷
void createHTree();  //锟斤拷锟斤拷2锟斤拷锟斤拷锟斤拷一锟斤拷Huffman锟斤拷锟斤拷锟斤拷锟节碉拷为Root
void makeHCode();  //锟斤拷锟斤拷3锟斤拷锟斤拷锟斤拷Huffman锟斤拷锟斤拷锟斤拷Huffman锟斤拷锟斤拷
void atoHZIP();  //锟斤拷锟斤拷4锟斤拷锟斤拷锟斤拷Huffman锟斤拷锟诫将指锟斤拷ASCII锟斤拷锟侥憋拷锟侥硷拷转锟斤拷锟斤拷Huffman锟斤拷锟侥硷拷

void print1();  //锟斤拷锟斤拷锟斤拷锟�1锟侥斤拷锟�
void print2(struct tnode *p);  //锟斤拷锟斤拷锟斤拷锟�2锟侥斤拷锟�
void print3();  //锟斤拷锟斤拷锟斤拷锟�3锟侥斤拷锟�
void print4();  //锟斤拷锟斤拷锟斤拷锟�4锟侥斤拷锟�

int main() {
    if ((Src = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if ((Obj = fopen("output.txt", "w")) == NULL) {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step);  //锟斤拷锟诫当前实锟介步锟斤拷

    statCount();  //实锟介步锟斤拷1锟斤拷统锟斤拷锟侥硷拷锟斤拷锟街凤拷锟斤拷锟街达拷锟斤拷锟斤拷频锟绞ｏ拷
    (Step == 1) ? print1() : 1;  //锟斤拷锟绞碉拷椴斤拷锟�1锟斤拷锟�
    createHTree();  //实锟介步锟斤拷2锟斤拷锟斤拷锟斤拷锟街凤拷频锟斤拷锟斤拷锟斤拷锟斤拷应锟斤拷Huffman锟斤拷
    (Step == 2) ? print2(Root) : 2;  //锟斤拷锟绞碉拷椴斤拷锟�2锟斤拷锟�
    makeHCode(
        Root);  //实锟介步锟斤拷3锟斤拷锟斤拷锟斤拷Root为锟斤拷锟侥革拷锟斤拷Huffman锟斤拷锟斤拷锟斤拷锟斤拷应Huffman锟斤拷锟斤拷
    (Step == 3) ? print3() : 3;  //锟斤拷锟绞碉拷椴斤拷锟�3锟斤拷锟�
    (Step >= 4)
        ? atoHZIP(),
        print4()
        : 4;  //实锟介步锟斤拷4锟斤拷锟斤拷Huffman锟斤拷锟斤拷锟斤拷锟斤拷压锟斤拷锟侥硷拷锟斤拷锟斤拷锟斤拷锟绞碉拷椴斤拷锟�4锟斤拷锟�

    fclose(Src);
    fclose(Obj);

    return 0;
}

//锟斤拷实锟介步锟斤拷1锟斤拷锟斤拷始

char s[1000];

void statCount() {
    Ccount[0] = 1;
    char c;
    while ((c = fgetc(Src)) != EOF) {
        if (c == '\n') continue;
        s[n1++] = c;
        Ccount[c]++;
    }
    s[n1] = '\0';
}

//锟斤拷实锟介步锟斤拷1锟斤拷锟斤拷锟斤拷

//锟斤拷实锟介步锟斤拷2锟斤拷锟斤拷始

int cmp(const void *p1, const void *p2) {
    struct tnode **P1 = (struct tnode **)p1;
    struct tnode **P2 = (struct tnode **)p2;
    if ((*P1)->weight != (*P2)->weight) return ((*P1)->weight - (*P2)->weight);
    return ((*P1)->c - (*P2)->c);
}

void createHTree() {
    struct tnode *All[128] = {NULL};
    int n1 = 0, n2 = 0;
    while (n1 < 128) {
        if (Ccount[n1] > 0) {
            struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
            p->c = n1;
            p->weight = Ccount[n1];
            p->left = NULL;
            p->right = NULL;
            All[n2++] = p;
        }
        n1++;
    }
    qsort(All, n2, sizeof(struct tnode *), cmp);
    int n3 = 0, n4 = 0;
    while (n2 > 2) {
        struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
        p->c = 127;
        p->weight = All[0]->weight + All[1]->weight;
        p->left = All[0];
        p->right = All[1];
        for (n3 = 2; n3 < n2; n3++) {
            All[n3 - 2] = All[n3];
        }
        for (n3 = 0; All[n3]->weight <= p->weight && n3 <= n2 - 3; n3++)
            ;
        for (n4 = n2 - 3; n4 >= n3; n4--) {
            All[n4 + 1] = All[n4];
        }
        All[n3] = p;
        n2--;
    }
    Root = (struct tnode *)malloc(sizeof(struct tnode));
    Root->c = '0';
    Root->weight = All[0]->weight + All[1]->weight;
    Root->left = All[0];
    Root->right = All[1];
}


void traverse(char code[], struct tnode *p) {
    char code1[128];
    char code2[128];
    strcpy(code2, code);
    strcpy(code1, code);
    if (p->left == NULL && p->right == NULL) {
        strcpy(HCode[p->c], code);
        return;
    }
    if (p->left != NULL) traverse(strcat(code1, "0"), p->left);
    if (p->right != NULL) traverse(strcat(code2, "1"), p->right);
    return;
}

void makeHCode() {
    char code[128] = {'\0'};
    traverse(code, Root);
}

//锟斤拷实锟介步锟斤拷3锟斤拷锟斤拷锟斤拷

//锟斤拷实锟介步锟斤拷4锟斤拷锟斤拷始

void atoHZIP() {
    int n1 = 0, i = 0, count = 0;
    unsigned char hc = '\0';
    while (1) {
        for (; HCode[s[i]][n1] != '\0' && count < 8; n1++, count++) {
            if (count != 0) hc = hc << 1;
            if (HCode[s[i]][n1] == '1') {
                hc++;
            }
            // printf("c:%c count%d:%x\n",s[i],count,hc);
        }
        if (count == 8) {
            fputc(hc, Obj);
            printf("%x", hc);
            hc = '\0';
            count = 0;
        }
        if (HCode[s[i]][n1] == '\0') {
            i++;
            n1 = 0;
            if (s[i] == '\0') break;
        }
    }
    for (; HCode[s[i]][n1] != '\0' && count < 8; n1++, count++) {
        if (count != 0) hc = hc << 1;
        if (HCode[s[i]][n1] == '1') {
            hc++;
        }
    }
    if (count == 8) {
        fputc(hc, Obj);
        printf("%x", hc);
        hc = '\0';
        count = 0;
    }
    if (HCode[0][n1] == '\0' && count < 8) {
        for (; count < 8; count++) {
            hc = hc << 1;
        }
        // printf("%x\n",hc);
    }
}

//锟斤拷实锟介步锟斤拷4锟斤拷锟斤拷锟斤拷

void print1() {
    int i;
    printf("NUL:1\n");
    for (i = 1; i < 128; i++)
        if (Ccount[i] > 0) printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p) {
    if (p != NULL) {
        if ((p->left == NULL) && (p->right == NULL)) switch (p->c) {
                case 0:
                    printf("NUL ");
                    break;
                case ' ':
                    printf("SP ");
                    break;
                case '\t':
                    printf("TAB ");
                    break;
                case '\n':
                    printf("CR ");
                    break;
                default:
                    printf("%c ", p->c);
                    break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3() {
    int i;

    for (i = 0; i < 128; i++) {
        if (HCode[i][0] != 0) {
            switch (i) {
                case 0:
                    printf("NUL:");
                    break;
                case ' ':
                    printf("SP:");
                    break;
                case '\t':
                    printf("TAB:");
                    break;
                case '\n':
                    printf("CR:");
                    break;
                default:
                    printf("%c:", i);
                    break;
            }
            printf("%s\n", HCode[i]);
        }
    }
}

void print4() {
    long int in_size, out_size;

    fseek(Src, 0, SEEK_END);
    fseek(Obj, 0, SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);

    printf("\n原锟侥硷拷锟斤拷小锟斤拷%ldB\n", in_size);
    printf("压锟斤拷锟斤拷锟侥硷拷锟斤拷小锟斤拷%ldB\n", out_size);
    printf("压锟斤拷锟绞ｏ拷%.2f%%\n",
           (float)(in_size - out_size) * 100 / in_size);
}
