#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char s[256];
    cout << "Рядок: ";
    fgets(s, sizeof(s), stdin);

    int len = strlen(s);
    if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
    }

    char all_words[100][50] {};
    int word_index = 0;

    char starts_with_letter[100][50] {};
    int alpha_index = 0;
    bool is_starts_letter[100] {};

    char* token = strtok(s, " \t\n.");
    while(token != NULL) {
        strcpy(all_words[word_index], token);

        if (isalpha(token[0])) {
            is_starts_letter[word_index] = true;
            strcpy(starts_with_letter[alpha_index], token);
            alpha_index++;
        }
        word_index++;
        token = strtok(NULL, " \t\n.");
    }

    for (int i = 0; i < alpha_index-1; i++) {
        for (int j = 0; j < alpha_index-1-i; j++) {
            if (strcmp(starts_with_letter[j], starts_with_letter[j+1]) > 0) {
                char temp[50];
                strcpy(temp, starts_with_letter[j]);
                strcpy(starts_with_letter[j], starts_with_letter[j+1]);
                strcpy(starts_with_letter[j+1], temp);
            }
        }
    }

    int curr_alpha_ind = 0;
    for (int i = 0; i < word_index; i++) {
        if (is_starts_letter[i]) {
            cout << starts_with_letter[curr_alpha_ind++] << " ";
        }
        else {
            cout << all_words[i] << " ";
        }
    }
}

// c 2e h 5r b a 8f 1w d