/* Задача "Ліки для тома"
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/81423
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void countingSort(int arr[], int n) {
    int max = 1000;
    int count[max + 1] = {0};

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= max) {
            count[arr[i]]++;
        }
    }

    int index = 0;
    for (int v = max; v>=0; v--) {
        while (count[v] > 0) {
            arr[index++] = v;
            count[v]--;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    int arr[n];

    for (int i = 0; i<n; i++){
        cin >> arr[i];
    }

    countingSort(arr, n);

    double log2_x = log2(x), time = 0;
    int current = 0, sum = 0;
    while (current!=n){
        sum+=arr[current];
        current++;
        if (sum<=x) continue;
        time+=log2(sum)-log2_x;
        sum=x;
    }
    
    cout << fixed << setprecision(10)<< time;
    return 0;
}