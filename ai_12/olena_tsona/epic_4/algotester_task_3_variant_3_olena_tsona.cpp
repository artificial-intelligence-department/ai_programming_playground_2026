#include <iostream> 
using namespace std; 
 
int main() { 
    
    string S;
    cin >> S;
    
    int count = 1;
    
    long long n;
    n = S.size();
    
    
    for (int i = 1; i <= n; i++) {
        if (i < n && S[i] == S[i - 1]) {
            count++;
            
        }
        
        else {
            cout << S[i - 1];
            if (count > 1) {
                cout << count;
            }
            count = 1;
        }
    }
    
    
    return 0; 
     
}
