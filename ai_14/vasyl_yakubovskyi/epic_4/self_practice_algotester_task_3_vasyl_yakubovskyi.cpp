/*
Task: self_practice_algotester_task_2 (Лотарея)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>

using namespace std;


int main (){

    int n = 0; //рядки
    int m = 0; //стовпці
    cin >> n >> m;

    int **a = new int*[n];
    for(int i = 0; i < n; i++){
        a[i] = new int[m];
    }

    int the_sm_big = a[0][0];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    int the_smBig = a[0][0];
    for(int i = 0; i < m; i++){
        int the_big = a[0][i];
        for(int j = 0; j < n; j++){
            if(a[j][i] > the_big) {
                the_big = a[j][i];
            }
        }
        if(i == 0){
            the_smBig = the_big;
        }else{
            if(the_smBig > the_big){
                the_smBig = the_big;
            }
        }
    }

    cout << the_smBig << endl;

     for(int i = 0; i < n; i++){
        delete[] a[i];
    }
    delete[] a;
    a = nullptr;

    return 0;
}