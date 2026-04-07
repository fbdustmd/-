#include <stdio.h>


int main() {
	int a;
	scanf("%d", &a);
	int line = a * 2 - 1;
	int star = 1;
	int b = 0;
	while (line >= star) {
		while ((line - star) / 2 > b) { // 띄어쓰기
			printf(" ");
			b++;
		}
		b *= 0;
		while (star > b) { // 별
			printf("*");
			b++;
		}
		b *= 0;
		star += 2;
		printf("\n");
	}
	return 0;
}