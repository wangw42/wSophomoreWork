/*
问题描述：

设有 M = 8 个有序队列，每个队列的关键字从小到大排列，需要将这些队列元素归并成一个新的从小到大的有序队列。

算法描述：

取出每个队列的队头元素，构造一个有 M 个节点的完全小顶堆，利用这个小顶堆实现 M-路归并排序。

排序的每一趟是：

* Pop 堆顶得到当前的最小元素 x，设 x 来自队列 k；
* Dequeue 队列 k 得到元素 y，将 y 装入队顶；
* 实施 Percolating 维护堆。
说明：队列 k 为空时，Dequeue 操作失败，此时将堆尾元素移入堆顶并维护堆；直至所有队列为空。此时堆也被清空。

数据结构描述：

设计上述实现的数据结构，包括队列结构和堆结构。

*/




#include <iostream>
#include <stdlib.h>

#define MAXSIZE 65

using namespace std;

class Queue{
private:
    int size;
    int data[MAXSIZE];
    
public:
    Queue(){
        size = 0;
    };
    
    Queue(int _s, int *arr){
        size = _s;
        for(int i = 0; i < size; i++){
            data[i] = arr[i];
        }
        
        //insertion sort
        for(int i = 1; i < size; i++){
            for(int j = i; j > 0; j--){
                if(data[j] < data[j-1]){
                    int tmp = data[j];
                    data[j] = data[j-1];
                    data[j-1] = tmp;
                }
            }
        }
    };
    
    pair<bool, int> dequeue(){
        pair<bool, int> ret;
        
        if(this->size == 0) {
            cout << "Empty Queue, dequeue failed." << endl;
            ret.first = false;
            ret.second = 0;
            return ret;
        }
        
        size--;
        ret.first = true;
        ret.second = data[0];
        
        for(int i = 0; i < size; i++){
            data[i] = data[i+1];
        }
        
        return ret;
    }
    
    void pushQueue(int d){
        data[size] = d;
        size++;
    };
    
    const int getSize(){
        return size;
    };
    
    void print(){
        
        for(int i = 0; i < size; i++){
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
};

typedef struct Heap{
    pair<int, int> *data; //data.first data, data.second from which queue
    int capacity;
} *minHeap;

int Min(int l, int r, minHeap h){
    return h->data[l].first < h->data[r].first ? l : r;
}

void swapData(minHeap & h, int a, int b){
    int tmp1 = h->data[a].first;
    int tmp2 = h->data[a].second;
    
    h->data[a].first = h->data[b].first;
    h->data[b].first= tmp1;
    
    h->data[a].second = h->data[b].second;
    h->data[b].second = tmp2;
};

void initHeap(int* arr, int _size, minHeap &_heap, int _max, int *from){
    _heap = (minHeap)malloc(sizeof(Heap));
    _heap->capacity = _max;
    _heap->data = new pair<int, int>[_max+1];
    _heap->data[0].first = _size;
    _heap->data[0].second = _size;
    
    //from
    for(int i = 1; i < _size; i++){
        _heap->data[i].second = from[i-1];
    }
    
    //data
    for (int i = 0; i < _size; i++){
        _heap->data[i+1].first = arr[i];
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
            
            if(_heap->data[tmp].first > _heap->data[flag].first){
                swapData(_heap, tmp, flag);
                tmp = flag;
            }else
                break;
        }
    }
};

pair<int , int> popHeap(minHeap& heap){
    pair<int, int> ret;
    ret.first = heap->data[1].first;
    ret.second = heap->data[1].second;
    int size = heap->data[0].first;
    
    if(size == 0){
        cout << "Pop failed, this heap is empty.";
    }
    
    heap->data[1].first = heap->data[size].first;
    heap->data[1].second = heap->data[size].second;
    heap->data[size].first = 0;
    heap->data[size].second = 0;
    //size
    heap->data[0].first--;
    heap->data[0].second--;
    size--;
    
    int p = 1;
    
    while( (p << 1)  < size ){
        int tmp = p << 1;

        if(heap->data[p].first < heap->data[tmp].first && heap->data[p].first < heap->data[tmp+1].first){
            break;
        }else if(heap->data[tmp].first <= heap->data[tmp+1].first){
            swapData(heap, p, tmp);
            p = tmp;
        } else if (heap->data[tmp].first > heap->data[tmp+1].first){
            swapData(heap, p, tmp+1);
            p = tmp+1;
        }
    }

    return ret;
};

bool pushHeap(minHeap & heap, int num, int from){
    if(heap->capacity == heap->data[0].first){
        return false;
    }
    
    heap->data[0].first += 1;
    heap->data[0].second += 1;
    int size = heap->data[0].first;
    heap->data[size].first = num;
    heap->data[size].second = from;
    
    for(int p = size; p > 1; ){
        int p2 = p/2;
        if(heap->data[p2].first > heap->data[p].first){
            swapData(heap, p, p2);
            p = p2;
        }else
            break;
    }
    
    return true;
}

void print(const minHeap& heap){
    for(int i = 1; i < heap->data[0].first+1; i++){
        cout << heap->data[i].first << " ";
    }
    
    cout << endl;
}

void printArr(const int* arr, int size){
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}



void example1(){
    int arr[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            arr[i][j] = rand()%100 + 1;
        }
    }
    
    Queue* q[8];
    for(int i = 0; i < 8; i++){
        q[i] = new Queue(8, arr[i]);
        //testing
        cout << "Queue: " << i << endl;
        q[i]->print();
    }
    
    int from[8] = {0,1,2,3,4,5,6,7};
    minHeap heap;
    
    int firstArr[8] = {q[0]->dequeue().second, q[1]->dequeue().second,
                       q[2]->dequeue().second, q[3]->dequeue().second,
                       q[4]->dequeue().second, q[5]->dequeue().second,
                       q[6]->dequeue().second, q[7]->dequeue().second};
    
    initHeap(firstArr, 8, heap, 8, from);
    
    //testing
    cout << "First data of queues: ";
    printArr(firstArr, 8);
    cout << "Heap: ";
    print(heap);
    
    Queue* ret = new Queue();
    
    //sorting
    while(heap->data[0].first){
    
        pair<int, int> xk = popHeap(heap); //first: data(x), second: which queue(k)
        
        //cout << "xk: " << xk.first << " " << xk.second << endl;
        
        pair<bool, int> by = q[xk.second]->dequeue(); // first: bool, second data y;
        
        /*
        //testing
        cout << "data y, x, k: ";
        cout << by.second << " " << xk.first  << " " << xk.second << endl;
        */
        
         
        int y = 0;
        if(by.first){
            y = by.second;
            pushHeap( heap, y, xk.second);
        }
        ret->pushQueue(xk.first);
    
    }
    
    ret->print();
        
}

int main(){
    example1();
    
    return 0;
}