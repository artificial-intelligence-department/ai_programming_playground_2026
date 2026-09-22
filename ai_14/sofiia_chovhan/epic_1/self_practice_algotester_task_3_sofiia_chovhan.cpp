#include <iostream> 
int main() {
    int a, b, c;
    std :: cin >> a >> b >> c;
    if(a >= 1 && b >= 1 && c >=1 && a + b > c){
        std :: cout << "YES";
    }
    else {
        std :: cout << "NO";
    }
    return 0;
}