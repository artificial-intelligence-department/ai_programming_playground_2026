#include <iostream>


using namespace std;
int main(){
int n = 0;
cin >> n;
int amount[n];
long long sum = 0;
for(int i = 0; i < n; i++){
    cin >> amount[i];
    sum += amount[i];


}
cout << sum - n << endl;
}
