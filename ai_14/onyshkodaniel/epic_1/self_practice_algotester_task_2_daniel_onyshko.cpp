#include <iostream>

int main() {
    int n;
    std::cin >> n;

   
    long long a[100];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    
    int dp[100];
    int max_len = 1;

    
    for (int i = 0; i < n; i++) {
        dp[i] = 1; 

        
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }

      
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    std::cout << max_len << std::endl;

    return 0;
}