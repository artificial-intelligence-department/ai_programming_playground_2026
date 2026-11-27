/*1. Різницю N-M
2. Різницю M-N
3. Їх перетин
4. Їх обєднання
5. Їх симетричну різницю*/
#include <iostream>
using namespace std;

void printSet(int arr[], int size) {
    cout << size << endl;
    for (int i = 0; i < size; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
    cout << endl;
}

int main() {
    int n, m;
    int cntA[101] = {0};
    int cntB[101] = {0};

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cntA[x]++;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        cntB[x]++;
    }

    int riz1[100], riz2[100], peretyn[100], ob[200], symriz[200];
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;

    for (int x = 1; x <= 100; x++) {
        int a = cntA[x];
        int b = cntB[x];

        for (int k = 0; k < a - b; k++) {
            riz1[s1] = x;
            s1++;
        }
        for (int k = 0; k < b - a; k++) {
            riz2[s2] = x;
            s2++;
        }

        int mn = a;
        if (b < mn) mn = b;
        for (int k = 0; k < mn; k++) {
            peretyn[s3] = x;
            s3++;
        }

        int mx = a;
        if (b > mx) mx = b;
        for (int k = 0; k < mx; k++) {
            ob[s4] = x;
            s4++;
        }

        int d = a - b;
        if (d < 0) d = -d;
        for (int k = 0; k < d; k++) {
            symriz[s5] = x;
            s5++;
        }
    }

    printSet(riz1, s1);
    printSet(riz2, s2);
    printSet(peretyn, s3);
    printSet(ob, s4);
    printSet(symriz, s5);

    return 0;
}
