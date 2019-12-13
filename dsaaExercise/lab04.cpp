/*
Lab Work 04-1. Application of Binary Trees

Note. Programming in C/C++, including <iostream>/<iostream.h> only

A left-child-right-sibling binary tree (LCRS) is a binary tree used to store a general rooted ordered tree by the following consideration:

The first child of each node is its left sub-tree in LCRS
The next sibling of each node is its right sub-tree in LCRS
The transformation of a general rooted ordered tree into a LCRS binary tree has been called the Knuth transform

Determine the data structures for general rooted ordered trees and binary trees
Implement the Knuth transform in C/C++
Show by examples that a post-order traversal of the original tree is identical to the in-order traversal of the Knuth transform
(END)

*/


#include <iostream>

using namespace std;

template<typename T>
class Node{
public:
    T val;
    Node *next;
    Node *pre;
};

template<typename T>
struct listIterator{
    typedef Node<T>* Node;
    Node data;
    
    listIterator(){ data = 0; };
    listIterator(Node other){ data = other; };
    listIterator(const listIterator &other){ data = other.data; };
    listIterator& operator ++(){
        data = data->next;
        return *this;
    };
    listIterator& operator ++(int){
        data = data->next;
        return *this;
    };
    T& operator *(){
        return data->val;
    };
    bool operator != (const listIterator & other){
        return (other.data != data);
    };
    bool operator == (const listIterator & other){
        return (other.data == data);
    };
};

template<typename T>
class list{
public:
    typedef Node<T> Node;
    typedef Node* pNode;
    typedef listIterator<T> iterator;
    
private:
    pNode head;
    pNode tail;
    int _size;
    
    void init(){
        tail = head = new Node;
        head->next = NULL;
        head->pre = NULL;
        head->val = 0;
        _size = 0;
    };

public:
    list() { init(); };
    list(const list & other){
        init();
        Node *p = other.head->next;
        while(p != NULL){
            push_back(p->val);
            p = p->next;
        }
    };
    ~list(){
        pNode tmp = head->next;
        while (tmp != NULL) {
            pNode tmpNext = tmp->next;
            delete tmp;
            tmp = tmpNext;
        }
        delete head;
    };
    
    iterator begin(){
        return iterator(head->next);
    };
    iterator end(){
        return iterator(tail->next);
    };
    
    int size() const{ return _size; };
    
    iterator insert(iterator pos, T data){
        pNode newNode = new Node;
        newNode->val = data;
        ++_size;
        
        if(pos != end()){
            pNode p = pos.data;
            pNode preN = p->pre;
            newNode->pre = p->pre;
            newNode->next = p;
            if(preN) preN->next = newNode;
            p->pre = newNode;
        }else{
            tail->next = newNode;
            newNode->pre = tail;
            newNode->next = NULL;
            tail = newNode;
        }
        return iterator(newNode);
    };
    void push_back(T data){
        insert(end(), data);
    };
    
};

string addSpace(int dep){
    string ret;
    for(int i = 0; i < dep; i++){
        ret += ' ';
    }
    return ret;
};

template<typename T>
class multiwayTree{
public:
    typedef multiwayTree<T>* mTreePtr;
    typedef list<mTreePtr> List;
    
    T mdata;
    List mNodes;
    
public:
    multiwayTree(const T& d){
        mdata = d;
    };
    
    ~multiwayTree(){
        typename List::iterator it;
        it = mNodes.begin();
        while(it != mNodes.end()){
            delete (*it);
            it++;
        }
    };
    
    T& getNode() const{
        return mdata;
    };
    
    void goToFirstChild(typename List::iterator & it){
        it = mNodes.begin();
    };
    
    void goToNextChild(typename List::iterator & it){
        it++;
    };
    
    bool getChildNode(typename List::iterator & it, mTreePtr & pNode){
        bool ret = (it != mNodes.end());
        if(ret) pNode = (*it);
        else pNode = NULL;
        
        return ret;
    };
    
    mTreePtr appendChild(const T& newData){
        mTreePtr newNode = new multiwayTree(newData);
        mNodes.push_back(newNode);
        return newNode;
    };
    
