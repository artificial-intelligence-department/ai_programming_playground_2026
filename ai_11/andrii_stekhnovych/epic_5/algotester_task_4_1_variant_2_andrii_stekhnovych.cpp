//Algotester Lab 4v2 (with STL)

#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n, k;
    int unique=0;
    cin >> n >> k;
    int* array = new int[n];
    for (int i=0; i<n; i++) {
        cin >> array[i];
    }
    std::sort(array, array+n);
    int* end = std::unique(array, array+n);
    int new_size=end-array;
    int* set = new int[new_size];
    for (int i =0; i<new_size; i++) {
        set[i]=array[i];
    }
    delete[] array;
    array=nullptr;
    k%=new_size;
    std::rotate(set, set+k, set+new_size);
    cout << new_size << endl;
    for (int i =0; i<new_size; i++) {
        cout << set[i] << " ";
    }
    delete[] set;
    set=nullptr;


}