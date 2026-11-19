//Відновіть рядок 0703

#include <iostream>
#include <string>

int main(){
    int n;
    if (!(std::cin >> n) || n < 0) {
        return 0;
    }

    char* s = new char[n + 1];
    int* str = new int[n];
    int* rank = new int[n + 2]{};

    bool possible = true;

    for(int i = 0; i < n; i++){
        //якщо stri != 0  або вихаодить за межі то...
        if (!(std::cin >> str[i]) || str[i] < 1 || str[i] > n ||
            rank[str[i]] != 0) {
            possible = false;
            break;
        }

        rank[str[i]] = i + 1;
    }

    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int letter = 0;

    if (possible) {
        for(int i = 0; i < n; i++){
            //перевіряємо суфікси на збіг, порівнюємо та відкидаємо хвости
            if (i > 0 && rank[str[i - 1] + 1] > rank[str[i] + 1]) {
                letter++;
            }

            if (letter == 26) {
                possible = false;
                break;
            }
            //записуємо вибрану літеру на позицію
            s[str[i] - 1] = alphabet[letter];
        }
    }

    s[n] = '\0';
    //вивід
    if (possible) {
        std::cout << s << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    delete[] rank;
    delete[] str;
    delete[] s;
    return 0;
}