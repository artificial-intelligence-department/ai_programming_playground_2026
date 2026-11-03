#include <iostream>
#include <random>
using namespace std;

int main() {
    int n;
    cin >> n;
    int *a = new int[n];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(-100000000, 100000000);
    for(int i=0;i<n;i++){
        a[i] = distrib(gen);
    }
    for(int i=0;i<n;i++){
        cout << a[i] << " ";
    }
    cout << "\n";
    int k;
    cin >> k;
    for(int i=0;i<n;i++){
        if(a[i] == k){
            int l = i;
            for(int j=0;j<(n-i)-1;j++){
                a[l] = a[l+1];
                l++;
            }
            n--;
            i--;
        }
    }
    int *bigger = new int[n*2];
    for(int i=0;i<n*2;i++){
        bigger[i] = 0;
    }
    for(int i=0;i<n;i++){
        bigger[i] = a[i];
    }
    delete[] a;
    a = bigger;
    for(int i=0;i<n;i++){
        if((a[i] % 2) == 0){
            for(int j=n-1;j>=i;j--){
                a[j+1] = a[j];
            }
            a[i] = 0;
            n++;
            i++;
        }
    }
    for(int i=0;i<n;i++){
        cout << a[i] << " ";
    }
    delete[] a;
    return 0;
}