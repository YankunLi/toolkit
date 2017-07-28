#include <stdio.h>

int main(int argc, char *argv[])
{
    int bit = 1;
    printf("size of int type is : %d, address is : %lx\n", sizeof(bit), &bit);

    int a[4];
    int i;
    printf("%lx\n", &i);
    for (i = 0; i < 4; i++) {
        printf("size of int type is : %d, address is : %lx\n", sizeof(a[i]), &a[i]);
    }

    return 0;
}
