#include <stdio.h>
int main()
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	if (a == b && b == c) { // 셋다 같은경우 
		printf("%d", 10000 + 1000 * a);
		return 0; //  이때 return 0; 을 안넣으면 음 문제생길거같아서 해놓음 
	}
	else if (a == b || b == c || a == c) { // 둘만 같은경우 
		if (a == b) {
			printf("%d", 1000 + a * 100);
		}
		else if (b == c) {
			printf("%d", 1000 + b * 100);
		}
		else {
			printf("%d", 1000 + c * 100);
		}
	}
	else { // 이떄부터는 무조건 셋다 다름 
		if (a > b && a > c) {
			printf("%d", a * 100);
		}
		else if (b > a && b > c) {
			printf("%d", b * 100);
		}
		else {
			printf("%d", c * 100);
		}
	}
}