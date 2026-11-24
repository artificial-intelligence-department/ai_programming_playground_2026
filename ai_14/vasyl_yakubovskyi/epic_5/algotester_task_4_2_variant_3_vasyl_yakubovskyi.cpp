/*
Task 3 lab 4v3()
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>

using namespace std;

const int MAXSIZE = 1000;

void quickSort(int a[], int begin, int end, bool ascending = true) {
    if (begin >= end) return;

    int i = begin;
    int j = end;
    int pivot = a[begin + (end - begin) / 2];

    while (i <= j) {
        if (ascending) {
            while (a[i] < pivot) i++;
            while (a[j] > pivot) j--;
        } else {
            while (a[i] > pivot) i++;
            while (a[j] < pivot) j--;
        }

        if (i <= j) {
            int temp = a[i]; 
            a[i] = a[j]; 
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (begin < j) quickSort(a, begin, j, ascending);
    if (i < end) quickSort(a, i, end, ascending);
}

void My_partipition(int *a, int len){
    int new_a[len];
    int count_new_a = 0;


    for(int i = 0; i < len; i++){
        bool isexist = false;
        if(a[i] % 3 == 0){
            for(int j = 0; j < count_new_a; j++){
                if(new_a[j] == a[i]) {
                    isexist = true;
                    break;
                }
            }
            if(!isexist){
                new_a[count_new_a] = a[i];
                count_new_a++;
            }
        }
    }


    quickSort(new_a, 0, count_new_a - 1);

    int current_count = count_new_a;

    for(int i = 0; i < len; i++){
        bool isexist = false;
        if(a[i] % 3 == 1){
            for(int j = 0; j < count_new_a; j++){
                if(new_a[j] == a[i]) {
                    isexist = true;
                    break;
                }
            }
            if(!isexist){
                new_a[count_new_a] = a[i];
                count_new_a++;
            }
        }
    }

    quickSort(new_a, current_count, count_new_a - 1, false);

    current_count = count_new_a;

    for(int i = 0; i < len; i++){
        bool isexist = false;
        if(a[i] % 3 == 2){
            for(int j = 0; j < count_new_a; j++){
                if(new_a[j] == a[i]) {
                    isexist = true;
                    break;
                }
            }
            if(!isexist){
                new_a[count_new_a] = a[i];
                count_new_a++;
            }
        }
    }

    quickSort(new_a, current_count, count_new_a - 1);

    cout << count_new_a << endl;

    for(int i = 0; i < count_new_a; i++){
        cout << new_a[i] << " ";
    }
    cout << endl;

}

int main ( ){
    int n = 0;
    cin >> n;

    int a[MAXSIZE];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    My_partipition(a, n);

    return 0;
}