#include <iostream>

using namespace std;

const int bits = 8;

 void freeRows(int **&rows){
    for(int i = 0; i < bits; i++){
        delete[] rows[i];
        rows[i] = nullptr;
    }
    delete[] rows;
    rows = nullptr;
 }

 void input(int **rows, int l){
    for(int i = 0; i < bits; i++){
        for(int j = 0; j < l; j++){
            cin >> rows[i][j];
        }
    }
 }

 bool same(int *a, int *b, int l){
    for(int i = 0; i < l; i++){
        if(*(a + i) != *(b + i)) return false;
    }
    return true;
 }

 int number(int **rows, int l){
    int n = 0;
    int step = 1;
    for(int i = 0; i < bits; i++){
        if(same(rows[i], rows[bits - 1], l) == false) n += step;
        step *= 2;
    }
    return n;
 }

int main(){
    int l = 0;
    cin >> l;

    int **rows = new int*[bits];
    for(int i = 0; i < bits; i++){
        rows[i] = new int[l];
    }

    input(rows, l);
    cout << number(rows, l) << endl;

    freeRows(rows);

    return 0;
}
