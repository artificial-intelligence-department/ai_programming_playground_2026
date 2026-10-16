#include <iostream>
#include <climits>
using namespace std;
int main(){
    int n;
    cin >> n;
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i<n; i++) {
        int current;
        cin >> current;
        if (current>max) {
            max=current;
        }
        if (current<min) {
            min=current;
        }
        
    }
    cout << max-min << endl;
    
}
