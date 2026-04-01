#include <stdio.h>

int main()
{
    int a, b, c;
    b = 1;
    scanf("%d", &a);
    while (b <= a)
    {
        printf("%d", b);
        c = b;
        b++;
        c += b;

    }
    printf("%d", &c);
    return 0;
}