#include <iostream> 
using namespace std; 
 
int main() { 
    long long N; 
    cin >> N;
    
    long long *r =  new long long [N]; 
    long long res1; 
    long long res2; 
     
     
    for (int i = 0; i < N; i++) { 
        cin >> r[i]; 
         
    } 
    if (N < 2) { 
        cout << "0" << endl; 
        delete[] r; 
        return 0; 
    } 
     
    sort(r, r + N); 
    for (int i = 0; i < N - 1; i++) { 
        //cout << r[i] << ' '; 
         
    } 
     
    res1 = r[N-1] - r[1]; 
    res2 = r[N-2] - r[0]; 
    if (res1 >= res2) { 
        cout << res2 << endl; 
    } 
     
    if (res1 < res2) { 
        cout << res1 << endl; 
    } 
     
    delete[] r; 
    return 0; 
     
}
