#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int *a = new int[n];
    int total = 0;
    int left = 0;

    for(int* p = a; p < n + a; p++){
        cin >> *p;
        total += *p;
    }
    for(int* p = a; p < n + a - 1; p++){
        left += *p;
        int right = 0;
        right = total - left;
        if(right == left){
            cout << "TAK" << endl;
            delete [] a;
            return 0;
        }
    }

    cout << "NI" << endl;
    delete [] a;

    return 0;
}