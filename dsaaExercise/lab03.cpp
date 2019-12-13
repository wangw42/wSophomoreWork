/*
Lab Work 03-1. Application of Lists and Stacks

Note. Programming in C++, including <iostream>/<iostream.h> and <cstdlib>/<cstdlib.h> only

Let n be a positive integer with specified initial value n=30. Use an array of n units to store polynomial of one indeterminate. Design and implement a C++ program to

Determine the data structure of the array
Use a stack S in the array to store unused units. Initially all the units are unused and the 0 to (n-1) indexes are spreaded randomly on the stack
Use two linked lists LP and LQ in the array to store two polynomial of one indeterminates P and Q
Show the map of the array
Adding P and Q, restore the result as a linked list LPQ in the array, and release all garbage units to the stack** S**
Show the map of the array again

*/

#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAXSIZE 30
#define MAXINT 2147483647u
#define MININT -2147483648u

typedef struct Node{
	int coef;
	int index;
	int cur;
}List[MAXSIZE];

class Stack{
public:
	Stack(){
		for(int i = 0; i < MAXSIZE-1; i++){
			index[i] = i+1;
		}
		index[MAXSIZE-1] = 0;
	
		for(int i = 0; i < MAXSIZE; i++){
			int flag = rand()%30;
			int tmp = index[flag];
			index[flag] = index[29-flag];
			index[29-flag] = tmp;
		}
		
		size = 30;
	};
	
	bool isFull(){
		return (size == 30);
	};
	
	bool isEmpty(){
		return (size == 0);	
	};
	
	void push(int i){
		if(isFull()) return;
		
		index[size-1] = i;
		size += 1;
	};
	
	int pop(){
		if(isEmpty()) return -1;
		
		size -= 1;
		return index[size];	
	};
	
private:
	int index[MAXSIZE];
	int size;
};

void initList(List& array);
bool checkOverflow(int n1, int n2);
void addPoly(List& res, List l1, List l2);
void showList(List& li);

void example1();
void example2();
void example3();
void example4();
void example5();

int main(){
	cout<< "example1 展示了普通的两个多项式相加." << endl;
	example1();
	cout << "example2 展示了俩稀疏多项式相加。" <<endl;
	example2();
	cout << "example3 展示了俩多项式相加，其中存在系数相加后溢出的情况，我的解决方法是将这两个连续分开展示。" << endl;
	example3();
	cout << "example4 展示了俩多项式相加，其中存在系数相加和为0的情况，即不展示。" << endl;
	example4();
	cout << "example5 展示了以上多种情况共同出现。" << endl; 
	example5();
	
	
	return 0;
};


void initList(List& array){
	for(int i = 0; i < MAXSIZE; i++){
		array[i].cur = -1;
		array[i].coef = 0;
		array[i].index = 0;
	}
	
};

bool checkOverflow(int n1, int n2){
	if(n1 > 0 && n2 > 0 && n1 > MAXINT-n2)
		return true;
		
	if(n1 < 0 && n2 < 0 && n1 < MININT-n2)
		return true;
		
	return false;
};

void addPoly(List& res, List l1, List l2){
	int cnt = 0;
	Stack stackRes;
	int flag = stackRes.pop();
	
	for(int i = 0; i < MAXSIZE; i++){
		if(l1[i].cur != -1){
			for(int j = 0; j < MAXSIZE; j++){
				if(l2[j].cur != -1 && l1[i].index == l2[j].index && (l2[j].coef+l1[i].coef == 0)){
					l1[i].cur = -1;
					l2[j].cur = -1;
				}else if(l2[j].cur != -1 && l1[i].index == l2[j].index && checkOverflow(l1[i].coef,l2[j].coef)){
					res[flag].index = l1[i].index;
					res[flag].coef = l1[i].coef;
					int tmp = flag;
					flag = stackRes.pop();
					res[tmp].cur = flag;
					
					res[flag].index = l2[j].index;
					res[flag].coef = l2[j].coef;
					tmp = flag;
					flag = stackRes.pop();
					res[tmp].cur = flag;
					
					cnt += 2;
					l1[i].cur = -1;
					l2[j].cur = -1;
				}else if(l2[j].cur != -1 && l1[i].index == l2[j].index && (l2[j].coef + l1[i].coef != 0)){
					res[flag].index = l1[i].index;
					res[flag].coef = l1[i].coef + l2[j].coef;
					int tmp = flag;
					flag = stackRes.pop();
					res[tmp].cur = flag;
					cnt++;
					l1[i].cur = -1;
					l2[j].cur = -1;					
				}
			}
			
			if(l1[i].cur != -1){
				res[flag].index = l1[i].index;
				res[flag].coef = l1[i].coef;
				int tmp = flag;
				flag = stackRes.pop();
				res[tmp].cur = flag;
				cnt++;
				l1[i].cur = -1;
			}
		}
	}
	
	for(int j = 0; j < MAXSIZE; j++){
		if(l2[j].cur != -1){
			res[flag].index = l2[j].index;
			res[flag].coef = l2[j].coef;
			int tmp = flag;
			flag = stackRes.pop();
			res[tmp].cur = flag;
			cnt++;
			l2[j].cur = -1;
		}
	}
};

