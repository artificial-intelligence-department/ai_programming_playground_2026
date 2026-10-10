#include <iostream>

int main()
{
    int n, i, cur_sequence, a;
    std::cin >> n;
    int arr[100];
    for (i = 0; i < n; i++) { std::cin >> arr[i]; }


    int list_max[100];

    int max_sequence = 1;
    for (i = n-1; i >= 0; i-=1) {
        cur_sequence = 1;
        for (a = i+1; a < n; a++) {
            if (arr[a] > arr[i]) {
                if (list_max[a]+1 > cur_sequence) {
                    cur_sequence = list_max[a] + 1;
                }
            }
        }
        if (cur_sequence > max_sequence) {
            max_sequence = cur_sequence;
        }
        list_max[i] = cur_sequence;
    }
    std::cout << max_sequence;
}