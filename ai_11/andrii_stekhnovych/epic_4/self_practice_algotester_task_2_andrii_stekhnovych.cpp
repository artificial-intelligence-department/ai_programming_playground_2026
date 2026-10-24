#include <iostream>
#include <cmath>
#include <climits>
#include <iomanip>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    int *array = new int[m];
    int max=INT_MIN;
    for (int i=0; i<m; i++) {
        cin >> array[i];
        if(array[i]>max) {
            max=array[i];
        }
    }
    double left=0;
    double right=max;
    double mid;
    while (right-left>pow(10, -7)) {
        mid=left+(right-left)/2;
        int count = 0;
        for(int i =0; i<m; i++) {
            count+=floor(array[i]/mid);
        }
        if(count<n) {
            right=mid;
        } else {
            left=mid;
        }
    }
    cout <<fixed<<setprecision(7)<< mid;
    delete[] array;
    array=nullptr;
}