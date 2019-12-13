#include <iostream>
#include <unistd.h>

#define M 5
#define L 3

using namespace std;

int memory40[10] = {4,6,7,22,12,16,9,33,32,30};

template<typename T>
class Node{
public:
    bool isleaf;
    T *key;
    int size;
    Node **ptr;
    Node(bool);
};

template<typename T>
class BPlusTree{
public:
    Node<T>* root;
    
public:
    BPlusTree();
    ~BPlusTree();
    
    bool search(T);
    void insert(T);
    void remove(T);
    
    void print(Node<T>*);
    
private:
    void insideInsert(T, Node<T>*, Node<T>*);
    void insideRemove(T, Node<T>*);
    Node<T>* findParent(Node<T>*, Node<T>*);
};


template<typename T>
Node<T>:: Node(bool _i){
    isleaf = _i;
    size = 0;
    
    if(isleaf){
        key = new T[L];
        ptr = new Node<T>*[M+1];
    }else{
        key = new T[M];
        ptr = new Node<T>*[M+1];
    }
};



template<typename T>
BPlusTree<T>::BPlusTree(){
    root = NULL;
};

template<typename T>
BPlusTree<T>::~BPlusTree(){
    
};

template<typename T>
bool BPlusTree<T>:: search(T data){
    cout << "Searching: " << data << ". ";
    if(root == NULL){
        cout << "Empty tree, search failed." << endl;
        return false;
    }else{
        Node<T>* p = root;
        // search the corresponding leaf
        while(p->isleaf == false){
            for(int i = 0; i < p->size; i++){
                if(data < p->key[i]){
                    p = p->ptr[i];
                    break;
                }else if( i+1 == p->size){
                    p = p->ptr[i+1];
                    break;
                }
            }
        }
        
        // search data
        for(int i = 0; i < p->size; i++){
            if(p->key[i] == data){
                cout << "Search succeed, data found." << endl;
                return true;
            }
        }
        cout << "Search failed, data not Found." << endl;
    }
    
    return false;
};


template<typename T>
void BPlusTree<T>::insert(T data){
    //no tree, create one
    if(root == NULL){
        cout << "Insert succeed: " << data << endl;
        root = new Node<T>(true);
        root->key[0] = data;
        root->size++;
        return;
    }
    
    Node<T>* p = root;
    Node<T>* parent ;
    // find position
    while (!p->isleaf) {
        parent = p;
        for(int i = 0; i < p->size; i++){
            if(data < p->key[i]){
                p = p->ptr[i];
                break;
            }else if(i+1 == p->size){
                p = p->ptr[i+1];
                break;
            }
        }
    }
    //check overflow
    if(p->size < L){
        int i = 0;
        for(i = 0; i < p->size; i++)
            if(data < p->key[i]) break;
            
        for(int j = p->size; j > i; j--)
            p->key[j] = p->key[j-1];
        p->key[i] = data;
        p->size += 1;
        p->ptr[p->size] = p->ptr[p->size-1];
        p->ptr[p->size-1] = NULL;
        
        cout << "Insert succeed: " << data << endl;
        return;
    }else{
        Node<T>* newLeaf = new Node<T>(true);
        int i;
        
        //rearrange data between newleaf and old leaf
        T temp[L+1];
        for(i = 0; i < L; i++)
            temp[i] = p->key[i];
        
        for(i = 0; i < L ; i++)
            if(temp[i] > data)  break;
        
        for(int j = L; j > i; j--)
            temp[j] = temp[j-1];
        temp[i] = data;
        p->size = (L+1)/2;
        
        newLeaf->size = L+1-(L+1)/2;
        for(i = 0; i < p->size; i++)
            p->key[i] = temp[i];
        
        for(i = 0; i < newLeaf->size; i++)
            newLeaf->key[i] = temp[p->size+i];
        
        p->ptr[p->size] = newLeaf;
        newLeaf->ptr[newLeaf->size] = p->ptr[L];
        p->ptr[L] = NULL;
        
        cout << "Insert succeed: " << data ;
        cout << ", but overflow." << endl;
        
        if(p == root){
            root = new Node<T>(false);
            root->key[0] = newLeaf->key[0];
            root->ptr[0] = p;
            root->ptr[1] = newLeaf;
            root->size++;
        } else {
            //check up to ensure !leaf node not overflow
            insideInsert(newLeaf->key[0], parent, newLeaf);
        }
    }
};