    void print(ostream& os, int wid = 0){
        mTreePtr p;
        typename List::iterator it;
        
        os << addSpace(wid) << mdata << endl;
        wid++;
        goToFirstChild(it);
        while(getChildNode(it, p)){
            p->print(os, wid);
            goToNextChild(it);
        }
    };
};

template<typename T>
class binaryTree{
public:
    typedef binaryTree<T>* bTreePtr;
    typedef multiwayTree<T>* mTreePtr;
    
    T bdata;
    
    bTreePtr leftChild;
    bTreePtr rightBros;
public:
    binaryTree(const T& d){
        bdata = d;
        leftChild = NULL;
        rightBros = NULL;
    };
    
    bTreePtr setRight(bTreePtr pNew){
        if(rightBros != NULL){
            delete rightBros;
        }
        rightBros = pNew;
        return rightBros;
    };
    
    binaryTree(mTreePtr mT){
        if(mT != NULL){
            bTreePtr pNewNode;
            mTreePtr pNode;
            typename multiwayTree<T>::List::iterator it;
            
            bdata = mT->mdata;
            mT->goToFirstChild(it);
            if(mT->getChildNode(it, pNode)){
                pNewNode = new binaryTree(pNode);
                leftChild = pNewNode;
                mT->goToNextChild(it);
            }else {
                leftChild = NULL;
            }
            
            rightBros = NULL;
            while(mT->getChildNode(it, pNode)){
                pNewNode = pNewNode->setRight(new binaryTree(pNode));
                mT->goToNextChild(it);
            }
        }
    };
    
    void print(ostream& os, int wid = 0, char ch = '\0'){
        if( ch != '\0')
            os << addSpace(wid-1) << ch << bdata << endl;
        else
            os << addSpace(wid) << bdata << endl;
        
        wid++;
        if(rightBros != NULL)
            rightBros->print(os, wid, 'r');
        if(leftChild != NULL)
            leftChild->print(os, wid, 'l');
    };
};


void example1();
void example2();
void example3();

int main(){
    example1();
    example2();
    example3();
    
    return 0;
}


void example1(){
    cout << "------------ Example 1 <char> ------------" << endl;
    //Depth: 0
    //A -> B,C,D,E
    multiwayTree<char>::mTreePtr mNodeA = new multiwayTree<char>('A');
    multiwayTree<char>::mTreePtr mNodeB = mNodeA->appendChild('B');
    multiwayTree<char>::mTreePtr mNodeC = mNodeA->appendChild('C');
    multiwayTree<char>::mTreePtr mNodeD = mNodeA->appendChild('D');
    multiwayTree<char>::mTreePtr mNodeE = mNodeA->appendChild('E');
    
    //Depth: 1
    //C -> F,G,H
    multiwayTree<char>::mTreePtr mNodeF = mNodeC->appendChild('F');
    multiwayTree<char>::mTreePtr mNodeG = mNodeC->appendChild('G');
    multiwayTree<char>::mTreePtr mNodeH = mNodeC->appendChild('H');
    //D -> I,J
    multiwayTree<char>::mTreePtr mNodeI = mNodeD->appendChild('I');
    multiwayTree<char>::mTreePtr mNodeJ = mNodeD->appendChild('J');
    //E -> K,L,M,N
    multiwayTree<char>::mTreePtr mNodeK = mNodeE->appendChild('K');
    multiwayTree<char>::mTreePtr mNodeL = mNodeE->appendChild('L');
    multiwayTree<char>::mTreePtr mNodeM = mNodeE->appendChild('M');
    multiwayTree<char>::mTreePtr mNodeN = mNodeE->appendChild('N');
    
    //Depth: 2
    multiwayTree<char>::mTreePtr mNodeO = mNodeF->appendChild('O');
    multiwayTree<char>::mTreePtr mNodeP = mNodeF->appendChild('P');
    
    multiwayTree<char>::mTreePtr mNodeQ = mNodeI->appendChild('Q');
    
    multiwayTree<char>::mTreePtr mNodeR = mNodeK->appendChild('R');
    
    multiwayTree<char>::mTreePtr mNodeS = mNodeM->appendChild('S');
    multiwayTree<char>::mTreePtr mNodeT = mNodeM->appendChild('T');
    
    //Depth: 3
    multiwayTree<char>::mTreePtr mNodeU = mNodeP->appendChild('U');
    
    multiwayTree<char>::mTreePtr mNodeV = mNodeQ->appendChild('V');
    multiwayTree<char>::mTreePtr mNodeW = mNodeQ->appendChild('W');
    
    multiwayTree<char>::mTreePtr mNodeX = mNodeT->appendChild('X');
    multiwayTree<char>::mTreePtr mNodeY = mNodeT->appendChild('Y');
    multiwayTree<char>::mTreePtr mNodeZ = mNodeT->appendChild('Z');
    
    
    cout << "General multi-way tree:" << endl;
    mNodeA->print(cout, 7);
    cout << endl;
    
    binaryTree<char>::bTreePtr bNode = new binaryTree<char>(mNodeA);
    
    cout << "Binary tree converted from multi-way tree:" << endl;
    bNode->print(cout, 7);
    
    delete mNodeA;
    delete bNode;
};


