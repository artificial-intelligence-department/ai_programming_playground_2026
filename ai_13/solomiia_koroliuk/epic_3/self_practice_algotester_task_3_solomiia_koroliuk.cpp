/* Task 1872: Складний екзамен */

#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(vector<long long>& arr);

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    bubble_sort(a);

    // for (int i = 0; i < n; i++) {
    //     cout << a[i] << " ";
    // }
    // cout << endl;

    long long max_sum = 0;
    int left = 0;
    int right = n - 1;

    while (left < right) {
        long long current_sum = a[left] + a[right];
        if (current_sum > max_sum) max_sum = current_sum;
        
        left ++;
        right--;
    }

    cout << max_sum;

    return 0;
}

void bubble_sort(vector<long long>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++){
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
    
}
