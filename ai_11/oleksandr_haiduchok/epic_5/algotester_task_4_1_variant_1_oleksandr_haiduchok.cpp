#include <iostream>
#include <algorithm>
using namespace std;
void riznNM(int arr1[], int arr2[], int n, int m){
    int riz[209];
    int rah = 0;
    int i = 0;
    int g = 0;
    while(i < n && g < m){
            if(arr1[i] < arr2[g]){
                riz[rah] = arr1[i];
                i++;
                rah++;
            }
            else if(arr1[i] == arr2[g]){
                i++;
                g++;
            }
        else{
            g++;
    }
}
while(i < n){
    riz[rah] = arr1[i];
    rah++;
    i++;
}
    cout << rah << "\n";
    for(int b = 0; b < rah; b++){
        if(b > 0) cout << " ";
        cout << riz[b];
    }
    cout << "\n\n";
}
void riznMN(int arr1[], int arr2[], int n, int m){
    riznNM(arr2, arr1, m, n);
}

void peretin(int arr1[], int arr2[], int n, int m){
    int per[209];
    int rah = 0;
    int i = 0;
    int g = 0;
    while(i < n && g < m){
            if(arr1[i] < arr2[g]){
                i++;
            }
            else if(arr1[i] == arr2[g]){
                per[rah] = arr1[i];
                i++;
                g++;
                rah++;
            }
        else{
            g++;
    }
}
    cout << rah << "\n";
    for(int b = 0; b < rah; b++){
        if(b > 0) cout << " ";
        cout << per[b];
    }
    cout << "\n\n";
}
void obyednanya(int arr1[], int arr2[], int n, int m){
    int ob[209];
    int i = 0;
    int g = 0;
    int size = 0;
    while(i < n && g < m){
        if(arr1[i] < arr2[g]){
            ob[size] = arr1[i];
            size++;
            i++;
        }
        else if(arr1[i] > arr2[g]){
            ob[size] = arr2[g];
            size++;
            g++;
        }
        else {
            ob[size] = arr1[i];
            size++;
            i++;
            g++;
        }
    }
    while(i < n) {
        ob[size] = arr1[i];
        size++;
        i++;
    }
    while(g < m) {
        ob[size] = arr2[g];
        size++;
        g++;
    }
    cout << size << "\n";
     for(int b = 0; b < size; b++){
        if(b > 0) cout << " ";
        cout << ob[b];
    }
    cout << "\n\n";
}
void simriz(int arr1[], int arr2[], int n, int m){
    int sim[209];
    int rah = 0;
    int i = 0;
    int g = 0;
    while(i < n && g < m){
            if(arr1[i] < arr2[g]){
                sim[rah] = arr1[i];
                i++;
                rah++;
            }
            else if(arr1[i] == arr2[g]){
                i++;
                g++;
            }
        else{
            sim[rah] = arr2[g];
                g++;
                rah++;
    }
}
while(i < n){
    sim[rah] = arr1[i];
    rah++;
    i++;
}
while(g < m){
    sim[rah] = arr2[g];
    rah++;
    g++;
}
    cout << rah << "\n";
     for(int b = 0; b < rah; b++){
        if(b > 0) cout << " ";
        cout << sim[b];
    }
    cout << "\n";
}

int main(){
    int N = 0;
    int M = 0;
    cin >> N;
    int mnozh1[107];
    for(int i = 0; i < N; i++){
        cin >> mnozh1[i];
    }
    sort(mnozh1, mnozh1 + N);
    cin >> M;
    int mnozh2[107];
    for(int k = 0; k < M; k++){
        cin >> mnozh2[k];
    }
    sort(mnozh2, mnozh2 + M);
    riznNM(mnozh1,mnozh2, N, M);
    riznMN(mnozh1,mnozh2, N, M);
    peretin(mnozh1,mnozh2, N, M);
    obyednanya(mnozh1,mnozh2, N, M);
    simriz(mnozh1,mnozh2, N, M);
    return 0;
}

