#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int* arr = new int[n];
    int sum = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum += arr[i];
    }
    int leftsum = 0;
    bool found = false;
    for(int i = 0; i < n; i++){
        leftsum += arr[i];
        if(leftsum == sum - leftsum){
            found = true;
            break;
        }
    }
    if(found) cout << "TAK";
    else cout << "NI";
}