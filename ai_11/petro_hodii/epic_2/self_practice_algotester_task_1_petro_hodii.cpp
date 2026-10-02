#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool isEqual = true;
    int n;
    cin >> n;

    vector<int> placing_0(n);

    for(int i=0; i<n; i++){
        cin >> placing_0[i];
    }

    vector<int> placing(n);

    for(int i=0; i<n; i++){
        cin >> placing[i];
    }

    
    for(int i=0; i<n; i++){
        if(placing_0[i]!=placing[n-1-i]){
            isEqual= false;
            break;
        }
    }

    if(isEqual){
        cout << "Yes";
    }
    else{
        cout << "No" << endl;
        for(int i=0; i<n; i++){
            cout << placing_0[n-1-i] << " ";
        }
    }

    return 0;
}
