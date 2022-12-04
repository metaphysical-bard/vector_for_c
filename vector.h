#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct vec_M {//
	void* p;	//ポインタ
	int size;		//要素数
	int zn;		//実際の要素数(確保している領域)
	int t;		//要素確保の際の区切り
	int b;		//一要素のバイト数
}vec_M;

vec_M* create_vec_M(int n, int b);
vec_M* resize_vec_M(vec_M* a, int n);
vec_M* push_back_vec_M(vec_M* a, void* data);
void* get_vec_M(vec_M* a, int n);
vec_M* set_vec_M(vec_M* a, void* data, int n);
vec_M* set2_vec_M(vec_M* a, void* data);
vec_M* delete_vec_M(vec_M* a, int n);
vec_M* erase_vec_M(vec_M* a, void* data);
vec_M* free_vec_M(vec_M* a);

vec_M* create_vec_M(int n, int b) {
	if (n < 0 || b <= 0) return NULL;
	vec_M* a = (vec_M*)malloc(sizeof(vec_M));
	if (a == NULL) return NULL;
	int zn = n + (16 - n % 16);
	a->p = malloc(zn * b);
	if (a->p == NULL) return free_vec_M(a);
	a->size = n;
	a->zn = zn;
	a->t = 16;
	a->b = b;
	return a;
}

vec_M* resize_vec_M(vec_M* a, int n) {
	if (a == NULL || n < 0) return NULL;
	int zn = n;
	if (n % a->t != 0) zn = zn + (a->t - n % a->t);
	if (a->zn < n || a->zn > zn) {
		void* p = realloc(a->p, zn * a->b);
		if (p == NULL) return free_vec_M(a);
		a->p = p;
		a->zn = zn;
	}
	a->size = n;
	return a;
}

vec_M* push_back_vec_M(vec_M* a, void* data) {
	if (a == NULL) return NULL;
	if (data == NULL) return free_vec_M(a);
	if (a->zn <= a->size) {
		a = resize_vec_M(a, a->size + 1);
		if (a == NULL) return free_vec_M(a);
	}
	else {
		a->size++;
	}
	char* c = (char*)data;
	char* p = (char*)a->p;
	p = p + (a->size - 1) * a->b;
	for (int i = 0; i < a->b; i++) {
		*(p + i) = *(c + i);
	}
	return a;
}

void* get_vec_M(vec_M* a, int n) {
	if (a == NULL) return NULL;
	if (n < 0 || n >= a->size) return (void*)free_vec_M(a);
	char* c = (char*)a->p;
	void* b = (void*)(c + n * a->b);
	return b;
}

vec_M* set_vec_M(vec_M* a, void* data, int n) {
	if (a == NULL) return NULL;
	if (n < 0 || n >= a->size || data == NULL) return free_vec_M(a);
	char* c = (char*)data;
	char* p = (char*)a->p;
	p = p + n * a->b;
	for (int i = 0; i < a->b; i++) {
		*(p + i) = *(c + i);
	}
	return a;
}

vec_M* set2_vec_M(vec_M* a, void* data) {
	if (a == NULL) return NULL;
	if (data == NULL) return free_vec_M(a);
	char* c = (char*)data;
	char* p = (char*)a->p;
	int i, j, ix;
	for (i = 0; i < a->size; i++) {
		ix = i * a->b;
		for (j = 0; j < a->b; j++) {
			if (*(p + ix) != *(c + j)) {
				break;
			}
			ix++;
		}
		if (j == a->b) break;
	}
	if (i == a->size) a = push_back_vec_M(a, data);
	return a;
}

vec_M* delete_vec_M(vec_M* a, int n) {
	int ix = n * a->b;
	int ixn = ix + a->b;
	char* p = (char*)a->p;
	for (int i = 0; i < (a->size - n) * a->b; i++) {
		*(p + ix + i) = *(p + ixn + i);
	}
	return  resize_vec_M(a, a->size - 1);
}

vec_M* erase_vec_M(vec_M* a, void* data) {
	if (a == NULL) return NULL;
	if (data == NULL) return free_vec_M(a);
	char* c = (char*)data;
	char* p = (char*)a->p;
	int i, j, ix;
	for (i = 0; i < a->size; i++) {
		ix = i * a->b;
		for (j = 0; j < a->b; j++) {
			if (*(p + ix) != *(c + j)) {
				break;
			}
			ix++;
		}
		if (j == a->b) {
			a = delete_vec_M(a, i);
			i--;
		}
	}
	return a;
}

vec_M* free_vec_M(vec_M* a) {
	free(a->p);
	free(a);
	return NULL;
}