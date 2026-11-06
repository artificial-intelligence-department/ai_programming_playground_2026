//Найдовший зростаючий підмасив
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    int count = 1;
    int maxCount = 1;
    for(int i = 0;i < n - 1;i++){
        if(a[i] < a[i + 1]){
            count++;
        }
        else {
            count = 1;
        }

        if (count > maxCount) {
            maxCount = count;
        }
    }
    cout << maxCount;
    delete[] a;
}