void showList(List& li){
	int cnt = 0;
	int unused[MAXSIZE];
	for(int i = 0; i < MAXSIZE; i++){
		if(li[i].cur != -1){
			cout << "No." << i  << ": "<< li[i].coef << "x^" << li[i].index << "-> No." << li[i].cur << endl;
		}else{
			unused[cnt++] = i;
		}
	}
	cout << "Unused unit:" ;
	for(int i = 0; i < cnt; i++){
		cout << unused[i] << " ";
	}
	cout << endl << "--------------------" << endl;
};

void example1(){
	int LP1[14][2] = {{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},
						{10,10},{11,11},{12,12},{13,13},{14,14}};
	int LQ1[16][2] = {{1,15},{2,16},{3,17},{4,18},{5,19},{6,20},{7,21},{8,22},{9,23},
						{10,24},{11,25},{12,26},{13,27},{14,28}};
		
	List listLP1;
	List listLQ1;
	initList(listLP1);
	initList(listLQ1);
	
	Stack stackLP1;
	Stack stackLQ1;
	
	int flag1 = stackLP1.pop();
	int flag2 = stackLQ1.pop();
	
	for(int i = 0; i < 14; i++){
		listLP1[flag1].coef = LP1[i][0];
		listLP1[flag1].index = LP1[i][1];
		int tmp = flag1;
		flag1 = stackLP1.pop();
		listLP1[tmp].cur = flag1;
	}
	
	for(int i = 0; i < 14; i++){
		listLQ1[flag2].coef = LQ1[i][0];
		listLQ1[flag2].index = LQ1[i][1];
		int tmp = flag2;
		flag2 = stackLQ1.pop();
		listLQ1[tmp].cur = flag2;
	}
	
	cout << "********** EXAMPLE 1 **********" << endl;
	
	showList(listLP1);
	showList(listLQ1);
	
	List res1;
	initList(res1);
	addPoly(res1, listLP1,listLQ1);
	showList(res1);
	
	cout << "********** END 1 **********" << endl;
};

void example2(){
	int LP1[1][2] = {{1,1}};
	int LQ1[2][2] = {{1,1},{16,30}};
		
	List listLP1;
	List listLQ1;
	initList(listLP1);
	initList(listLQ1);
	
	Stack stackLP1;
	Stack stackLQ1;
	
	int flag1 = stackLP1.pop();
	int flag2 = stackLQ1.pop();
	
	for(int i = 0; i < 1; i++){
		listLP1[flag1].coef = LP1[i][0];
		listLP1[flag1].index = LP1[i][1];
		int tmp = flag1;
		flag1 = stackLP1.pop();
		listLP1[tmp].cur = flag1;
	}
	
	for(int i = 0; i < 2; i++){
		listLQ1[flag2].coef = LQ1[i][0];
		listLQ1[flag2].index = LQ1[i][1];
		int tmp = flag2;
		flag2 = stackLQ1.pop();
		listLQ1[tmp].cur = flag2;
	}
	
	cout << "********** EXAMPLE 2 **********" << endl;
	
	showList(listLP1);
	showList(listLQ1);
	
	List res1;
	initList(res1);
	addPoly(res1, listLP1,listLQ1);
	showList(res1);
	
	cout << "********** END 2 **********" << endl;
};

