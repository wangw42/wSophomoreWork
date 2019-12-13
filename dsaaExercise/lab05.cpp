/*
Lab Work 05-1. Balance Rotations of AVL Trees

Note. Programming in C/C++, including <iostream>/<iostream.h> only

An AVL tree is a binary search tree where every node in the tree has a balance factor of -1, 0 or +1. But any insertion into the AVL tree may cause violations of balance in four cases: Left-Left, Left-Right, Right-Right, and Right-Left. Single Rotations and Double Rotations are introduced to fix these cases.

Determine the data structures for an AVL tree
Implement an insertion into the AVL tree
Implement the four possible rotations to fix violations of balance caused by the insertion.
(End)

*/

#include <iostream>

using namespace std;

template<typename T>
class AVLNode{
public:
	T value;
	int height;
	AVLNode* left;
	AVLNode* right;
	
	
	AVLNode(T v, AVLNode* l, AVLNode* r): value(v), height(0), left(l), right(r){};
	
	string addSpace(int d){
		string ret;
		for(int i = 0; i < d; i++)
			ret += ' ';
			
		return ret;	
	};
	
	void print(ostream& os, int wid = 0, char ch = '\0'){
		if(ch != '\0')
			os << addSpace(wid-1) << ch << value << endl;
		else 
			os << addSpace(wid) << value << endl;
		
		wid++;
		
		if(left != NULL)
			left->print(os, wid, 'L');
		if(right != NULL)
			right->print(os,wid, 'R');
	};
	
};

template<typename T>
class AVLTree{
private:
	AVLNode<T>* root;
	
public:
	AVLTree(){
		root = NULL;
	};
	~AVLTree(){
		deleteTree(root);
	};
	
	void deleteTree(AVLTree<T>* tree){
		if(tree == NULL) return;
		if(tree->left != NULL )
			deleteTree(tree->left);
		if(tree->right != NULL )
			deleteTree(tree->right );
		
		delete tree;
	}
	
	int height(AVLNode<T>* tree){
		if(tree != NULL)
			return tree->height;
		return 0;
	};
	int max(int a, int b){
		return a>b ? a : b;
	};
	
	void insert(T val){
		insert(root, val);	
	};
	
	AVLNode<T>* insert(AVLNode<T>* &tree, T val){
		if(tree == NULL){
			tree = new AVLNode<T>(val, NULL, NULL);
		}else if( val < tree->value){
			tree->left = insert(tree->left, val);
			
			if((height(tree->left) - height(tree->right))== 2){
				if(val < tree->left->value)
					tree = leftLeft(tree);
				else
					tree = leftRight(tree);
			}
		}else if( val > tree-> value ){
			tree->right = insert(tree->right, val);
			
			if((height(tree->right)-height(tree->left)) == 2){
				if(val < tree->right->value)
					tree = rightLeft(tree);
				else
					tree = rightRight(tree);
			}
		}else
			cout << "Insertion failed, your value is the same as one of the tree." << endl;
			
		tree->height = max(height(tree->left), height(tree->right)) + 1;
		
		return tree;
		
	};
	
	AVLNode<T>* leftLeft(AVLNode<T>* b){
		AVLNode<T>* a;
		a = b->left;
		b->left = a->right;
		a->right = b;
		
		b->height = max(height(b->left), height(b->right)) + 1;
		a->height = max(b->height, height(a->left)) + 1;
		
		return a;
	};
	
	AVLNode<T>* rightRight(AVLNode<T>* a){
		AVLNode<T>* b;
		b = a->right;
		a->right = b->left;
		b->left = a;
		
		a->height = max(height(a->left), height(a->right)) + 1;
		b->height = max(a->height, height(b->right)) + 1;
		
		return b;
	};
	
	AVLNode<T>* leftRight(AVLNode<T>* c){
		c->left = rightRight(c->left);
		return leftLeft(c);
	};
	
	AVLNode<T>* rightLeft(AVLNode<T>* a){
		a->right = leftLeft(a->right);
		return rightRight(a);
	};
	
	void print(){
		root->print(cout, 7);
	}
	
		
};

void example1();
void example2();

int main(){
	example1();
	example2();
	
	return 0;
};


void example1(){
	AVLTree<int>* tree = new AVLTree<int>();
		
	tree->insert(12);	
	tree->insert(15);
	tree->insert(18);
	tree->insert(21);
	tree->insert(24);
	tree->insert(27);
	tree->insert(30);
	tree->insert(33);
	
	cout << "----------- EXAMPLE 1 ----------" << endl;
	cout << "Before insert:" << endl;
	tree->print();
	
	cout << endl << "After insert 10(min):" << endl;
	tree->insert(10);
	tree->print();
	
	cout << endl << "After insert 40(max):" << endl;
	tree->insert(40);
	tree->print();
	
	cout << endl << "After insert 28(between min and max):" << endl;
	tree->insert(28);
	tree->print();
	
	cout << endl << "After insert 28(same number cannot be inserted):" << endl;
	tree->insert(28);
	tree->print();
	
	
};

void example2(){
	AVLTree<char>* tree = new AVLTree<char>();
		
	tree->insert('x');	
	tree->insert('m');
	tree->insert('o');
	tree->insert('q');
	tree->insert('s');
	
	tree->insert('f');
	tree->insert('g');
	tree->insert('h');
	tree->insert('i');	
	tree->insert('j');
	

	
	cout << "----------- EXAMPLE 2 ----------" << endl;
	cout << "Before insert:" << endl;
	tree->print();
	
	cout << endl << "After insert 'a'(min):" << endl;
	tree->insert('a');
	tree->print();
	
	cout << endl << "After insert 'z'(max):" << endl;
	tree->insert('z');
	tree->print();
	
	cout << endl << "After insert 'n'(between min and max):" << endl;
	tree->insert('n');
	tree->print();
	
	cout << endl << "After insert 'a'(same number cannot be inserted):" << endl;
	tree->insert('a');
	tree->print();
	
	
};
