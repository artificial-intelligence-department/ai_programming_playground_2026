#include <iostream>
using namespace std;

void reorder(int *b, int len)
{
    int *ptr = b;
    int count = 0;
    for (int i = 0; i < len; i++){
        if (*(ptr + i) % 2 == 0){
            count++;
        }
    }

    bool good = false;
    if (count == len/2 || count+1 == len/2 || count-1 == len/2){
        good = true;
    } else if (!good){
        cout << -1 << endl;
    }

    if (good){
        for (int i = 0; i < len; i++){
            for (int j = 1; j < len; j++){
                if ((*(ptr + i) + *(ptr + j)) % 2 != 0){
                    swap(*(ptr + j-1), *(ptr + j));
                }
            }
        }
    }

    for (int i = 0; i < len; i++){
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}

int main()
{
    int a[1000000] = {0};
    int n;
    cin >> n;
    int *b = new int[n];
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }
    reorder(b, n);
    delete[] b;
    return 0;
}