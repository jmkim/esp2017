#include <stdio.h>
#include "f2.h"
#include "f1.h"

int
f2(void)
{
    printf("f2\n");
    return f1a();
}
