/*
    Задача: Цікавий масив
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
using namespace std;

int main(){
    int n, a[100];

    cin >> n;

    int sum=0;
    for (int i=0; i <n; i++){
        cin >> a[i];
        sum += a[i];
    }
    
    int left = 0;
    bool answer = false;
    
    for (int i = 0; i < n - 1; i++){
        left += a[i];
        int right = sum - left;

        if (left == right){
            answer = true;
            break;
        }
    }
    cout << (answer ? "TAK" : "NI" );
 
    return 0;
}