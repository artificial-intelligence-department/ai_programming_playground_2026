#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    
    int sum = 0;
    string *arr = new string[N];
    
    for (int i = 0; i < N; i++) {
        getline(cin, arr[i]);
    }
    
    for (int i = 0; i < N; i++) {
        bool is_damaged = false;
        
        for (char c : arr[i]) {
            if (c == '#' && !is_damaged) {
                sum++;
                is_damaged = true;
            } else if (c != '#') {
                is_damaged = false; 
            }
        }
    }
    
    cout << sum;
    delete[] arr;
    return 0;
}