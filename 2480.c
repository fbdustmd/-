#include <stdio.h>

int main()
{
    int a, b, c, d;
    scanf("%d %d %d", &a, &b, &c);
    if (a == b && b == c) // 셋다 같을경우 
    {
        d = 10000 + a * 1000;
        printf("%d", d);
    }
    if (a == b && b != c) // a==b
    {
        printf("%d", 1000 + b * 100);
    }
    if (c == b && b != a) // b==c
    {
        printf("%d", 1000 + b * 100);
    }
    if (a == c && b != c) // a == c
    {
        printf("%d", 1000 + 100 * a);
    }
    else
    {
        if (a > b && b > c)
        {
            printf("%d", a * 100);
        }
        if (a > c && c > b)
        {
            printf("%d", a * 100);
        }
        if (b > a && a > c)
        {
            printf("%d", b * 100);
        }
        if (b > c && c > a)
        {
            printf("%d", b * 100);
        }
        if (c > a && a > b)
        {
            printf("%d", c * 100);
        }
        if (c > b && b > a)
        {
            printf("%d", c * 100);
        }
    }
    return 0;
}