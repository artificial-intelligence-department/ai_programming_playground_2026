#include <iostream>
using namespace std;
int main(){
        long long a,b;
        long long smaller, bigger;
        cin >> a;
        cin >> b;
        if (a > b){
                bigger = a;
                smaller = b;
        }
        else {
                smaller = a;
                bigger = b;
        }
        if (bigger - smaller > 1){
                cout << smaller + 1 << endl;
        }
        else {
                cout << -1 << endl;
        }

        return 0;
}