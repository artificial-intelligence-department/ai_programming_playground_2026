#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    long long n,k;
    cin >> n >> k;

    long long *a = new long long[n]();
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    long long *new_array = unique(a,a+n);
    long long counter = new_array-a;
    long long index = k;
    while(index >= counter){
        index -= counter;
    }
    rotate(a,a+index,new_array);
    cout << counter << endl;
    for (int i = 0; i < counter; i++)
    {
        cout << a[i] << " ";
    }
    delete[] a;
}
