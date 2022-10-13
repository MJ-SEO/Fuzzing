#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

int rand_len = 0;

int*
shellsort(int* arr, int size){

	int* sorted_elems = (int*)malloc(sizeof(int) * size);

	for(int i=0; i<size; i++){
		sorted_elems[i] = arr[i];
	}
	
	int gaps[] = {701, 301, 132, 57, 23 ,10, 4, 1};
	
	for(int i=0; i<8; i++){
		int gap = gaps[i];
		for(int j = gap; j<size; j++){
			int temp = sorted_elems[j];
			int k = j;
			while(k >= gap && sorted_elems[k-gap] > temp){
				sorted_elems[k] = sorted_elems[k - gap];
				k -= gap;
			}
			sorted_elems[k] = temp;
		}
	}
	return sorted_elems;
}	

int cmp(int* arr1, int* arr2, int size){
	for(int i=0; i<size; i++){
		if(arr1[i] != arr2[i]) return 0;
	}
	return 1;
}

int
is_sorted(int* arr, int size){
	for(int i=0; i<size-1; i++){
		if(arr[i] > arr[i+1]) return 0;
	}
	return 1;
}

int count(int* arr, int target, int size){
	int c = 0;
	for(int i=0; i<size; i++){
		if(target == arr[i]) c++;
	}
	return c;
}	

int 
is_permutation(int* arr1, int size1, int* arr2, int size2){
	int len_check = 0;
	int dup_check = 1;
	if(size1 == size2) len_check = 1;

	for(int i=0; i<size1; i++){
		if(count(arr1, arr1[i], size1) != count(arr2, arr1[i], size1)){
			dup_check = 0;		
			break;
		}
	}
//	printf("[DEBUG] %d %d\n", len_check, dup_check);
	if(dup_check == 1 && len_check == 1) return 1;
	return 0;
}

int*
random_list(){
	rand_len = (rand()%10) + 1;
//	printf("%d\n", rand_len);
	int* rand_Arr = (int*)malloc(sizeof(int)*rand_len);
	
	for(int i=0; i<rand_len; i++){
		rand_Arr[i] = (rand()%100) + 1;
	}
	
	return rand_Arr;
}

int main(){
	srand((unsigned int)time(NULL));
	int arr[] = {3, 2, 1};
	int * test;
	test = shellsort(arr, 3);
	for(int i=0; i<3; i++){
		printf("%d ", test[i]);
	}
	printf("\n");

	assert(cmp(shellsort(arr, 3), test, 3) == 1);

	// part 1
	
	int l1[] = {1, 2, 3, 4};
	int l2[] = {6, 5};
	int l2s[] = {5, 6};	
	int l3[] = {2, 2, 1};
	int l3s[] = {1, 2, 2};
	int l4[] = {};
	
	assert(cmp(shellsort(l1, 4), l1, 4) == 1);
	assert(cmp(shellsort(l2, 2), l2s, 2) == 1);
	assert(cmp(shellsort(l3, 3), l3s, 3) == 1);
	assert(cmp(shellsort(l4, 0), l4, 0) == 1);
	
	// part 2
	
	int sorted[] = {3, 5, 9};
	is_sorted(sorted, 3);
	if(is_sorted(sorted, 3) == 1) printf("S True\n");

	int dup1[] = {3, 2, 1};
	int dup2[] = {1, 3, 2};
	if(is_permutation(dup1, 3, dup2, 3) == 1) printf("P True\n");
	
	for(int i=0; i<1000; i++){
		int* elems = random_list();
		int* sorted_elems = shellsort(elems, rand_len);
	assert(((is_sorted(sorted_elems, rand_len)) == 1) && (is_permutation(sorted_elems, rand_len, elems, rand_len)) == 1);
	}

	return 0;
}
