#include <iostream>

int main(){
    int a, b;
    std::cin >> a >> b;
    
    int min_val = std:: min (a, b);
    int max_val = std:: max (a, b);

    if (max_val - min_val <= 1) {
        std::cout << -1 << std:: endl;
    } else {
        std::cout << min_val+1 << std:: endl;
    }
    return 0;
    
}
