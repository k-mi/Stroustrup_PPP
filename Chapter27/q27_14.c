#include <stdio.h>
#include <stdlib.h>	/* exit, qsort */
#include <string.h>	/* memcpy */

struct Minmax_res{
	int min;
	int max;
};

/* int型配列の要素から最大値と最小値を求める */
struct Minmax_res minmax(const int* array, int size){
	if(size < 1){
		printf("no elemnts array\n");
		exit(EXIT_FAILURE);
	}

	{
		int i;
		struct Minmax_res res;
		res.min = res.max = array[0];
		for(i = 1; i < size; ++i){
			if(res.min > array[i]) res.min = array[i];
			if(res.max < array[i]) res.max = array[i];
		}

		return res;
	}
}

int compare_ints(const void* a, const void* b){
	int arg1 = *(const int*)a;
	int arg2 = *(const int*)b;

	if(arg1 < arg2) return -1;
	else if(arg1 > arg2) return 1;
	return 0;
}

/* int型配列の要素から中央値を求める */
double median(const int* array, int size){
	if(size < 1){
		printf("no elemnts array\n");
		exit(EXIT_FAILURE);
	}

	{
		int tmp[size];
		int index = (size - 1) / 2;

		memcpy(tmp, array, sizeof(int) * size);
		qsort(tmp, size, sizeof(int), compare_ints);

		if(size % 2 != 0)
			return tmp[index];
		else
			return (tmp[index] + tmp[index+1]) / 2.0;
	}
}

/* int型配列の要素から平均値を求める */
double average(const int* array, int size){
	if(size < 1){
		printf("no elemnts array\n");
		exit(EXIT_FAILURE);
	}

	{
		int i;
		double sum = 0;
		for(i = 0; i < size; ++i) 
			sum += array[i];
		return sum / size;
	}	
}

int main(){
	const int array[] = { 2, 13, 7, 17, 3, 6, 20, 1, 10, 8 };
	const int size = sizeof(array) / sizeof(*array);

	struct Minmax_res res = minmax(array, size);
	printf("min: %d\nmax: %d\n", res.min, res.max);
	printf("med: %g\n", median(array, size));
	printf("ave: %g\n", average(array, size));
}