/* 
Задача: Нечесний розподіл
*/ 
#include <iostream>

using namespace std;

void MinMax (int* arr, int size, int &minimum, int &maximum){
    minimum = *arr;
    maximum = *arr;
    for(int i = 1; i < size; i++){
        int value = *(arr +i );

        if(value < minimum){
            minimum = value;
        }
        if(value > maximum){
            maximum = value;
        }
    }
}

int main(){
  int* numbers = new int[4];
  int sum = 0;
  
  for(int i = 0; i < 4; i++){
    cin >> numbers[i];
    sum += numbers[i];
  }

  int minimum, maximum;
  MinMax(numbers, 4, minimum, maximum);

  int mSum = minimum + maximum;
  int zSum = sum - mSum;

  if(mSum > zSum){
    cout << "Marichka";
  } 
  else if( zSum > mSum){
    cout << "Zenyk";
  }
  else {
    cout << "Love always wins";
  }
  delete[] numbers;
  numbers = nullptr;
  return 0;
}
