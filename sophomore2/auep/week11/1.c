#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *env_name = "STUDENT_ID";
    printf("$%s = %s\n", env_name, getenv(env_name));

    return 0;
}