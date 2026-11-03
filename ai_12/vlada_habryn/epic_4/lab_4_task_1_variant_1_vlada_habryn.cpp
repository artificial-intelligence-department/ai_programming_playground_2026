#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    srand(time(0));
    int n;
    int a[100];
    cout << "Enter the number of elements: ";
    cin >> n;
    if (n < 1 || n > 50) {
        cout << "Invalid number" << endl;
        return 1;
    }
for (int i = 0; i < n; i++) {
    a[i] = rand() % 100;
}
for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
}
int k;
cout << endl;
cout << "Enter the element number to delete: ";
cin >> k;
if (k<1 || k>n) {
    cout<<"Invalid number!"<<endl;
    return 1;
}
for (int i = k - 1; i < n - 1; i++) {
    a[i] = a[i + 1];
}
n --;

for (int i = 0; i<n; i++){
    cout<<a[i]<<" ";
}
for (int i = 0; i < n; i++) {
    if (a[i] %2 == 0){
        for (int j= n-1; j>i; j--){
            a[j+1] = a[j];
        }
        a[i+1] = 0;
        n++;
        i++;
    }
}
cout<<endl;
for (int i = 0; i<n; i++) {
    cout<<a[i]<< " ";
}

    return 0;
}
