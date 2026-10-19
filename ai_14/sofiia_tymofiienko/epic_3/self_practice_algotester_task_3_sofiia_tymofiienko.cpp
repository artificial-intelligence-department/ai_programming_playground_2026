#include <iostream>
using namespace std;
    int main(){
    int n;
    cin>>n;

    int MAX;
    cin>> MAX;
        for (int i=1; i<n; i++){
            int x;
            cin>>x;
            if (x>MAX){
                MAX=x;
            }
        }
        cout<< MAX<<endl;
        return 0;
    }
    