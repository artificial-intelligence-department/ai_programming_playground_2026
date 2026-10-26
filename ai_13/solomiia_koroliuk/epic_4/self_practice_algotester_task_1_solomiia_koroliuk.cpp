/* Task 2461 - Найдовший зростаючий підмасив*/

#include <iostream>

using namespace std;

int main(){

    int max_len = 1;
    int current_len = 1;

    int n;
    cin >> n;
    int a[n];

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 1; i < n; i++){
        if (a[i] > a[i - 1]){
            current_len++;
        }
        else 
        {
            max_len = max(max_len, current_len);
            current_len = 1;
        }
    }
    max_len = max(max_len, current_len);

    cout << max_len;

    return 0;
}