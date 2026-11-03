#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>

using namespace std;

void printArr(int arr[], int N);

int main() {
    srand(time(nullptr));
    int N=100;
    int arr[N];
    int smaller_array[N];
    int final_array[2*N];

    while(true){
        cout<<"Введіть число: ";      
        if(!(cin>>N)||N>100||N<=0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Неправильний ввід, спробуйте ще раз"<<endl;
        }else break;
    }
    for (int i = 0; i < N; i++){
        arr[i]=rand() % 201 - 100;
    }
    printArr(arr, N);

    int N_for_smaller_array=0;
    for (int i = 0; i < N; i++){      
        if(i%3!=0){
            N_for_smaller_array++;
        }
    }

    for (int i = 0, j = 0; i < N; i++){
        if(i%3!=0){
            smaller_array[j]=arr[i];
            j++;
        }
    }
    int number_of_minuses=0;
    for (int i = 0; i < N_for_smaller_array; i++){
        if(smaller_array[i]<0){
            number_of_minuses++;
        }
    }
    int final_number=N_for_smaller_array + number_of_minuses;
        for (int i = 0, j = 0; i < final_number; i++,j++){
            final_array[i]=smaller_array[j];
            if(final_array[i]<0){
                i++;
                final_array[i]=abs(final_array[i-1]+1);
            }
            
        }

    printArr(final_array, final_number);

    }

void printArr(int arr[], int N){

    for (int i = 0; i < N; i++){
        if(i==N-1){
            cout<<arr[i]<<endl;
        }else{
             cout<<arr[i]<<", ";
        }
    }
}