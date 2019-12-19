
/*
Lab Work 09-1. Double Hashing

Note. Programming in C/C++, including <iostream>/<iostream.h> and <cstdlib>/<cstdlib.h>only

Consider a hash table with M = 64 bins. Given a 24-bit unsigned number, take the lowest 6 bits as the primary hash function (bin number), and the highest 6 bits as the secondary hash function (jump size).

Determine the array structures for a hash table
Hash a list of 32 random 24-bit positive numbers
Calculate the average number of probes
(End)

*/


#include <iostream>
#include <stdlib.h>
#include <math.h>
#define M 64

using namespace std;

class HashTable{
private:
    //table.first: true == empty
    pair<bool,int> table[M];
    int size;
    int probes;
    
public:
    HashTable(){
        for(int i = 0; i < M; i++){
            table[i].first = true;
            table[i].second = 0;
        }
        size = 0;
        probes = 0;
    };
    
    void init(int *numbers, int n){
        size = n;
        for(int i = 0; i < size; i++){
            pair<bool, int> flag = primaryHashFunc(numbers[i]);
            if(flag.first){
                int index = flag.second;
                table[index].second = numbers[i];
                table[index].first = false;
            }else{
                int index = secondaryHashFunc(numbers[i]);
                table[index].second = numbers[i];
                table[index].first = false;
            }
        }
    }
    
    pair<bool,int> primaryHashFunc(const int num) {
        int primary = getLow6(num);
        pair<bool, int> ret;
        if(table[primary].first){
            ret.first = true;
            ret.second = primary;
            probes++;
        }else{
            ret.first = false;
            ret.second = -1;
        }
        return ret;
    }

    int secondaryHashFunc(const int num) {
        int primary = getLow6(num);
        int jumpSize = getHigh6(num);
        int ret = primary;
        int cnt = 1;
        while(!table[ret].first){
            if(jumpSize % 2 == 1){
                ret = (primary + cnt*jumpSize) & (M-1);
            }else{
                jumpSize = jumpSize | 1;
                ret = (primary + cnt*jumpSize) & (M-1);
            }
            cnt++;
            probes++;
        }
        
        return ret;
    }
    
    double getProbes()const{
        return 1.0*probes/size;
    }
    
    void print(){
        for(int i = 0; i < M; i++){
            if(!table[i].first){
                cout << i << ": " << table[i].second << endl;
            }
        }
        cout << endl;
    }
    
    int getLow6(int data) const{
        return data & 0x3f;
    }
    
    int getHigh6(int data) const{
        return data >> 26;
    }
};


int main(){
    
    int num[32];
    for(int i = 0; i < 32; i++){
        num[i] = rand()%10000000 ;
    }
    
    HashTable table;
    table.init(num, 32);
    table.print();
    cout << "average number of probes: " << table.getProbes() << endl;
     
        
    return 0;
}

