/*
algotester task 3 variant 2, Андрій Мадяр
*/
#include <iostream>
using namespace std;
bool contains(int a[], int s, int b){//функція на перевірку унікальності елемента
    for(int i = 0; i<s; i++){
        if(a[i] == b)return true;
    }return false;
}

int main(){
    int N=0, M=0;
    cin >> N;
    int count1 = 0, count2 = N;//кожен елемент першої множини вже є унікальним
    //створення динамічних масивів і ввід елементів у них
    int* A = new int[N];
    for(int i = 0; i<N; i++){
        cin >> A[i];
    }
    cin >> M;
    int* B = new int[M];
    for(int i = 0; i<M; i++){
        cin >> B[i];
    }
    if(N>M){//ми не знаємо яка множина більша тому два випадки перерізу
        for(int i = 0; i<N; i++){
            if(contains(B, M, A[i]))count1++;
        }
    }else{
        for(int i = 0; i<M; i++){
            if(contains(A, N, B[i]))count1++;
        }
    }
    for(int i = 0; i<M; i++){//по факту об'єднання
        if(!contains(A, N, B[i]))count2++;
    }
    cout << count1 << "\n" << count2;
    delete[] A;//видаляю масиви
    delete[] B;
    return 0;
}