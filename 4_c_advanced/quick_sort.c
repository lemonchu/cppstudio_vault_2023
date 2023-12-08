#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 20
#define TEST_REPEAT 5

void Swap(int *a, int i, int j);
int Rearrange(int *a, int l, int r);
void Quicksort(int *a, int l, int r);

void InitArray(int *a, int n);
void PrintArray(int *a, int n);
void TestSorted(int *a, int n);

int main() {
    srand(time(0));
    int a[ARRAY_LEN];
    for (int i = 0; i < TEST_REPEAT; i++) {
	InitArray(a, ARRAY_LEN);
	PrintArray(a, ARRAY_LEN);
	Quicksort(a, 0, ARRAY_LEN - 1);
	PrintArray(a, ARRAY_LEN);
	TestSorted(a, ARRAY_LEN);
    }
}

void InitArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
	a[i] = rand() % 100;
    }
}

void PrintArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
	printf("%d ", a[i]);
    }
    printf("\n");
}

void TestSorted(int *a, int n) {
    for (int i = 1; i < n; i++) {
	if (a[i - 1] > a[i]) {
	    printf("Unsorted! --------------------------\n");
	    return;
	}
    }
    printf("Sorted! ------------------------\n");
}

void Swap(int *a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int Rearrange(int *a, int l, int r) {
    //TODO
}

void Quicksort(int *a, int l, int r) {
    //TODO
}

