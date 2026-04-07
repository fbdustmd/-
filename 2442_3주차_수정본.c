#include <stdio.h>

int main()
{
	int a;
	scanf("%d", &a);
	int b = 1;
	int c = 0;
	int d = 1;
	for (;a >= b;b++) {
		while ((a - b) > c) { // 띄어쓰기
			printf(" ");
			c++;
		}
		c = 0;
		while (d > c) { // 별
			printf("*");
			c++;
		}
		d += 2;
		c = 0;
		printf("\n");
	}
	return 0;
}