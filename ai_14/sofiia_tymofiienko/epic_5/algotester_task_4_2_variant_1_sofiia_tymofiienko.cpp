//Власна реалізація 
#include <iostream>
using namespace std;
void print(const int* r, int k){
    cout << k << "\n";
    for (int i = 0; i < k; i++){
        if (i) cout << " ";
        cout << r[i];
    }
    cout << "\n";
}
void sortArray(int* a, int n){
    for (int i = 0; i < n - 1; i++){
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++){
            if (a[j] > a[j + 1]){
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
int read(int*& a){
    int n;
    cin >> n;
    a = new int[n + 1];
    for (int i = 0; i < n; i++) cin >> a[i];
    sortArray(a, n);
    return n;
}
int difference(const int* a, int na, const int* b, int nb, int* r){
    int k = 0, i = 0, j = 0;
    while (i < na){
        if (j == nb || a[i] < b[j]) r[k++] = a[i++];
        else if (a[i] == b[j]) { i++; j++; }
        else j++;
    }
    return k;
}

int intersection(const int* a, int na, const int* b, int nb, int* r){
    int k = 0, i = 0, j = 0;
    while (i < na && j < nb){
        if (a[i] < b[j]) i++;
        else if (b[j] < a[i]) j++;
        else { r[k++] = a[i]; i++; j++; }
    }
    return k;
}
int unite(const int* a, int na, const int* b, int nb, int* r){
    int k = 0, i = 0, j = 0;
    while (i < na || j < nb){
        if (j == nb || (i < na && a[i] < b[j])) r[k++] = a[i++];
        else if (i == na || b[j] < a[i]) r[k++] = b[j++];
        else { r[k++] = a[i]; i++; j++; }
    }
    return k;
}
int symDifference(const int* a, int na, const int* b, int nb, int* r){
    int k = 0, i = 0, j = 0;
    while (i < na || j < nb){
        if (j == nb || (i < na && a[i] < b[j])) r[k++] = a[i++];
        else if (i == na || b[j] < a[i]) r[k++] = b[j++];
        else { i++; j++; }
    }
    return k;
}
int main(){
    int *a, *b;
    int na = read(a);
    int nb = read(b);
    int* r = new int[na + nb + 1];
    int k;
    k = difference(a, na, b, nb, r);
    print(r, k);
    k = difference(b, nb, a, na, r);
    print(r, k);
    k = intersection(a, na, b, nb, r);
    print(r, k);
    k = unite(a, na, b, nb, r);
    print(r, k);
    k = symDifference(a, na, b, nb, r);
    print(r, k);
    delete[] a;
    delete[] b;
    delete[] r;
    return 0;
}
