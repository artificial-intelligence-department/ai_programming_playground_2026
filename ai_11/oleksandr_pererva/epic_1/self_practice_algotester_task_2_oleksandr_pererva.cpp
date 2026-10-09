/*
Марічка і печиво
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long ai=0;
    for (int i=0; i<n; i++) {
        long long a;
        cin>>a;
        if (a>0) {
            ai+=(a-1);
        }
    }

    cout<<ai<<endl;
    return 0;
}