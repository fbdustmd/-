#include <stdio.h>

int main()
{
	int a;
	scanf("%d", &a);
	int b = 1;
	int c = 0;
	for (;a >= b;b++) {
		while ((a - b) > c) { // 띄어쓰기 
			printf(" ");
			c++;
		}
		c = 0;
		while (b > c) { // 별 입력
			printf("*");
			c++;
		}
		printf("\n");
		c = 0;
	}
	return 0;
}