// notice: !leaf node is M not L
template<typename T>
void BPlusTree<T>::insideInsert(T data, Node<T>* p, Node<T>* child){
    if(p->size < M){
        int i = 0;
        for(i = 0; i < p->size; i++)
            if(p->key[i] > data) break;
        
        for(int j = p->size; j > i ; j--){
            p->key[j] = p->key[j-1];
            p->ptr[j+1] = p->ptr[j];
        }
        
        p->key[i] = data;
        p->size++;
        p->ptr[i+1] = child;
    }else  {
        Node<T>* newLeaf = new Node<T>(false);
        
        int i = 0;
        T temp[M+1];
        Node<T>* temp2[M+2];
        temp2[M] = p->ptr[M];
        for(i = 0; i < M; i++) {
            temp[i] = p->key[i];
            temp2[i] = p->ptr[i];
        }

        for(i = 0; i < M; i++)
            if(temp[i] > data)  break;
        
        for(int j = M; j > i; j--){
            temp[j] = temp[j-1];
            temp2[j+1] = temp2[j];
        }

        temp[i] = data;
        temp2[i+1] = child;
        p->size=(M+1)/2;
        newLeaf->size = M - (M+1)/2;
        
        for(i = 0; i < p->size; i++)
            p->key[i] = temp[i];
        
        for(i = 0; i < p->size+1; i++)
            p->ptr[i] = temp2[i];
        
        for(i = 0; i < newLeaf->size; i++)
            newLeaf->key[i] = temp[p->size+1+i];
        
        for(i = 0; i < newLeaf->size+1; i++)
            newLeaf->ptr[i] = temp2[p->size+1+i];
        
        
        if(p == root) {
            root =new Node<T>(false);
            root->key[0] = temp[p->size];
            root->ptr[0] = p;
            root->ptr[1] = newLeaf;
            root->ptr[2] = NULL;
            root->size++;
        }  else
            insideInsert(temp[p->size],findParent(root,p),newLeaf);
        
    }
};

template<typename T>
void BPlusTree<T>::remove(T data){
    cout << "removing: " << data << endl;
    if(root == NULL)  {
        cout << "Empty tree, remove failed." << endl;
        return;
    }
    
    int i = 0;
    int left = -1;
    int right = -1;
    Node<T>* p = root;
    Node<T>* parent = NULL;
    
    //find and delete
    while(!p->isleaf){
        parent = p;
        for(i = 0; i < p->size; i++){
            if(data < p->key[i]){
                left = i-1;
                right = i+1;
                p = p->ptr[i];
                break;
            } else if(i+1 == p->size){
                left = i;
                right = i+2;
                p = p->ptr[i+1];
                break;
            }
        }
    }
    
    for(i = 0; i < p->size; i++)
        if(p->key[i] == data) break;
    
    if(i == p->size)  {
        cout << "Not found, remove failed." << endl;
        return;
    }
    p->size--;
    for(; i < p->size; i++)
        p->key[i] = p->key[i+1];
    
    p->ptr[p->size] = p->ptr[p->size+1];
    p->ptr[p->size+1] = NULL;
    cout << "Delete succeed: " << data << endl;
    
    //check underflow
    if(p->size < (L+1)/2){
        cout << "Underflow." << endl;
        if(p == root){
            if(p->size == 0) {
                Node<T>* temp = root;
                root = NULL;
                delete(temp);
            }
        }
        if(left >= 0){
            Node<T>* ls = parent->ptr[left];
            if(ls->size > (L+1)/2){
                for(i = p->size; i > 0; i--)
                    p->key[i]=p->key[i-1];
                
                p->ptr[p->size+1] = p->ptr[p->size];
                p->ptr[p->size] = NULL;
                p->size++;
                
                ls->size--;
                parent->key[left] = ls->key[ls->size];
                p->key[0] = ls->key[ls->size];
                ls->ptr[ls->size] = ls->ptr[ls->size+1];
                ls->ptr[ls->size+1] = NULL;
                return;
            }
        }
        if(right  <= parent->size) {
            Node<T>* rs = parent->ptr[right];
            if(rs->size > (L+1)/2){
                p->ptr[p->size+1] = p->ptr[p->size];
                p->ptr[p->size] = NULL;
                p->key[p->size] = rs->key[0];
                parent->key[right-1] = rs->key[0];
                p->size++;
                rs->size--;
                
                for(i = 0; i < rs->size; i++)
                    rs->key[i] = rs->key[i+1];
                
                rs->ptr[rs->size] = rs->ptr[rs->size+1];
                rs->ptr[rs->size+1] = NULL;
                return;
            }
        }
        if(left >= 0){
            Node<T>* ls = parent->ptr[left];
            if(ls->size + p->size < L+1) {
                for(i = 0; i < p->size; i++) {
                    ls->key[ls->size+i] = p->key[i];
                }
                ls->ptr[ls->size] = NULL;
                ls->size = ls->size + p->size;
                ls->ptr[ls->size] = p->ptr[p->size];
                insideRemove(parent->key[left], parent);
                return;
            }
        }
        if(right <= parent->size) {
            Node<T>* rs = parent->ptr[right];
            if(p->size + rs->size < L+1){
                for(i = 0; i < rs->size; i++) {
                    p->key[p->size+i] = rs->key[i];
                }
                p->ptr[p->size] = NULL;
                p->size = p->size + rs->size;
                p->ptr[p->size] = rs->ptr[rs->size];
                insideRemove(parent->key[right-1], parent);
                return;
            }
        }
    }
    return;
};

