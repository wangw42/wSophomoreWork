


/*
 Lab Work 11-1. Implementation of Kruskal Algorithm
 Note. Programming in C/C++, including <iostream>/<iostream.h> only

 Refer to the example of graph and data structures in Lecture 23, slide 92.

 Represent the graph with an Adjacency List
 Determine the data structures for the process of improved Kruskal algorithm
 Design a C/C++ program implementing the improved Kruskal algorithm.
 (End)
 
 */


#include <iostream>
#define MAXSIZE 30

using namespace std;


class Graph{
public:
    class ENode{
    public:
        char vex;
        int weight;
        ENode *nextEdge;
    };
    
    class VNode{
    public:
        char data;
        ENode *firstEdge;
    };
    
    int nodeNum;
    int edgeNum;
    VNode ajlist[12];
    pair<char[2], int> arrOfEdge[22];
    
public:
    Graph(){
        nodeNum = 12;
        edgeNum = 22;
        
        char tmp = 'A';
        for(int i = 0; i < nodeNum; i++){
            ajlist[i].data = tmp;
            tmp++;
            ajlist[i].firstEdge = NULL;
        }
        
        char edges[][3] = {
            {'B', 'A', 20},
            {'C', 'B', 7},
            {'D', 'A', 21},
            {'D', 'B', 13},
            {'E', 'B', 5},
            {'E', 'C', 1},
            {'E', 'D', 10},
            {'F', 'D', 14},
            {'F', 'E', 22},
            {'G', 'E', 15},
            {'G', 'F', 4},
            {'H', 'E', 6},
            {'H', 'G', 11},
            {'I', 'G', 3},
            {'I', 'H', 2},
            {'J', 'G', 19},
            {'J', 'I', 18},
            {'K', 'H', 8},
            {'K', 'I', 12},
            {'K', 'J', 17},
            {'L', 'H', 9},
            {'L', 'K', 16}
        };
        
        ENode* node ;
        
        for(int i = 0; i < edgeNum; i++){
            node = new ENode();
            node->vex = edges[i][1];
            node->nextEdge = NULL;
            node->weight = edges[i][2];
            arrOfEdge[i].first[0] = edges[i][1];
            arrOfEdge[i].first[1] = edges[i][0];
            addArrOfEdges(edges[i][1], edges[i][0], edges[i][2]);
            
            int index = getIndexByChar(edges[i][0]);
            if(ajlist[index].firstEdge == NULL)
                ajlist[index].firstEdge = node;
            else{
                addNode(ajlist[index].firstEdge, node);
            }
        }
        
        sortArrOfEdges();
    }
    
    void addNode(ENode* n1, ENode* n2){
        ENode*n = n1;
        while(n->nextEdge){
            n = n->nextEdge;
        }
        n->nextEdge = n2;
    }
    
    void sortArrOfEdges(){
        for(int i = 0; i < edgeNum-1; i++){
            for(int j = 0; j < edgeNum-1-i; j++){
                if(arrOfEdge[j].second > arrOfEdge[j+1].second){
                    char tmp[2];
                    tmp[0] = arrOfEdge[j].first[0];
                    arrOfEdge[j].first[0] = arrOfEdge[j+1].first[0];
                    arrOfEdge[j+1].first[0] = tmp[0];
                    
                    tmp[1] = arrOfEdge[j].first[1];
                    arrOfEdge[j].first[1] = arrOfEdge[j+1].first[1];
                    arrOfEdge[j+1].first[1] = tmp[1];
                    
                    char tmpInt = arrOfEdge[j].second;
                    arrOfEdge[j].second = arrOfEdge[j+1].second;
                    arrOfEdge[j+1].second = tmpInt;
                }
            }
        }
            
    }
    
    void addArrOfEdges(char ch1, char ch2, int weight){
        for(int i = 0; i < edgeNum; i++){
            if(arrOfEdge[i].first[0] == ch1 && arrOfEdge[i].first[1] == ch2)
                arrOfEdge[i].second = weight;
        }
    };
    
