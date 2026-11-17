#include <iostream>

using namespace std;

int main() {
    int cntA[101] = {0};
    int cntB[101] = {0};

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cntA[a]++;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        cntB[a]++;
    }

    int* diffAB = new int[n + m];
    int* diffBA = new int[n + m];
    int* inter  = new int[n + m];
    int* uni    = new int[n + m];
    int* symm   = new int[n + m];

    int sz_diffAB = 0;
    int sz_diffBA = 0;
    int sz_inter  = 0;
    int sz_uni    = 0;
    int sz_symm   = 0;

    for (int v = 1; v <= 100; v++) {
        int ca = cntA[v], cb = cntB[v];

        int k_diffAB = (ca > cb) ? (ca - cb) : 0;
        for (int k = 0; k < k_diffAB; k++) diffAB[sz_diffAB++] = v;

        int k_diffBA = (cb > ca) ? (cb - ca) : 0;
        for (int k = 0; k < k_diffBA; k++) diffBA[sz_diffBA++] = v;

        int k_inter = (ca < cb) ? ca : cb;
        for (int k = 0; k < k_inter; k++) inter[sz_inter++] = v;

        int k_uni = (ca > cb) ? ca : cb;
        for (int k = 0; k < k_uni; k++) uni[sz_uni++] = v;

        int k_symm = (ca > cb) ? (ca - cb) : (cb - ca);
        for (int k = 0; k < k_symm; k++) symm[sz_symm++] = v;
    }

    int* arrays[5] = {diffAB, diffBA, inter, uni, symm};
    int sizes[5]   = {sz_diffAB, sz_diffBA, sz_inter, sz_uni, sz_symm};

    for (int t = 0; t < 5; t++) {
        cout << sizes[t] << "\n";
        for (int i = 0; i < sizes[t]; i++) {
            cout << arrays[t][i] << " ";
        }
        cout << "\n\n";
    }

    delete[] diffAB;
    delete[] diffBA;
    delete[] inter;
    delete[] uni;
    delete[] symm;

    return 0;
}