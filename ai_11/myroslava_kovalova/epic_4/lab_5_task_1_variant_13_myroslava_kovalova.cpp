/* Лабораторна робота 5, завдання 1, варіант 13
Ковальова Мирослава
ШІ-11
*/
#include <iostream>
using namespace std;

float leftSum(float **arr,int rows,int k){
    float sum = 0;
    for(int i = 0;i<rows;i++){
        for(int j = 0; j<k; j++){
            sum+=arr[i][j];
        }
    }
    return sum;

}
float rightSum(float **arr,int rows,int cols, int k){
    float sum = 0;
    for(int i = 0;i<rows;i++){
        for(int j = k+1; j<cols; j++){
            sum+=arr[i][j];
        }
    }
    return sum;
}
void printArr(float **arr, int rows, int cols){
    for (int i =0; i<rows;i++){
        cout<<"\n";
        for (int j = 0; j<cols; j++){
            cout<<arr[i][j]<<" ";
        }
    }
}
int main(){

    int rows = 0,cols =0;
    while(true){
        cout<<"Введіть кількість рядків та колонок через пробіл\n";
        cin>>rows>>cols;
        if (rows>=1 && cols>=3 && !cin.fail()) break;
        else{
            cout<<"Введіть цілі числа більші за нуль. Кількість колонок мінімум 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    float **arr= new float*[rows];
    for (int i = 0; i<rows;i++){
        arr[i]= new float[cols];
    }
   
    cout<<"Введіть масив\n";
    for (int i = 0; i<rows;i++){
         for (int j =0;j<cols; j++){
            cin>>arr[i][j];
        }
    }
       
   
    printArr(arr, rows, cols);

    bool found = false;
    for(int k = 1; k<cols-1; k++){
        if (rightSum(arr, rows,cols, k)<leftSum(arr, rows, k)){
            cout<<"\nМожливо. Розбиття по "<<k+1<<" стовпцю.\n";
            found = true;
            break;
        }
    }
    if(!found) cout<<"\nНеможливо\n";
    
    //Звільнення динамічно виділеної пам'яті
    for (int i = 0; i<rows;i++){
        delete[] arr[i];
    }
    delete[] arr;
    arr=nullptr;
    
    return 0;
}