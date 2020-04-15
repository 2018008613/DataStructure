#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp1;

int n;
int* arr;
int* arr1;
int* tmp;

//merge를 시행해주는 함수
void merge(int* a, int* t, int lp, int rp, int re)
{
	int num = re - lp + 1, le = rp - 1, tp = lp;
	while (lp <= le && rp <= re)
	{
		if (a[lp] > a[rp])
			t[tp++] = a[rp++];
		else
			t[tp++] = a[lp++];
	}
	while (lp <= le)
		t[tp++] = a[lp++];
	while (rp <= re)
		t[tp++] = a[rp++];
	for (int i = re - num + 1;i <= re;i++)
	{
		a[i] = t[i];
		fprintf(fp1, "%d ", a[i]);
	}
	fprintf(fp1, "\n");
}

//recursive형식으로 merge sort 해주는 함수
void rmsort(int* a, int* t, int l, int r)
{
	int c;
	if (l < r)
	{
		c = (l + r) / 2;
		rmsort(a, t, l, c);
		rmsort(a, t, c + 1, r);
		merge(a, t, l, c + 1, r);
	}
}

int Min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

//iterative형식으로 merge sort 해주는 함수
void msort(int* a, int* t, int l, int r)
{
	int now = 2;
	while (1)
	{
		int i = 0;
		for (int i = 0;i < r;i += now)
			merge(a, t, i, (2 * i + now - 1) / 2 + 1, Min(i + now - 1, r));
		if (now >= n)
			break;
		now *= 2;
	}
}

int main()
{
	fp = fopen("input.txt", "r");
	fp1 = fopen("output.txt", "w");
	fscanf(fp, "%d", &n);

	//배열의 크기를 입력받은 뒤 동적할당해준다
	arr = (int*)malloc(sizeof(int)*(n + 1));
	arr1 = (int*)malloc(sizeof(int)*(n + 1));
	tmp = (int*)malloc(sizeof(int)*(n + 1));
	
	//입력한 값을 배열에 넣어주고 출력해준다
	fprintf(fp1, "input :\n");
	for (int i = 0;i < n;i++)
	{
		fscanf(fp, "%d", arr + i);
		arr1[i] = arr[i];
		fprintf(fp1, "%d ", arr[i]);
	}
	//iterative형식으로 merge sorting
	fprintf(fp1, "\n\niterative :\n");
	msort(arr1, tmp, 0, n - 1);

	//recursice 형식으로 merge sorting
	fprintf(fp1, "\nrecursive :\n");
	rmsort(arr, tmp, 0, n - 1);

	//메모리 해제
	free(arr);
	free(arr1);
	free(tmp);
}
