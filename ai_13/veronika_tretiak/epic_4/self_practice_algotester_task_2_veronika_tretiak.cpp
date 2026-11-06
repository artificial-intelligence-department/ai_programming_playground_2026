/*
Задача: Найбільша пара
*/
#include <iostream>

using namespace std;

void swapValues(int* a, int* b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubblesort(int* arr, int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - 1 - i; j++){
          if(arr[j] > arr[j + 1]){
            swapValues(&arr[j], &arr[j + 1]);
          }
        }
    }
}

long long MaxSum(int* arr, int size){
    long long max = (long long)arr[0] + arr[size - 1];
    for(int i = 1; i < size/2; i++){
        long long Sum = (long long)arr[i] + arr[size - 1 - i];
        if(Sum > max){
            max = Sum;
        }
    }
    return max;
}

int main(){
   int n;
   cin >> n;
   int* numbers = new int[n];
   for(int i = 0; i < n; i++){
    cin >> numbers[i];
   }
   bubblesort(numbers, n);

   long long answer = MaxSum(numbers, n);
   cout << answer << "\n";

   delete[] numbers;
   numbers = nullptr;
   return 0;

}