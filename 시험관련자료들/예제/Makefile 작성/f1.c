#include <stdio.h>
#include "f1.h"
#include "f2.h"

int
f1(void)
{
    printf("f1\n");
    return f2();
}

int
f1a(void)
{
    printf("f1a\n");
    return 0;
}
