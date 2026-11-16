#include <iostream>
#include <algorithm> 

using namespace std;


int removeduplicates(int arr[], int n) {
    if (n == 0) return 0;
    int* new_end = unique(arr, arr + n); 
    return new_end - arr;
}

int main() {
    int n; 
    cin >> n;


    int a0[n], a1[n], a2[n];
    int zero = 0, one = 0, two = 0;

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        int rem = val% 3; 

        if (rem == 0) {
            a0[zero++] = val;
        } else if (rem == 1) {
            a1[one++] = val;
        } else {
            a2[two++] = val;
        }
    }

   
    sort(a0, a0 + zero);                      
    sort(a1, a1 + one, greater<int>());      
    sort(a2, a2 + two);                     

    
    int newsize0 = removeduplicates(a0, zero);
    int newsize1 = removeduplicates(a1, one);
    int newsize2 = removeduplicates(a2, two);

    cout << newsize0 + newsize1 + newsize2 << "\n";

    for (int i = 0; i < newsize0; i++) cout << a0[i] << " ";
    for (int i = 0; i < newsize1; i++) cout << a1[i] << " ";
    for (int i = 0; i < newsize2; i++) cout << a2[i] << " ";
    cout << "\n";

    return 0;
}