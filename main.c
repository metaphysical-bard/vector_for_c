
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

//↓windowsでscanfのワーニングをとめるやつ
#pragma warning(disable: 4996)

void write_print(vec_M* a) {
	int* p = (int*)a->p;
	printf("vec_M\n");
	printf(" p = %p \n size = %d \n zn = %d \n t = %d \n b = %d \n", a->p, a->size, a->zn, a->t, a->b);
	for (int i = 0; i < a->size; i++) {
		printf(" index = %d → %d\n", i, *(p + i));
	}
	printf("push enter key\n");
	getchar();
}

int main() {
	printf("vec_M test\n");

	int n = 10;

	vec_M* b = create_vec_M(n, sizeof(int));
	if (b == NULL) {
		printf("lost\n");
		printf("push enter key\n");
		getchar();
		return 0;
	}

	int* t = b->p;
	for (int i = 0; i < n; i++) {
		*(t + i) = i;
	}

	printf("要素(10)を表示します\n");
	write_print(b);
	write_print(b);


	printf("要素数を15にしました\n");
	b = resize_vec_M(b, 15);
	t = b->p;
	for (int i = 10; i < 15; i++) *(t + i) = i * 2;
	write_print(b);

	printf("要素の末尾に123を追加します\n");
	int c = 123;
	b = push_back_vec_M(b, (void*)&c);
	write_print(b);

	printf("index13の要素を表示します\n");
	int* prt = (int*)get_vec_M(b, 13);
	printf(" index = 13 → %d\n", *prt);
	getchar();

	printf("index13の値を23にします\n");
	c = 23;
	b = set_vec_M(b, (void*)&c, 13);
	prt = (int*)get_vec_M(b, 13);
	printf(" index = 13 → %d\n", *prt);
	getchar();

	printf("要素のindex10を削除しました\n");
	b = delete_vec_M(b, 10);
	write_print(b);

	free_vec_M(b);
	return 0;
}