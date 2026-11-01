#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;

    int arr[100000];

    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int left = 0;
    int right = n - 1;

    while (true){

        if (left == right){
            cout << left + 1 << " " << right + 1 << endl;
            cout << "Collision";
            return 0;
        }

        if (left > right){
            cout << left + 1 << " " << right + 1 << endl;
            cout << "Miss";
            return 0;
        }

        if (right == left + 1){
            cout << left + 1 << " " << right + 1 << endl;
            cout << "Stopped";
            return 0;
        }

        int newLeft = left + arr[left];
        int newRight = right - arr[right];

        left = newLeft;
        right = newRight;
    }

    return 0;
}