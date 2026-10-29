/*Epic 4 - Веселі каруселі
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

void insertionSort(int* arr, int n){
    for(int i = 0; i < n; i++){
        int key = *(arr + i);
        int j = i - 1;
        
        while(j>=0 && *(arr+j)>key){
            *(arr + j + 1) = *(arr + j);
            j--;
        }
        *(arr + j + 1) = key;
    }
}

int count(int* arr, int n, int budget){
    insertionSort(arr, n);
    
    int count = 0;
    int current_sum = 0;
    
    // Рахуємо к-сть атракціонів
    for(int i = 0; i < n; i++){
        if(current_sum + *(arr + i) <= budget){
            current_sum += *(arr + i);
            count++;
        } else {
            break;
        }
    }    
    return count;
}

int main(){
    int k, n;
    cin >> k >> n;
    
    int* prices = new int [n];
    for(int i = 0; i < n; i++){
        cin >> *(prices + i);
    }
    
    int result = count(prices, n, k);
    cout << result << endl;
    delete[] prices;
    return 0;
}