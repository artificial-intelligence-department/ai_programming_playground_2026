#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

main() {
    int answer1 = 0;
    int N;
    cin >> N;
    vector<int> vec1;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        vec1.push_back(x);
    }
    int M;
    cin >> M;
    vector<int> vec2;

    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        vec2.push_back(x);
    }
    int X = N < M ? N : M;
    for (int i = 0; i < X; i++) {
        if (X == N) {
            if (ranges::contains(vec2, vec1[i])) {
                answer1 += 1;
            }
        } else {
            if (ranges::contains(vec1, vec2[i])) {
                answer1 += 1;
            }
        }
    }

    int answer2 = (N + M) - answer1;
    cout << answer1 << "\n";
    cout << answer2 << "\n";
}   