template<typename T>
void BPlusTree<T>::insideRemove(T data, Node<T>* p){
    int i = 0;
    for(i = 0; i < p->size; i++)
        if(p->key[i] == data)  break;
    p->size--;
    Node<T>*temp = p->ptr[i+1];
    for(int j = i; j < p->size; j++) {
        p->key[j] = p->key[j+1];
        p->ptr[j+1] = p->ptr[j+2];
    }
    delete(temp);

    if(p->size < (M+1)/2){
        if(p == root) {
            if(p->size == 0){
                temp = root;
                root = p->ptr[0];
                delete(temp);
            }
        }else {
            Node<T>* parent = findParent(root,p);
            int left = -1;
            int right = -1;
            for(i = 0; i < parent->size+1; i++) {
                if(p == parent->ptr[i]){
                    left = i-1;
                    right = i+1;
                    break;
                } else if(i+1 == parent->size+2) {
                    left = i;
                    right = i+2;
                    break;
                }
            }
            
            if(left >= 0) {
                Node<T>* ls = parent->ptr[left];
                if(ls->size > (M+1)/2) {
                    for(i = p->size; i > 0; i--)
                        p->key[i] = p->key[i-1];
                    
                    for(i = p->size+1; i > 0; i++)
                        p->ptr[i] = p->ptr[i-1];
                    
                    p->size++;
                    ls->size--;
                    parent->key[left] = ls->key[ls->size];
                    p->key[0] = ls->key[ls->size];
                    p->ptr[0] = ls->ptr[ls->size+1];
                    ls->ptr[ls->size+1] = NULL;
                    return;
                }
            }
            if(right <= parent->size){
                Node<T>* rs = parent->ptr[right];
                if(rs->size > (M+1)/2) {
                    p->key[p->size] = parent->key[right-1];
                    p->ptr[p->size+1] = rs->ptr[0];
                    parent->key[right-1] = rs->key[0];
                    p->size++;
                    rs->size--;
                    for(i = 0; i < rs->size; i++)
                        rs->key[i] = rs->key[i+1];
                    
                    for(i = 0; i < rs->size+1; i++)
                        rs->ptr[i] = rs->ptr[i+1];
                    
                    rs->ptr[rs->size+1] = NULL;
                    return;
                }
            }
            if(left >= 0){
                Node<T>* ls = parent->ptr[left];
                if(ls->size+p->size < M) {
                    ls->key[ls->size] = parent->key[left];
                    for(i = 0; i < p->size+1; i++)
                        ls->key[ls->size+1+i] = p->key[i];
                    
                    for(i = 0; i < p->size+2; i++)
                        ls->ptr[ls->size+1+i] = p->ptr[i];
                    
                    ls->size = ls->size + p->size + 1;
                    
                    insideRemove(parent->key[left], parent);
                    return;
                }
            }
            if(right <= parent->size)  {
                Node<T>* rs = parent->ptr[right];
                if(p->size + rs->size < M) {
                    p->key[p->size] = parent->key[right-1];
                    for(i = 0; i < rs->size+1; i++)
                        p->key[p->size+1+i] = rs->key[i];
                    
                    for(i = 0; i < rs->size+2; i++)
                        p->ptr[p->size+1+i] = rs->ptr[i];
                    
                    p->size = p->size + rs->size + 1;
                    insideRemove(parent->key[right-1], parent);
                    return;
                }
            }
        }
    }
    return;
    
};

