
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
using namespace std;

int main() {

    int N;
    cin >> N;

    int* array = new int[N];

    for (int i = 0; i < N; i++) {
        cin >> array[i];
    }

    int a, b, c;
    cin >> a >> b >> c;

    int* filtered = new int[N];
    int count = 0; // count рахує і показує, куди класти наступне

    for (int i = 0; i < N; i++) {
        if (array[i] != a && array[i] != b && array[i] != c) {
            filtered[count] = array[i];
            count++;
        }
    } 

    if (count < 2) {
        cout << "0" << endl;
        delete[] array;
        delete[] filtered;
        return 0;
    } else {
        // пар сусідів на одну менше, ніж чисел, тому сум рівно count - 1
        int* sum = new int[count - 1];
        for (int i = 0; i < count - 1; i++) {
            sum[i] = filtered[i] + filtered[i + 1];
        }
         cout << count - 1 << endl;

    for (int i = 0; i < count - 1; i++) {
        cout << sum[i] << " ";
       }
       cout << endl;
       delete[] sum;
    }

    delete[] array;
    delete[] filtered;

    return 0;
}