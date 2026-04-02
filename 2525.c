#include <stdio.h>

int main()
{
    int a, b, c, d, e; // a는 시간 b는 분 c 는 조리시간 ( 분단위 ) d는 걍 암거나 
    scanf("%d %d", &a, &b);
    scanf("%d", &c); // a b c 입력 받음 
    b += c;
    if (b >= 60)
    {
        d = b;
        d /= 60;
        a += d;
        b -= 60 * d;
    }
    if (a >= 24)
    {
        a -= 24;
    }
    printf("%d %d", a, b);
    return 0;
}