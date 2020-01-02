/*
Lab Work 10-1. Implementation of Topological Sorting

 Refer to the example of digraph and data structures in Lecture 22, slide 45.
 * Represent the digraph with an Adjacency List
 * Determine the data structures for the process of improved topological sorting
 * Design a C/C++ program implementing the improved topolofical sorting.
 
 */

#include <iostream>
#define MAXSIZE 20

using namespace std;


class Graph{
public:
    class ENode{
    public:
        char vex;
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
    pair<char, int> arrOfEdge[12];
    
public:
    Graph(){
        nodeNum = 12;
        edgeNum = 16;
        
        char tmp = 'A';
        for(int i = 0; i < 12; i++){
            ajlist[i].data = tmp;
            arrOfEdge[i].first = tmp;
            tmp++;
            ajlist[i].firstEdge = NULL;
            arrOfEdge[i].second = 0;
        }
        
        char edges[][2] = {
            {'A', 'B'},
            {'B', 'E'},
            {'C', 'D'},
            {'D', 'A'},
            {'D', 'E'},
            {'D', 'F'},
            {'F', 'E'},
            {'F', 'G'},
            {'F', 'K'},
            {'G', 'E'},
            {'G', 'L'},
            {'H', 'D'},
            {'H', 'I'},
            {'I', 'J'},
            {'J', 'F'},
            {'K', 'L'}
        };
        
        ENode* node ;
        
        for(int i = 0; i < edgeNum; i++){
            node = new ENode();
            node->vex = edges[i][1];
            node->nextEdge = NULL;
            addArrOfEdges(edges[i][1]);
            
            int index = getIndexByChar(edges[i][0]);
            if(ajlist[index].firstEdge == NULL)
                ajlist[index].firstEdge = node;
            else{
                addNode(ajlist[index].firstEdge, node);
            }
        }
        
    }
    
    void addNode(ENode* n1, ENode* n2){
        ENode*n = n1;
        while(n->nextEdge){
            n = n->nextEdge;
        }
        n->nextEdge = n2;
    }
    
    void addArrOfEdges(char ch){
        for(int i = 0; i < nodeNum; i++){
            if(arrOfEdge[i].first == ch)
                arrOfEdge[i].second++;
        }
    };
    
    void subArrOfEdges(char ch){
        //ch is vex
        int flag = 0;
        for(int i = 0; i < nodeNum; i++){
            if(ajlist[i].data == ch){
                flag = i;
                break;
            }
        }
        ENode* tmp = ajlist[flag].firstEdge;
        while(tmp != NULL){
            for(int i = 0; i < nodeNum; i++){
                if(arrOfEdge[i].first == tmp->vex && arrOfEdge[i].second != 0){
                    arrOfEdge[i].second--;
                    break;
                }
            }
            tmp = tmp->nextEdge;
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
                cout << " -> " << tmp->vex;
                tmp = tmp->nextEdge;
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void printArr(){
        for(int i = 0; i < nodeNum; i++){
            cout << arrOfEdge[i].first << ": " << arrOfEdge[i].second << endl;
        }
    }
};

bool checkRes(char *res, char ch, int size){
    for(int i = 0; i <size; i++){
        if(res[i] == ch)
            return false;
    }
    return true;
}

void topologicalSort(Graph& g){
    int nodeNum = g.nodeNum;
    char res[nodeNum];
    int cnt = 0;
    
    while(!g.isArrEmpty()){
        for(int i = 0; i < nodeNum; i++){
            if (g.arrOfEdge[i].second == 0 && checkRes(res, g.arrOfEdge[i].first,nodeNum)) {
                res[cnt++] = g.arrOfEdge[i].first;
                g.subArrOfEdges(g.arrOfEdge[i].first);
            }
        }
    }
    
    cout << "After sorting: " << endl;
    for(int i = 0; i < nodeNum; i++){
        cout << res[i] << " " ;
    }
    cout << endl;
    
}


int main(){
    
    Graph g;
    g.print();
    g.printArr();
    topologicalSort(g);
    
    
    
    return 0;
}

/*
A -> B
B -> E
C -> D
D -> A -> E -> F
E
F -> E -> G -> K
G -> E -> L
H -> D -> I
I -> J
J -> F
K -> L
L

A: 1
B: 1
C: 0
D: 2
E: 4
F: 2
G: 1
H: 0
I: 1
J: 1
K: 1
L: 2
After sorting: 
C H I J D F G K L A B E 
Program ended with exit code: 0
*/