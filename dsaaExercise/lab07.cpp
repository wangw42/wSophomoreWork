/*
Lab Work 07-1. In-place Heap Sorting
Note. Programming in C/C++, including <iostream>/<iostream.h> and <cstdlib>/<cstdlib.h>only

Determine the array structures for a complete max-heap
Input a linear list of 20 random numbers, building a complete max-heap to store the numbers by the process of in-place heapification
Implement an in-place sorting, making use of POP operation for the built complete max-heaps .

*/

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Heap{
	int* data;
	int capacity;
} *maxHeap;

int Max(int l, int r, maxHeap h){
	return h->data[l] > h->data[r] ? l : r;
}

void initHeap(int* arr, int _size, maxHeap &_heap, int _max){
	_heap = (maxHeap)malloc(sizeof(Heap));
	_heap->capacity = _max;
	_heap->data = new int[_max+1];
	_heap->data[0] = _size;
	
	for (int i = 0; i < _size; i++){
		_heap->data[i+1] = arr[i];
	}
	
	for(int p = _size/2; p >= 1; p--){
		int tmp = p;
		while((tmp << 1) <= _size){
			int flag = 0;
			if((tmp << 1)+1 > _size){
				flag = (tmp << 1);
			}else {
				flag = Max(tmp<<1, (tmp<<1)+1, _heap);
			}
			
			if(_heap->data[tmp] < _heap->data[flag]){
				int tmp2 = _heap->data[tmp];
				_heap->data[tmp] = _heap->data[flag];
				_heap->data[flag] = tmp2;
				
				tmp = flag;
			}else  
				break;
		}
	}
};

int popHeap(maxHeap& heap){
	int ret = heap->data[1];
	int size = heap->data[0];
	
	if(size == 0){
		cout << "Pop failed, this heap is empty.";
	}
	
	heap->data[1] = heap->data[size];
	heap->data[size] = -1;
	heap->data[0]--;
	size--;
	
	int p = 1;
	
	while( (p << 1) <= size ){
		int tmp = p << 1;
		
		if(heap->data[p] > heap->data[tmp] && heap->data[p] > heap->data[tmp+1]){
			break;
		}else if(heap->data[tmp] > heap->data[tmp+1]){
			int tmp2 = heap->data[p];
			heap->data[p] = heap->data[tmp];
			heap->data[tmp] = tmp2;
			p = tmp;
		} else if (heap->data[tmp] < heap->data[tmp+1]){
			int tmp2 = heap->data[p];
			heap->data[p] = heap->data[tmp+1];
			heap->data[tmp+1] = tmp2;
			p = tmp+1;
		}
	}

	return ret;
};


bool pushHeap(maxHeap & heap, int num){
	if(heap->capacity == heap->data[0]){
		return false;
	}
	
	heap->data[0] += 1;
	int size = heap->data[0];
	heap->data[size] = num;
	
	for(int p = size; p > 1; ){
		int p2 = p/2;
		if(heap->data[p2] < heap->data[p]){
			int tmp = heap->data[p2];
			heap->data[p2] = heap->data[p];
			heap->data[p] = tmp;
			p = p2;
		}else
			break;
	}
	
	return true;
}

//merge sort without using pop
/*
void mergeSort(maxHeap& heap, int l, int m, int r){
	int len = r-l+1;
	int arr[len];
	
	int i = 0; 
	int j = m+1-l;
	
	for(int x = 0; x <= r-l; x++){
		arr[x] = heap->data[x+l];
	}
	heap->data[0] = 20;
	
	int k = l;
	while(i <= m-l && j <= r-l){
		if(arr[i] <= arr[j]){
			heap->data[k] = arr[i];
			i++;
		}else{
			heap->data[k] = arr[j];
			j++;
		}
		k++;
	}
	
	while(i <= m-l){
		heap->data[k] = arr[i];
		i++;
		k++;
	}
	
	while(j <= r-l){
		heap->data[k] = arr[j];
		j++;
		k++;
	}
}

void sortHeap(maxHeap& heap, int l, int r){
	if(l < r){
		int m = l+(r-l)/2;
		sortHeap(heap, l, m);
		sortHeap(heap, m+1, r);
		
		mergeSort(heap, l, m, r);
	}
}
*/

void sortByPop(maxHeap& heap){
	int arr[20];
	for(int i = 0; i < 20; i++){
		arr[i] = popHeap(heap);
	}
	
	for(int i = 0; i < 20; i++){
		pushHeap(heap, arr[i]);
	}
}

void print(const maxHeap& heap){
	for(int i = 1; i < heap->data[0]+1; i++){
		cout << heap->data[i] << " ";
	}
	
	cout << endl;
}



int main(){
	//freopen("output.txt", "w", stdout);
	
	
	int arr[20] = {20,18,2,7,77,86,34,40,14,38,67,71,9,1,15,55,61,39,24,16};
	maxHeap heap;
	initHeap(arr, 20, heap, 25);
	
	cout << "maxHeap:" << endl;
	print(heap);
	
	cout << "After sorting: " << endl;
	sortByPop(heap);
	print(heap);
	
	//sortHeap(heap, 1, 20);
	//print(heap);
	
	
	return 0;
}
