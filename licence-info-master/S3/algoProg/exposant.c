#include <stdio.h>
//	<>
int main(void) {
	int x = 0;
	int n = 0;
	int r = 1;
	printf("x = \n");
	scanf("%d",&x);
	printf("n = \n");
	scanf("%d",&n);

	if (n != 0) 
	{
		while (n != 0) {
			printf("nb\n");
			r *= x;
			n --;
		}
	}
	printf("x^n = %d\n", r);
	return 0;
}