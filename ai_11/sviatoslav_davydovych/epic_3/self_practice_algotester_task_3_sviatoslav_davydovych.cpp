/* Задача "Офіс для домашніх тварин"
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/81420
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c = 0;
    cin >> n;
    int arr[n];

    for (int i = 0; i<n; i++){
        cin >> arr[i];
    }

    for (int i = 1; i<n-1; i++){
        int sign = arr[i]>=arr[i+1] ? 1: -1;
        if(arr[i-1]==arr[i]){
            arr[i]+=sign;
            c++;
        }
    }
    if (arr[n-1]==arr[n-2]) c++;

    cout << c;

    return 0;
}