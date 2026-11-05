#include <iostream>
using namespace std;

int main()
{
    int n = 100;
    int a[n] = {0};
    int len;
    cin >> len;
    for (int i = 0; i < len; i++){
        cin >> a[i];
    }
    int k;
    int last;

    cin >> k >> last;
    cout << "Вліво: " << endl;
    do {
        cout << a[k] << " ";
        k--;
        if (k == -1) k = len-1;
    } while (k != last);
    cout << endl;

    cout << "Додати перший і останній елементи: " << endl;
    cin >> k >> last;
    int *ptr = &a[len];
    *ptr = k;
    for (int i = 0; i < len; i++){
        *(ptr + i + 1) = a[i];
    }
    len = len + 2;
    *(ptr + len-1) = last;

    cout << "Вправо: " << endl;
    cin >> k >> last;
    do {
        cout << *(ptr + k) << " ";
        k = (++k % len);
    } while (k != last);
    cout << endl;
    return 0;
}