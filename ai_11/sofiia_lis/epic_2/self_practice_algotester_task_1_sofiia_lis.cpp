/* 
Епік 2. self_practice_algotester_task_1_sofiia_lis
"Marichka and cookies"
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long eaten_cookies = 0;

    for (int i = 0; i < n; i++) {
        long long cookies_in_pack;
        cin >> cookies_in_pack;
        if (cookies_in_pack > 1) {
            eaten_cookies += cookies_in_pack - 1;
        }
    }

    cout << eaten_cookies;
    
    return 0;
}