#include <iostream>
#include <algorithm>
using namespace std;

void riznNM(int arr1[], int arr2[], int n, int m){
    int riz[209];
    int rah = set_difference(arr1, arr1 + n, arr2, arr2 + m, riz) - riz;
    cout << rah << "\n";
    for(int b = 0; b < rah; b++){
        if(b > 0) cout << " ";
        cout << riz[b];
    }
    cout << "\n\n";
}

void riznMN(int arr1[], int arr2[], int n, int m){
    int riz[209];
    int rah = set_difference(arr2, arr2 + m, arr1, arr1 + n, riz) - riz;
    cout << rah << "\n";
    for(int b = 0; b < rah; b++){
        if(b > 0) cout << " ";
        cout << riz[b];
    }
    cout << "\n\n";
}

void peretin(int arr1[], int arr2[], int n, int m){
    int per[209];
    int rah = set_intersection(arr1, arr1 + n, arr2, arr2 + m, per) - per;
    cout << rah << "\n";
    for(int b = 0; b < rah; b++){
        if(b > 0) cout << " ";
        cout << per[b];
    }
    cout << "\n\n";
}

void obyednanya(int arr1[], int arr2[], int n, int m){
    int ob[209];
    int size = set_union(arr1, arr1 + n, arr2, arr2 + m, ob) - ob;
    cout << size << "\n";
    for(int b = 0; b < size; b++){
        if(b > 0) cout << " ";
        cout << ob[b];
    }
    cout << "\n\n";
}

void simriz(int arr1[], int arr2[], int n, int m){
    int sim[209];
    int sum = set_symmetric_difference(arr1, arr1 + n, arr2, arr2 + m, sim) - sim;
    cout << sum << "\n";
    for(int x = 0; x < sum; x++){
        if(x > 0) cout << " ";
        cout << sim[x];
    }
    cout << "\n";
}

int main(){
    int N = 0;
    int M = 0;
    int mnozh1[106];
    int mnozh2[106];

    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> mnozh1[i];
    }
    sort(mnozh1, mnozh1 + N);

    cin >> M;
    for(int k = 0; k < M; k++){
        cin >> mnozh2[k];
    }
    sort(mnozh2, mnozh2 + M);

    riznNM(mnozh1, mnozh2, N, M);
    riznMN(mnozh1, mnozh2, N, M);
    peretin(mnozh1, mnozh2, N, M);
    obyednanya(mnozh1, mnozh2, N, M);
    simriz(mnozh1, mnozh2, N, M);
    return 0;
}

