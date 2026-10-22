//Малюк

#include <iostream>

using namespace std;

int main()
{
    int n,d;
    cin >> n >> d;
    
    int A[n];
    for(int i = 0;i< n;i++){
        cin >> A[i];
    }

    int B[n];
    for(int i = 0;i< n;i++){
        cin >> B[i];
    }

    int count =0;
    for(int i = 0;i< n;i++){
        if(A[i] + d >= B[i] && A[i] - d <= B[i]){
            count++;
        }
        
    }

    if(count == n){
        cout << "YES";
    }
    else{
        cout << "NO";
    }


}