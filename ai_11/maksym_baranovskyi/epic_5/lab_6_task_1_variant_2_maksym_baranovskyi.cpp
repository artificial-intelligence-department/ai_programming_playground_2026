#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    char text[256];
    char result[2048] = "";
    const char *symbols = " \t.,!?;:-()\"'0123456789"; 
    const char *vowels = "aeiouAEIOU";
    int k = 0;
    
    cout << "Введіть текст (крапка для завершення введення): " << endl;

    while (fgets(text, sizeof(text), stdin) != nullptr) {
        text[strcspn(text, "\r\n")] = '\0';
        bool stopfgets = (strlen(text) > 0 && text[strlen(text) - 1] == '.'); 

        char *word = strtok(text, symbols);
        while (word != nullptr) {
            bool hasVowel = false;
            for (int j = 0; word[j] != '\0'; j++) {
                if (strchr(vowels, word[j]) != nullptr) {
                    hasVowel = true;
                    break;
                }
            }

            if (!hasVowel) {                 
                int len = strlen(word);
                if (k + len + 1 < (int)sizeof(result)) {   
                    for (int j = 0; j < len; j++) {
                        result[k++] = word[j];
                    }
                    result[k++] = ' ';
                }
            }
            word = strtok(nullptr, symbols);
        }

        if (stopfgets) {
            break;
        }
    }
    cout << "Слова без голосних літер: " << result; 

    return 0;
}