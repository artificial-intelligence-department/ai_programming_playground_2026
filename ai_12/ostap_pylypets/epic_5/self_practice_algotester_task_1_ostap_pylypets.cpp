//ДНК репяховірусу 1806

#include <cstdio>

char* readWord(int& length) {
    int capacity = 64;
    char* word = new char[capacity];
    length = 0;

    char c;
    if (scanf(" %c", &c) != 1) {
        return word;
    }

    do {
        if (c < 'a' || c > 'z') {
            break;
        }
        //регулюємо виділення пім'яті
        if (length == capacity) {
            capacity *= 2;
            char* bigger = new char[capacity];

            for (int i = 0; i < length; i++) {
                bigger[i] = word[i];
            }

            delete[] word;
            word = bigger;
        }
        //записуємо c у word
        word[length++] = c;
    } while (scanf("%c", &c) == 1);

    return word;
}

int main() {
    int n, m;
    char* s = readWord(n);
    char* t = readWord(m);

    long long answer = 0;

    if (m > 0 && m <= n) {
        //кількість можливих початкі рядка
        int width = n - m + 1;
        int frequency[26] = {};
        //зберігає сікльки окжна літера трапляється
        for (int j = 0; j < width; j++) {
            frequency[s[j] - 'a']++;
        }

        for (int i = 0; i < m; i++) {
            answer += 1LL * (i + 1) * frequency[t[i] - 'a'];
            //перевіряє чи є ще наступна літера
            if (i + 1 < m){
                //кількість збігів для поточної літери шаблону
                frequency[s[i] - 'a']--;
                frequency[s[i + width] - 'a']++;
            }
        }
    }

    printf("%lld\n", answer);

    delete[] s;
    delete[] t;
    return 0;
}