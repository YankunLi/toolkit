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

    struct stu {
    char sex;
    int length;
    char name[10];
    };
    struct stu my_stu;

    printf("the size of struct stu is %d\n", sizeof(struct stu));
    printf("variable of struct stu address is : %lx\n \
            attribute char address is : %lx\n \
            attribute char [] address is %lx\n \
            attribute int address is %lx\n ", \
            &my_stu, &my_stu.sex, my_stu.name, &my_stu.length);

    struct stu1 {
    char sex;
    char name[10];
    int length;
    };
    struct stu my_stu1;

    printf("the size of struct stu1 is %d\n", sizeof(struct stu1));
    printf("variable of struct stu1 address is : %lx\n \
            attribute char address is : %lx\n \
            attribute char [] address is %lx\n \
            attribute int address is %lx\n ", \
            &my_stu1, &my_stu1.sex, my_stu1.name, &my_stu1.length);

    struct st1 {
    char a;
    int b;
    short c;
    };
    struct st1 ss1;
    printf("the size of struct st1 is %d\n", sizeof(struct st1));
    printf("variable of struct st1 address is : %lx\n \
            attribute char address is : %lx\n \
            attribute int address is %lx\n \
            attribute short address is %lx\n ", \
            &ss1, &ss1.a, &ss1.b, &ss1.c);



    return 0;
}
