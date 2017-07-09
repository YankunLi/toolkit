#include <stdio.h>

typedef struct list{
    int value;
    struct list *next;
} List;

void reserve(List ** ls)
{
    if(!ls)
    {
        printf("ERROR: input is null\n");
        return;
    }
    struct list *it, *temp, *head;
    head = it = *ls;
    if(it && it->next)
    {
        it = it->next;
        head->next = NULL;

        while(it)
        {
            temp = it->next;
            it->next = head;
            head = it;
            it = temp;
        }
        *ls = head;
    }
}

void show(List *ls)
{
    if(!ls)
    {
        printf("ERROR: input is null\n");
        return;
    }

    List *it = ls;

    printf("list value:");
    while(it)
    {
        printf("%d ",it->value);
        it = it->next;
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    struct list *ls = NULL;
    struct list **lss = NULL;

    struct list ls1 = {1, NULL};
    struct list ls2 = {2, NULL};
    struct list ls3 = {3, NULL};

    //empty
    show(ls);
    reserve(lss);

    // single linked list
    ls = &ls1;
    lss = &ls;
    show(*lss);
    reserve(lss);
    show(*lss);

    //linked list
    ls1.next = &ls2;
    ls2.next = &ls3;
    ls3.next = NULL;
    ls = &ls1;
    lss = &ls;
    show(*lss);
    reserve(lss);
    show(*lss);

    return 0;
}
