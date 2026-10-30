/*
Задача : Лабораторна задча №4 варіант 25
Виконав : Андрій Шикоряк ШІ-13
*/
#include <iostream>
using namespace std;
int main()
{
    int K,N;
    cout << "Введіть кількість елементів: ";
    cin >> N;
    int N_for_new_array = N;
    cout << "Введіть номер елемента: " ;
    cin >> K;
    if(K>=N){
        cout << "Введено невірний індекс, за правилом кільця індекс буде 0" << endl;
        K = 0;
    }
    else if(K < 0){
        cout << "Введено невірний індекс, за правилом кільця індекс буде "<<N-1 << endl;
        K = N - 1;
    }
    int K_for_new_array = K;
    int* A = new int[N];
    cout << "Введіть елементи масиву: ";
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int N_for_K = N;
    cout << "Виведення елементів по колу: ";
    while(N > 0){
        if(K<0){
            K = N_for_K-1;
        }
        cout << A[K] << " ";
        K--;
        N--;
    }
    cout << endl;
    int min_value = A[0];
    int* new_array = new int[N_for_new_array];
    int even_counter = 0;
    for (int i = 0; i < N_for_new_array; i++) {
        for (int j = 0; j < N_for_new_array - i - 1; j++) {
            if(A[j] < A[j+1]){
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
    int index = 0;
    for (int i = 0; i < N_for_new_array; i++){
        if(A[i] % 2 == 0){ 
            even_counter++;
            new_array[index] = A[i];
            index++;
        }
    }
    if(K_for_new_array<0 || K_for_new_array >= even_counter){
            K_for_new_array = even_counter-1;
        }
    cout << "Виведення готового масиву по колу: ";
    int steps = even_counter;
    while(steps>0){
        if(K_for_new_array<0){
        K_for_new_array = even_counter-1;
        }
        cout << new_array[K_for_new_array] << " ";
        K_for_new_array--;
        steps--;
    }
    
    delete[] A;
    delete[] new_array;
    
    return 0;
}