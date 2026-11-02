#include <iostream>
using namespace std;

void arithmetic_mean(int n, int a[][4], float *sum, int column){
    for(int i =0; i <n; i++){
        *sum += a[i][column -1];
    }
    *sum /= n;
    cout << "Середнє арифметичне " << column << "-го стовпця дорівнює " << *sum << endl;
}

void arithmetic_much(float *sum, int n, int a[][4]){
    int number = 0;
    for(int i =1; i <4; i++){
        arithmetic_mean(n, a, sum, i);
        for(int j =0; j <n; j++){
            if(a[j][i] > *sum){
                number++;
            }
        }
        cout << "У " << i+1 << " стовпці елементів, що перевищують середнє арифметичне попереднього, є рівно " << number << endl; 
        number = 0;
        cout << endl;
        *sum = 0;
    }   
}


int main(){

    float sum_a =0; //середнє арифметичне заданого стовпця
    const int n = 5, k = 4;
    int a[n][k] = {
        { 4, 12,  5,  3},
        { 8,  1, 14, 20},
        { 7,  7,  2, 10},
        { 2,  9,  6, 13},
        { 4, 18, 10,  9}
    };
    arithmetic_much(&sum_a, n, a);

    return 0;
}