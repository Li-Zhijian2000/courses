#include <stdio.h>
#include <string.h>

void error() {
    fprintf(stderr, "error: invalid argument\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        error();
        return 1;
    }
    
    char *op = argv[1];
    int a, b;
    sscanf(argv[2], "%d", &a);
    sscanf(argv[3], "%d", &b);
    
    if (!strcmp(op, "add")) 
        printf("%d + %d = %d\n", a, b, a + b);
    else if (!strcmp(op, "sub"))
        printf("%d - %d = %d\n", a, b, a - b);
    else error();

    return 0;
}