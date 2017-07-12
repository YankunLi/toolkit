/*
 *Author: Yankun Li <lioveni99@gmail.com>
 *
 *
 */

#include <stdio.h>

#include "file.h"

static char *file_path = "./test_file";

int main(int argc, char *argv[])
{
    int size = 10240;
    resize_file(file_path, size, 1);

    return 0;
}
