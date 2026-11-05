#include <iostream>
using namespace std;

void sortVstavka(int *b, int n)
{
    int x;
    int j;
    for (int i = 1; i < n; i++){
        x = b[i];
        j = i - 1;
        while (x < b[j] && j >= 0){
            b[j+1] = b[j];
            j--;
        }
        b[j+1] = x;
    }
    for (int i = 0; i < n; i++){
        cout << b[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n = 0;
    int a[10001] = {0};
    int num;
    while (cin >> num){
        a[n] = num;
        n++;
    }
    sortVstavka(a, n);
    return 0;
}