#include <iostream>
#include <cmath>

using namespace std;
int main(){
    double quantity, radius;
    cin >> quantity >> radius;
    double result = sqrt((radius * radius) / quantity);
    cout << result;
    return 0;
}