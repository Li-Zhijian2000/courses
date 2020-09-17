#include <stdio.h>
int main() {
    int a[19][19];
    int i, j;
    int mark = 0;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 19; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 16; j++) {
            if ((j == 0) && (a[i][j] == a[i][j + 1]) &&
                (a[i][j + 1] == a[i][j + 2]) && (a[i][j + 2] == a[i][j + 3]) &&
                (a[i][j] != 0) && (a[i][j + 4] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else if ((j == 15) && (a[i][j] == a[i][j + 1]) &&
                       (a[i][j + 1] == a[i][j + 2]) &&
                       (a[i][j + 2] == a[i][j + 3]) && (a[i][j] != 0) &&
                       (a[i][j - 1] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else {
                if ((a[i][j] == a[i][j + 1]) && (a[i][j + 1] == a[i][j + 2]) &&
                    (a[i][j + 2] == a[i][j + 3]) && (a[i][j] != 0) &&
                    ((a[i][j - 1] == 0) || (a[i][j + 4] == 0))) {
                    printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                    mark = 1;
                    break;
                }
            }
        }
        if (mark != 0) break;
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            if ((i == 0 && j == 15) || (i == 15 && j == 0)) continue;
            if ((i == 0) && (a[i][j] == a[i + 1][j + 1]) &&
                (a[i + 1][j + 1] == a[i + 2][j + 2]) &&
                (a[i + 2][j + 2] == a[i + 3][j + 3]) && (a[i][j] != 0) &&
                (a[i + 4][j + 4] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else if ((i == 15) && (a[i][j] == a[i + 1][j + 1]) &&
                       (a[i + 1][j + 1] == a[i + 2][j + 2]) &&
                       (a[i + 2][j + 2] == a[i + 3][j + 3]) && (a[i][j] != 0) &&
                       (a[i - 1][j - 1] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else {
                if ((a[i][j] == a[i + 1][j + 1]) &&
                    (a[i + 1][j + 1] == a[i + 2][j + 2]) &&
                    (a[i + 2][j + 2] == a[i + 3][j + 3]) && (a[i][j] != 0) &&
                    ((a[i - 1][j - 1] == 0) || (a[i + 4][j + 4] == 0))) {
                    printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                    mark = 1;
                    break;
                }
            }
        }
        if (mark != 0) break;
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 19; j++) {
            if ((i == 0) && (a[i][j] == a[i + 1][j]) &&
                (a[i + 1][j] == a[i + 2][j]) && (a[i + 2][j] == a[i + 3][j]) &&
                (a[i][j] != 0) && (a[i + 4][j] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else if ((i == 15) && (a[i][j] == a[i + 1][j]) &&
                       (a[i + 1][j] == a[i + 2][j]) &&
                       (a[i + 2][j] == a[i + 3][j]) && (a[i][j] != 0) &&
                       (a[i - 1][j] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else {
                if ((a[i][j] == a[i + 1][j]) && (a[i + 1][j] == a[i + 2][j]) &&
                    (a[i + 2][j] == a[i + 3][j]) && (a[i][j] != 0) &&
                    ((a[i - 1][j] == 0) || (a[i + 4][j] == 0))) {
                    printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                    mark = 1;
                    break;
                }
            }
        }
        if (mark != 0) break;
    }
    for (i = 0; i < 16; i++) {
        for (j = 3; j < 19; j++) {
            if ((i == 0 && j == 3) || (i == 15 && j == 18)) continue;
            if ((i == 0) && (a[i][j] == a[i + 1][j - 1]) &&
                (a[i + 1][j - 1] == a[i + 2][j - 2]) &&
                (a[i + 2][j - 2] == a[i + 3][j - 3]) && (a[i][j] != 0) &&
                (a[i + 4][j - 4] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else if ((i == 15) && (a[i][j] == a[i + 1][j - 1]) &&
                       (a[i + 1][j - 1] == a[i + 2][j - 2]) &&
                       (a[i + 2][j - 2] == a[i + 3][j - 3]) && (a[i][j] != 0) &&
                       (a[i - 1][j + 1] == 0)) {
                printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                mark = 1;
                break;
            } else {
                if ((a[i][j] == a[i + 1][j - 1]) &&
                    (a[i + 1][j - 1] == a[i + 2][j - 2]) &&
                    (a[i + 2][j - 2] == a[i + 3][j - 3]) && (a[i][j] != 0) &&
                    ((a[i - 1][j + 1] == 0) || (a[i + 4][j - 4] == 0))) {
                    printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                    mark = 1;
                    break;
                }
            }
        }
        if (mark != 0) break;
    }

    if (mark == 0) printf("No\n");
    return 0;
}