    int getIndexByChar(char ch){
        for(int i = 0; i < nodeNum; i++){
            if(ajlist[i].data == ch)
                return i;
        }
        return -1;
    }
    
    bool isArrEmpty(){
        for(int i = 0; i < nodeNum; i++){
            if(arrOfEdge[i].second == 0)
                continue;
            else
                return false;
        }
        return true;
    }
    
    void print(){
        for(int i = 0; i < nodeNum; i++){
            cout << ajlist[i].data;
            ENode *tmp = ajlist[i].firstEdge;
            while(tmp){
                cout << " -- " << tmp->weight << " -- " << tmp->vex;
                tmp = tmp->nextEdge;
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void printArr(){
        for(int i = 0; i < edgeNum; i++){
            cout << arrOfEdge[i].first[0] << "," << arrOfEdge[i].first[1] << ": " << arrOfEdge[i].second << endl;
        }
    }
};

class Set{
public:
    char set[MAXSIZE];
    int size = 0;
    
public:
    Set(){
        size = 0;
    }
    
    void initSet(){
        for(int i = 0; i < MAXSIZE; i++)
            set[i] = ' ';
        size = 0;
    }
    
    void push(char ch){
        set[size] = ch;
        size++;
    }
    
    bool inSet(char ch){
        for(int i = 0; i < size; i++){
            if(ch == set[i]) return true;
        }
        return false;
    }
    
    int getSize(){
        return size;
    }
    
    Set& operator =(const Set& s){
        this->size = s.size;
        for(int i = 0; i < this->size; i++){
            this->set[i] = s.set[i];
        }
        return *this;
    }
    
    void mergeSet(Set& set2){
        int size2 = set2.getSize();
        
        for(int i = 0; i < size2; i++){
            this->push(set2.set[i]);
        }
        
        set2.clearAll();
    };
    
    void clearAll(){
        for(int i = 0; i < size; i++){
            set[i] = ' ';
        }
        size = 0;
    }
    
    void printSet(){
        if(size == 0){
            cout << "NULL" << endl;
            return;
        }
        
        cout << "{ " ;
        for(int i = 0; i < size; i++){
            cout << set[i] << " ";
        }
        cout << " }" << endl;
    }
};


void printMST(Graph & g){
    int nodeNum = g.nodeNum;
    int edgeNum = g.edgeNum;
    
    Set sets[nodeNum];
    char tmpch = 'A';
    for(int i = 0; i < nodeNum; i++){
        sets[i] = *new Set();
        sets[i].initSet();
        sets[i].push(tmpch++);
        
    }
    
    pair<char[2], int> res[nodeNum];
    int cntRes = 0;
    
    for(int i = 0; i < edgeNum; i++){
        char ch1 = g.arrOfEdge[i].first[0];
        char ch2 = g.arrOfEdge[i].first[1];
        
        Set set1;
        Set set2;
        int flag1 = 0, flag2 = 0;
        for(int j = 0; j < nodeNum; j++){
            
            if(sets[j].inSet(ch1)) {
                set1 = sets[j];
                flag1 = j;
            }
            if(sets[j].inSet(ch2)) {
                set2 = sets[j];
                flag2 = j;
            }
        }
        
        if(flag2 == flag1){
            continue;
        }else{
            res[cntRes].first[0] = ch1;
            res[cntRes].first[1] = ch2;
            res[cntRes++].second = g.arrOfEdge[i].second;
            
            sets[flag1].mergeSet(sets[flag2]);
        }
        
        /*
        for(int k = 0; k < nodeNum; k++){
            sets[k].printSet();
        }
         */
        
    }
    
    cout << "Minimum Spanning Tree:" << endl;
    for(int i = 0; i < cntRes; i++){
        cout << res[i].first[0] << "," << res[i].first[1] << ": " << res[i].second << endl;
    }
    
};


int main(){
    
    Graph g;
    cout << "Graph:" << endl;
    g.print();
    cout << "All edge after sorting: "<< endl;
    g.printArr();
    
    printMST(g);
    
    
    return 0;
}