void example2(){
     cout << "------------ Example 2 <int> ------------" << endl;
    
     //Depth: 0
     //1 -> 2,3,4,5,6
     multiwayTree<int>::mTreePtr mNode1 = new multiwayTree<int>(1);
     multiwayTree<int>::mTreePtr mNode2 = mNode1->appendChild(2);
     multiwayTree<int>::mTreePtr mNode3 = mNode1->appendChild(3);
     multiwayTree<int>::mTreePtr mNode4 = mNode1->appendChild(4);
     multiwayTree<int>::mTreePtr mNode5 = mNode1->appendChild(5);
     multiwayTree<int>::mTreePtr mNode6 = mNode1->appendChild(6);

     
     //Depth: 1
     multiwayTree<int>::mTreePtr mNode7 = mNode4->appendChild(7);
     multiwayTree<int>::mTreePtr mNode8 = mNode4->appendChild(8);
     multiwayTree<int>::mTreePtr mNode9 = mNode4->appendChild(9);
    
     multiwayTree<int>::mTreePtr mNode10 = mNode6->appendChild(10);
     
     //Depth: 2
     multiwayTree<int>::mTreePtr mNode11 = mNode7->appendChild(11);
     
     multiwayTree<int>::mTreePtr mNode12 = mNode10->appendChild(12);
     
     //Depth: 3
     multiwayTree<int>::mTreePtr mNode13 = mNode11->appendChild(13);
     
     multiwayTree<int>::mTreePtr mNode14 = mNode12->appendChild(14);
     multiwayTree<int>::mTreePtr mNode15 = mNode12->appendChild(15);
     
     
     cout << "General multi-way tree:" << endl;
     mNode1->print(cout, 7);
     cout << endl;
     
     binaryTree<int>::bTreePtr bNode = new binaryTree<int>(mNode1);
     
     cout << "Binary tree converted from multi-way tree:" << endl;
     bNode->print(cout, 7);
     
     delete mNode1;
     delete bNode;
    
};

void example3(){
    cout << "------------ Example 3 <string> ------------" << endl;
    //Depth: 0
    //1 -> 2,3,4,5,6
    multiwayTree<string>::mTreePtr mNode1 = new multiwayTree<string>("Ancestor");
    multiwayTree<string>::mTreePtr mNode2 = mNode1->appendChild("Grandfather1");
    multiwayTree<string>::mTreePtr mNode3 = mNode1->appendChild("Grandfather2");
    multiwayTree<string>::mTreePtr mNode4 = mNode1->appendChild("Grandfather3");

    
    //Depth: 1
    multiwayTree<string>::mTreePtr mNode5 = mNode4->appendChild("Father");
    multiwayTree<string>::mTreePtr mNode6 = mNode4->appendChild("Uncle");
    
    //Depth: 2
    multiwayTree<string>::mTreePtr mNode7 = mNode5->appendChild("Son");
    
    multiwayTree<string>::mTreePtr mNode8 = mNode7->appendChild("Daughter");
    
    
    cout << "General multi-way tree:" << endl;
    mNode1->print(cout, 7);
    cout << endl;
    
    binaryTree<string>::bTreePtr bNode = new binaryTree<string>(mNode1);
    
    cout << "Binary tree converted from multi-way tree:" << endl;
    bNode->print(cout, 7);
    
    delete mNode1;
    delete bNode;
};
