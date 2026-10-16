/* Задача "Папероні"
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/81393
Автор: Давидович Святослав
Група: ШІ-11
*/

/* Ідея: перший циклічний зсув починається з 1, другий - з наступного елемента.
таким чином, LIS в першому випадку утворюється додаванням 1 на початку другого, тобто є довшим*/
#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int arr[n];
    int id1 = 0;

    for (int i = 0; i<n; i++){
        int num;
        cin >> num;
        if (num == 1) id1 = i;
        arr[i] = num;
    }

    for (int i = 0; i < n; i++) {
        cout << arr[(id1 + i) % n] << " ";
    }
    cout << "\n";

    int id2 = (id1 + 1) % n;
    for (int i = 0; i < n; i++) {
        cout << arr[(id2 + i) % n] << " ";
    }
    cout << "\n";

    return 0;
}