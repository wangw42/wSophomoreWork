/*
Lab Work 06-1. Array Implemetation of min-Heaps

Note. Programming in C/C++, including <iostream>/<iostream.h> and <cstdlib>/<cstdlib.h>only

A complete min-heap is a min-heap with the structure of a complete binary tree which can be stored using an array.

Determine the array structures for a complete min-heap
Input a linear list of 20 random numbers, building a complete min-heap to store the numbers
Implement POP and PUSH operations for the min-heaps.
(End)


*/

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Heap{
	int* data;
	int capacity;
} *minHeap;

int Min(int l, int r, minHeap h){
	return h->data[l] < h->data[r] ? l : r;
}

void initHeap(int* arr, int _size, minHeap &_heap, int _max){
	_heap = (minHeap)malloc(sizeof(Heap));
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
				flag = Min(tmp<<1, (tmp<<1)+1, _heap);
			}
			
			if(_heap->data[tmp] > _heap->data[flag]){
				int tmp2 = _heap->data[tmp];
				_heap->data[tmp] = _heap->data[flag];
				_heap->data[flag] = tmp2;
				
				tmp = flag;
			}else  
				break;
		}
	}
};

int popHeap(minHeap& heap){
	int size = heap->data[0];
	if(size == 0){
		cout << "Pop failed, this heap is empty.";
	}
	int p = 1, ret = heap->data[1];
	
	while((p << 1) <= size){
		int tmp = p<<1;
		if(heap->data[tmp] < heap->data[tmp+1]){
			heap->data[p] = heap->data[tmp];
			p = tmp;
		}else {
			heap->data[p] = heap->data[tmp+1];
			p = tmp+1;
		}
	}
	heap->data[p] = -1;
	
	
	heap->data[0] -= 1;
	
	return ret;
};

bool pushHeap(minHeap & heap, int num){
	if(heap->capacity == heap->data[0]){
		return false;
	}
	
	heap->data[0] += 1;
	int size = heap->data[0];
	heap->data[size] = num;
	
	for(int p = size; p > 1; ){
		int p2 = p/2;
		if(heap->data[p2] > heap->data[p]){
			int tmp = heap->data[p2];
			heap->data[p2] = heap->data[p];
			heap->data[p] = tmp;
			p = p2;
		}else
			break;
	}
	
	return true;
}

void print(const minHeap& heap){
	for(int i = 1; i < heap->data[0]+1; i++){
		cout << heap->data[i] << " ";
	}
	
	cout << endl;
}

void printArr(const int* arr, int size){
	for(int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void example1(){
	//freopen("output.txt", "w", stdout);
	
	int arr[20] = {20,18,2,7,77,86,34,40,14,38,67,71,9,1,15,55,61,39,24,16};
	minHeap heap;
	initHeap(arr, 20, heap, 25);
	
	cout << "arr before init:" << endl;
	printArr(arr, 20);
	cout << "minHeap:" << endl;
	print(heap);
	
	cout << "Push 19 : (1 for true 0 for false) " << pushHeap(heap, 19) << endl;
	print(heap);
	cout << "Push 100 : (1 for true 0 for false) " << pushHeap(heap, 100) << endl;
	print(heap);
	cout << "Push 57 : (1 for true 0 for false) " << pushHeap(heap, 57) << endl;
	print(heap);
	cout << "Push 51 : (1 for true 0 for false) " << pushHeap(heap, 51) << endl;
	print(heap);
	cout << "Push 42 : (1 for true 0 for false) " << pushHeap(heap, 42) << endl;
	print(heap);
	cout << "Push 5 : (1 for true 0 for false) " << pushHeap(heap, 5) << endl;
	print(heap);
	cout << endl;
	
	cout << "Pop " << popHeap(heap) << endl;
	print(heap);
	cout << "Pop " << popHeap(heap) << endl;
	print(heap);
	cout << "Pop " << popHeap(heap) << endl;
	print(heap);
	cout << "Pop " << popHeap(heap) << endl;
	print(heap);
	cout << "Pop " << popHeap(heap) << endl;
	print(heap);
}

int main(){
	example1();

	
	return 0;
}