template<typename T>
Node<T>* BPlusTree<T>::findParent(Node<T>* p, Node<T>* child){
    if(p->isleaf)  return NULL; //root only
    Node<T>* parent = NULL;
    
    for(int i = 0; i < p->size+1; i++){
        if (p->ptr[i] == child)  return p;
        else{
            parent = findParent(p->ptr[i], child);
            if(parent != NULL) return parent;
        }
    }
    
    return NULL;
};

template<typename T>
void BPlusTree<T>::print(Node<T>* p){
    if(p == NULL) return;
    
    cout << "[ ";
    for(int i = 0; i < p->size; i++)
        cout << p->key[i]<<" ";
    
    if(!p->isleaf){
        cout << " : < ";
        for(int i = 0; i < p->size+1; i++)
                print(p->ptr[i]);
        
        cout << " > " ;
    }
    cout << "] " ;
    
};

void test0();
void test1();
void test2Time();
void test3Char();


int main(){
    test1();
    test2Time();
    test3Char();
    test0();
    
    return 0;
};

void test0(){
    cout << "----------- Test0, initialize with 50 int. -----------" << endl;
    BPlusTree<int> bpt;
    for(int i = 1; i < 50; i++){
        bpt.insert(i);
    }
    
    bpt.print(bpt.root);
    cout << endl << endl;
};

void test1(){
    cout << "----------- Test1, test search, remove and insert. -----------" << endl;
    BPlusTree<int> bpt;
    bpt.insert(1);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(3);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(19);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(7);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(9);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(11);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(13);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(15);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(17);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(5);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(23);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(25);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(27);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(29);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(31);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(33);
    bpt.print(bpt.root);
    cout << endl;
    
    bpt.remove(31);
    bpt.print(bpt.root);
    cout << endl;
    bpt.remove(2);
    bpt.print(bpt.root);
    cout << endl;
    bpt.remove(11);
    bpt.print(bpt.root);
    cout << endl;
    bpt.remove(29);
    bpt.print(bpt.root);
    cout << endl;
    bpt.remove(29);
    bpt.print(bpt.root);
    cout << endl << endl;
    
    bpt.search(27);
    bpt.search(29);
    
}


void test2Time(){
    cout << "----------- Test2, test delay. -----------" << endl;
    BPlusTree<int> bpt;
    bpt.insert(1);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(3);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(5);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(7);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(9);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(11);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(13);
    bpt.print(bpt.root);
    cout << endl;
    bpt.insert(15);
    bpt.print(bpt.root);
    cout << endl;
    
    cout << "Insert " << memory40[0] << " outside." << endl;
    usleep(20);
    bpt.insert(memory40[0]);
    bpt.print(bpt.root);
    cout << endl;
    
    cout << "Remove " << memory40[0] << " outside." << endl;
    usleep(20);
    bpt.remove(memory40[0]);
    bpt.print(bpt.root);
    cout << endl;
}

void test3Char(){
    cout << "----------- Test3, test template. -----------" << endl;
    BPlusTree<char> bpt;
    bpt.insert('a');
    bpt.insert('b');
    bpt.insert('c');
    bpt.insert('g');
    bpt.insert('d');
    bpt.insert('z');
    bpt.insert('w');
    bpt.print(bpt.root);
    cout << endl;
    
    bpt.remove('a');
    bpt.print(bpt.root);
    cout << endl;
}