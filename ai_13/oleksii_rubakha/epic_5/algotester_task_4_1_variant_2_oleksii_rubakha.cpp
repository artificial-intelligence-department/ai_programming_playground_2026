#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int N, K; std::cin >> N >> K;

    std::vector<int> a(N);
    for (int i = 0; i < N; i++) std::cin >> a[i];

    // Сортуємо та видаляємо дублікати
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int M = a.size();

    // Обертаємо вліво на K позицій
    rotate(a.begin(), a.begin() + K % M, a.end());

    std::cout << M << "\n";
    for (int i = 0; i < M; i++) std::cout << a[i] << " ";

    return 0;
}