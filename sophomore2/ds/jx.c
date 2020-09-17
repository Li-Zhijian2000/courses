//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 32

struct tnode {  // Huffman���ṹ
    char c;
    int weight;  //���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
    struct tnode *left, *right;
};
int Ccount[128] = {0};  //���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ���
struct tnode *Root = NULL;  // Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE] = {
    {0}};  //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ��
int Step = 0;  //ʵ�鲽��
FILE *Src, *Obj;

void statCount();  //����1��ͳ���ļ����ַ�Ƶ��
void createHTree();  //����2������һ��Huffman�������ڵ�ΪRoot
void makeHCode();  //����3������Huffman������Huffman����
void atoHZIP();  //����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();                 //�������1�Ľ��
void print2(struct tnode *p);  //�������2�Ľ��
void print3();                 //�������3�Ľ��
void print4();                 //�������4�Ľ��

int main() {
    if ((Src = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if ((Obj = fopen("output.txt", "w")) == NULL) {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step);  //���뵱ǰʵ�鲽��

    statCount();  //ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
    (Step == 1) ? print1() : 1;  //���ʵ�鲽��1���
    createHTree();  //ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
    (Step == 2) ? print2(Root) : 2;  //���ʵ�鲽��2���
    makeHCode(Root);  //ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
    (Step == 3) ? print3() : 3;  //���ʵ�鲽��3���
    (Step >= 4) ? atoHZIP(),
        print4() : 4;  //ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���

    fclose(Src);
    fclose(Obj);

    return 0;
}

void statCount() {
    char c;
    while (~scanf("%c", &c)) {
        if (c != '\n') Ccount[c]++;
    }
    Ccount[0] = 1;
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ
void cmp(struct tnode **basket, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (basket[j + 1]->weight < basket[j]->weight ||
                (basket[j + 1]->weight == basket[j]->weight &&
                 basket[j + 1]->c < basket[j]->c)) {
                struct tnode *tmp;
                tmp = basket[j];
                basket[j] = basket[j + 1];
                basket[j + 1] = tmp;
            }
        }
    }
}
int change(struct tnode **b, int n, struct tnode *tmp) {
    if (n == 2) {
        b[0] = tmp;
        return 1;
    } else {
        int i;
        for (i = 0; i + 2 < n; i++) b[i] = b[i + 2];
        n -= 2;
        if (tmp->weight < b[0]->weight) {
            for (i = n - 1; i > 0; i--) {
                b[i] = b[i - 1];
            }
            b[0] = tmp;
        } else if (tmp->weight >= b[n - 1]->weight) {
            b[n] = tmp;
        } else {
            for (i = n - 1; i > 0; i--) {
                if (tmp->weight >= b[i - 1]->weight &&
                    tmp->weight < b[i]->weight) {
                    int j;
                    for (j = n; j > i; j--) {
                        b[j] = b[j - 1];
                    }
                    b[i] = tmp;
                }
            }
        }
        return (n + 1);
    }
}
void createHTree() {
    int i, j = 0;
    struct tnode *p, *basket[128];
    for (i = 0; i < 128; i++)
        if (Ccount[i] > 0) {
            p = (struct tnode *)malloc(sizeof(struct tnode));
            p->c = i, p->weight = Ccount[i];
            p->left = p->right = NULL;
            basket[j++] = p;
        }
    cmp(basket, j);
    while (j > 1) {
        struct tnode *tmp;
        tmp = (struct tnode *)malloc(sizeof(struct tnode));
        tmp->weight = basket[0]->weight + basket[1]->weight;
        tmp->left = basket[0], tmp->right = basket[1];
        j = change(basket, j, tmp);  //ɾ��0��1,����tmp
    }
    Root = basket[0];
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ
void visitHTree(struct tnode *p, char *code, int i) {
    if (p->left == NULL && p->right == NULL) {
        code[i] = '\0';
        strcpy(HCode[p->c - '\0'], code);
        return;
    }
    if (p->left != NULL) {
        code[i] = '0';
        visitHTree(p->left, code, i + 1);
    }
    if (p->right != NULL) {
        code[i] = '1';
        visitHTree(p->right, code, i + 1);
    }
}
void makeHCode() {
    char code[MAXSIZE];
    visitHTree(Root, code, 0);
}

void atoHZIP() {
    char s[10000], c;
    int i, sl = 0;
    fseek(Src, 0L, SEEK_SET);
    while (~(c = fgetc(Src))) {
        if (c != '\n') {
            strcat(s, HCode[c - '\0']);
            sl += strlen(HCode[c - '\0']);
        }
    }
    strcat(s, HCode[0]);
    while (sl % 8 != 0) s[sl++] = '0';

    for (i = 0; s[i] != '\0'; i++) {
        unsigned char hc = (hc << 1) + (s[i] - '0');
        if ((i + 1) % 8 == 0) {
            fputc(hc, Obj);
            printf("%x", hc);
        }
    }
}

//��ʵ�鲽��4������

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

    printf("\nԭ�ļ���С��%ldB\n", in_size);
    printf("ѹ�����ļ���С��%ldB\n", out_size);
    printf("ѹ���ʣ�%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
