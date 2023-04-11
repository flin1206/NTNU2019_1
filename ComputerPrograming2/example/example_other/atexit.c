#include <stdio.h>
#include <stdlib.h>

void foo(void)
{
    printf("Goodbye Foo!\n");
}

void bar(void)
{
    printf("Goodbye Bar!\n");
}

int main(int argc, wchar_t* argv[])
{
    atexit(bar);
    atexit(foo);
    return 0;
}
