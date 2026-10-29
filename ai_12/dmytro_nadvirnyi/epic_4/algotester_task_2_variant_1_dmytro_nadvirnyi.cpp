#include <iostream>
using namespace std;

int road(int n, int arr[]){
    for(int i=0; i<n; i++){
        cin>> arr[i];
    }
    return 0;
}
int Exhausted(int n, int arr[], int skipIndex) {
    int Min, Max;
    bool first = true;

    for (int i = 0; i < n; i++) {
        if (i == skipIndex) continue;

        if (first) {
            Min = Max = arr[i];
            first = false;
        }

        if (arr[i] < Min) Min = arr[i];
        if (arr[i] > Max) Max = arr[i];
    }

    return Max - Min;
}
int MinExhausted(int n, int arr[]) {
    int minIndex = 0;
    int maxIndex = 0;
    if (n == 1) return 0; // якщо масив містить лише один елемент, повертаємо 0
    for (int i = 0; i < n; i++) {
        if(arr[i]<arr[minIndex]) minIndex = i; // знайди індекс мінімального елемента
        if(arr[i]>arr[maxIndex]) maxIndex = i; // знайди індекс максимального елемента
    }
    int a = Exhausted(n, arr, minIndex);
    int b = Exhausted(n, arr, maxIndex);
    if(a < b) return a;
    else return b;
}


int main(){
    int arr[100000];
    int n;
    cin >> n;
    road(n, arr);
    cout << MinExhausted(n, arr);


    return 0;
}