void example3(){
	int LP1[4][2] = {{50,1},{2,2},{-200,3},{4,4}};
	int LQ1[6][2] = {{2147483647,1},{2,2},{-2147483647,3},{4,4},{5,19},{6,20}};
		
	List listLP1;
	List listLQ1;
	initList(listLP1);
	initList(listLQ1);
	
	Stack stackLP1;
	Stack stackLQ1;
	
	int flag1 = stackLP1.pop();
	int flag2 = stackLQ1.pop();
	
	for(int i = 0; i < 4; i++){
		listLP1[flag1].coef = LP1[i][0];
		listLP1[flag1].index = LP1[i][1];
		int tmp = flag1;
		flag1 = stackLP1.pop();
		listLP1[tmp].cur = flag1;
	}
	
	for(int i = 0; i < 6; i++){
		listLQ1[flag2].coef = LQ1[i][0];
		listLQ1[flag2].index = LQ1[i][1];
		int tmp = flag2;
		flag2 = stackLQ1.pop();
		listLQ1[tmp].cur = flag2;
	}
	
	cout << "********** EXAMPLE 3 **********" << endl;
	
	showList(listLP1);
	showList(listLQ1);
	
	List res1;
	initList(res1);
	addPoly(res1, listLP1,listLQ1);
	showList(res1);
	
	cout << "********** END 3 **********" << endl;
}

void example4(){
	int LP1[7][2] = {{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}};
	int LQ1[6][2] = {{1,15},{2,16},{-4,4},{-5,5},{5,19},{6,20}};
		
	List listLP1;
	List listLQ1;
	initList(listLP1);
	initList(listLQ1);
	
	Stack stackLP1;
	Stack stackLQ1;
	
	int flag1 = stackLP1.pop();
	int flag2 = stackLQ1.pop();
	
	for(int i = 0; i < 7; i++){
		listLP1[flag1].coef = LP1[i][0];
		listLP1[flag1].index = LP1[i][1];
		int tmp = flag1;
		flag1 = stackLP1.pop();
		listLP1[tmp].cur = flag1;
	}
	
	for(int i = 0; i < 6; i++){
		listLQ1[flag2].coef = LQ1[i][0];
		listLQ1[flag2].index = LQ1[i][1];
		int tmp = flag2;
		flag2 = stackLQ1.pop();
		listLQ1[tmp].cur = flag2;
	}
	
	cout << "********** EXAMPLE 4 **********" << endl;
	
	showList(listLP1);
	showList(listLQ1);
	
	List res1;
	initList(res1);
	addPoly(res1, listLP1,listLQ1);
	showList(res1);
	
	cout << "********** END 4 **********" << endl;
}

void example5(){
	int LP1[12][2] = {{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},
						{11,11},{12,12},{13,13},{14,14}};
	int LQ1[14][2] = {{1,15},{2,16},{-3,3},{4,18},{5,19},{6,20},{7,21},{8,22},{9,23},
						{10,24},{-11,11},{12,26},{-2147483647,13},{-14,14}};
		
	List listLP1;
	List listLQ1;
	initList(listLP1);
	initList(listLQ1);
	
	Stack stackLP1;
	Stack stackLQ1;
	
	int flag1 = stackLP1.pop();
	int flag2 = stackLQ1.pop();
	
	for(int i = 0; i < 12; i++){
		listLP1[flag1].coef = LP1[i][0];
		listLP1[flag1].index = LP1[i][1];
		int tmp = flag1;
		flag1 = stackLP1.pop();
		listLP1[tmp].cur = flag1;
	}
	
	for(int i = 0; i < 14; i++){
		listLQ1[flag2].coef = LQ1[i][0];
		listLQ1[flag2].index = LQ1[i][1];
		int tmp = flag2;
		flag2 = stackLQ1.pop();
		listLQ1[tmp].cur = flag2;
	}
	
	cout << "********** EXAMPLE 5 **********" << endl;
	
	showList(listLP1);
	showList(listLQ1);
	
	List res1;
	initList(res1);
	addPoly(res1, listLP1,listLQ1);
	showList(res1);
	
	cout << "********** END 5 **********" << endl;
}
