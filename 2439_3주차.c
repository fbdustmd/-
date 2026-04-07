#include <stdio.h>

int main()
{
	int a;
	scanf("%d", &a);
	int star = 1;
	int b = 0;
	while (a >= star) {
		while ((a - star) > b) { // 띄어쓰기
			printf(" ");
			b++;
		}
		b *= 0;
		while (star > b) { // 별
			printf("*");
			b++;
		}
		b *= 0;
		printf("\n");
		star++;
	}
}