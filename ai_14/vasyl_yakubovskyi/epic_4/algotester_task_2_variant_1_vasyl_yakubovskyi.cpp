/*
Task 2 from algotester option 1
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>

using namespace std;

int main (){
    long long N = 0; 
    cin >> N;
    if(N < 1) return 0;

    long long *a = new long long[N];
    for(long long i = 0; i < N; i++) {
        cin >> a[i];
        if(a[i] < 0){
            delete [] a;
            a = nullptr;
            return 0;
        }
    }
   
    //сортуємо масив
    for(long long i = 1; i < N; i++){
        long long temp = a[i];
        long long j = i - 1;

        while(j >= 0 && a[j] > temp){
            a[j+1] = a[j];

            j--;
        }
        a[j+1] = temp;

    }
    long long m = 0;
    if(N != 1){

    long long option1 = a[N-1] - a[1];
    long long option2 = a[N-2] - a[0];
    if(option1 < option2){
            m = option1;
        }else{
            m = option2;
        }
    }
    


    cout << m << endl;;

    delete[] a;
    a = nullptr;

    return 0;
}