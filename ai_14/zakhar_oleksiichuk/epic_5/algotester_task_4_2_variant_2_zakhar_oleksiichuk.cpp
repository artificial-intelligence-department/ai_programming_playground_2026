#include <iostream>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    int a[N];
    int un_arr_count = 0;
    bool numFound[101] = {0};
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (numFound[a[i]] == false) un_arr_count++;
        numFound[a[i]] = true;
    }
    
    int* unique_arr = new int[un_arr_count];
    int un_arr_ind = 0;
    for (int i = 0; i < 101; i++) {
        if (numFound[i] == true) {
            unique_arr[un_arr_ind] = i;
            un_arr_ind++;
        }
    }
    
    int moveTimes = K % un_arr_count;
    int* movedArr = new int[un_arr_count];
    int movedArrInd = 0;
    for (int i = moveTimes; i < un_arr_count; i++) {
        movedArr[movedArrInd] = unique_arr[i];
        movedArrInd++;
    }
    for (int i = 0; i < moveTimes; i++) {
        movedArr[movedArrInd] = unique_arr[i];
        movedArrInd++;
    }
    
    cout << un_arr_count << endl;
    for (int i = 0; i < un_arr_count; i++) {
        cout << movedArr[i] << " ";
    }
    
    delete[] unique_arr;
    delete[] movedArr;
    return 0;
}