#include <iostream>
using namespace std;

int main(){  
    int n;
    cin >> n;
    int* even = new int[n];
    int* odd = new int[n];
    int evencount = 0;
    int oddcount = 0;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        if(x % 2 == 0){
            even[evencount] = x;
            evencount++;
        }
        else{
            odd[oddcount] = x;
            oddcount++;
        }
    }
    if(evencount > oddcount + 1 || oddcount > evencount + 1){
        cout << "-1" << endl;
    }
    else{
        int e = 0;
        int o = 0;
        if(evencount >= oddcount){
            for(int i = 0; i < n; i++){
                if(i % 2 == 0){
                    cout << even[e] << " ";
                    e++;
                }
                else{
                    cout << odd[o] << " ";
                    o++;
                }
            }
        }
        else{
            for(int i = 0; i < n; i++){
                if(i % 2 == 0){
                    cout << odd[o] << " ";
                    o++;
                }
                else{
                    cout << even[e] << " ";
                    e++;
                }
            }
        }
    }
    delete[] even;
    delete[] odd;
    return 0;
}