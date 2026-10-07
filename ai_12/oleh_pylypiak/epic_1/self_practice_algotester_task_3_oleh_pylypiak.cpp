#include <iostream>
using namespace std;
int main(){
    int N;
    cin >> N;
    int M;
    cin >> M;
    int k=N*M;
    if (k%2==0){
        cout << "Dragon";
    }
    if (k%2==1){
        cout << "Imp";
    }
    return 0;
}