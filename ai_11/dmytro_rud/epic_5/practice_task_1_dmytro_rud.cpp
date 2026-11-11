#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

bool isValidChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           (c == ' ');
}

bool isValidWord(const char *word) {
    if (strlen(word) == 0) return false;
    for (size_t i = 0; word[i] != '\0'; i++) {
        if (!isalnum(static_cast<unsigned char>(word[i]))) {
            return false;
        }
    }
    return true;
}

char **splitWords(const char *text, int &count) {
    count = 0;
    if (text == nullptr) return nullptr;

    char copy[256];
    strcpy(copy, text);

    size_t tlen = strlen(copy);
    if (tlen > 0 && copy[tlen - 1] == '.') {
        copy[tlen - 1] = '\0';
    }

    char temp[256];
    strcpy(temp, copy);
    char *token = strtok(temp, " ");
    while (token != nullptr) {
        count++;
        token = strtok(nullptr, " ");
    }

    if (count == 0) return nullptr;

    char **words = new char*[count];

    strcpy(temp, copy);
    token = strtok(temp, " ");
    int i = 0;
    while (token != nullptr) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        token = strtok(nullptr, " ");
        i++;
    }

    return words;
}

void freeWords(char **&words, int &count) {
    if (words == nullptr) return;
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

int menu() {
    while (true) {
        printf("\nВиберіть операцію:\n");
        printf("1 Показати текст і статистику\n");
        printf("2 Таблиця слів\n");
        printf("3 Замінити слово\n");
        printf("4 Порівняти два слова\n");
        printf("5 Інформація про символ\n");
        printf("6 Ввести нове речення\n");
        printf("0 Вийти\n");
        printf("Ваш вибір: ");

        int option;
        int status = scanf("%d", &option);

        if (status != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (option >= 0 && option <= 6) {
            return option;
        } else {
            printf("Помилка: пункту %d немає в меню.\n", option);
        }
    }
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    const char *ptr = text;
    while (*ptr != '\0') {
        if (isalpha(static_cast<unsigned char>(*ptr))) letters++;
        else if (isdigit(static_cast<unsigned char>(*ptr))) digits++;
        else if (*ptr == ' ') spaces++;
        ptr++;
    }
}

void showStatistics(const char *text, int word_count) {
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);

    size_t total_chars = strlen(text);

    double letters_pct = total_chars > 0 ? (letters * 100.0 / total_chars) : 0.0;
    double digits_pct  = total_chars > 0 ? (digits * 100.0 / total_chars) : 0.0;
    double spaces_pct  = total_chars > 0 ? (spaces * 100.0 / total_chars) : 0.0;

    printf("\nТекст:\t\"%s\"\n", text);
    printf("Символів: %5zu\n", total_chars);
    printf("Слів:     %5d\n", word_count);
    printf("Літер:    %5d (%5.1f%%)\n", letters, letters_pct);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, digits_pct);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, spaces_pct);
}

void showWordTable(char **words, int count) {
    if (count == 0 || words == nullptr) return;

    printf("\n+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    int min_len = (int)strlen(words[0]);
    int max_len = (int)strlen(words[0]);
    int min_idx = 0;
    int max_idx = 0;
    int total_chars_in_words = 0;

    for (int i = 0; i < count; i++) {
        int wlen = (int)strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], wlen);

        total_chars_in_words += wlen;

        if (wlen > max_len) {
            max_len = wlen;
            max_idx = i;
        }
        if (wlen < min_len) {
            min_len = wlen;
            min_idx = i;
        }
    }
    printf("+----+-----------------+-------+\n");

    double avg_len = (double)total_chars_in_words / count;
    printf("Найдовше слово: %s (%d)\n", words[max_idx], max_len);
    printf("Найкоротше слово: %s (%d)\n", words[min_idx], min_len);
    printf("Середня довжина: %.2f\n", avg_len);

    const char **sorted = new const char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                const char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою: ");
    for (int i = 0; i < count; i++) {
        printf("%s%s", sorted[i], (i == count - 1 ? "" : " "));
    }
    printf("\n");

    const char *most_freq_word = sorted[0];
    int max_freq = 0;
    int current_freq = 0;

    for (int i = 0; i < count; i++) {
        current_freq++;
        if (i == count - 1 || strcmp(sorted[i], sorted[i + 1]) != 0) {
            if (current_freq > max_freq) {
                max_freq = current_freq;
                most_freq_word = sorted[i];
            }
            current_freq = 0;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", most_freq_word, max_freq);

    delete[] sorted;
}

void changeWord(char *textChar, char **&words, int &count) {
    char from[32];
    char to[32];

    printf("Замінити слово: ");
    if (scanf("%31s", from) != 1) return;

    printf("На слово: ");
    if (scanf("%31s", to) != 1) return;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (!isValidWord(to)) {
        printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
        return;
    }

    std::string text = textChar;
    std::string reservText = textChar;
    std::string word = from;
    std::string new_word = to;

    int replaces = 0;
    size_t pos = 0;

    while ((pos = text.find(word, pos)) != std::string::npos) {
        bool left_ok = (pos == 0) || (text[pos - 1] == ' ');

        size_t right_pos = pos + word.length();
        bool right_ok = (right_pos == text.length()) || 
                        (text[right_pos] == ' ') || 
                        (text[right_pos] == '.');

        if (left_ok && right_ok) {
            text.replace(pos, word.length(), new_word);
            replaces++;
            pos += new_word.length();
        } else {
            pos += 1;
        }
    }

    if (text.length() > 255) {
        printf("Помилка: довжина тексту після заміни перевищує 255 символів. Зміни скасовано.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaces);
    printf("Було:  \"%s\"\n", reservText.c_str());
    printf("Стало: \"%s\"\n", text.c_str());
    printf("Нова довжина: %zu\n", text.length());

    if (replaces > 0) {
        strcpy(textChar, text.c_str());

        freeWords(words, count);
        words = splitWords(textChar, count);
    }
}

void compareWords() {
    char a[32];
    char b[32];

    printf("Перше слово: ");
    if (scanf("%31s", a) != 1) return;

    printf("Друге слово: ");
    if (scanf("%31s", b) != 1) return;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (!isValidWord(a) || !isValidWord(b)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    int cmp = strcmp(a, b);
    int norm_cmp = 0;
    const char *explanation = "слова однакові";

    if (cmp < 0) {
        norm_cmp = -1;
        explanation = "перше слово менше";
    } else if (cmp > 0) {
        norm_cmp = 1;
        explanation = "перше слово більше";
    }
    printf("strcmp: %d -> %s\n", norm_cmp, explanation);

    std::string str_a = a;
    std::string str_b = b;

    bool are_equal = (str_a == str_b);
    printf("Рівні (==): %s\n", are_equal ? "так" : "ні");

    bool equal_ci = false;
    if (str_a.length() == str_b.length()) {
        equal_ci = true;
        for (size_t i = 0; i < str_a.length(); i++) {
            if (tolower(static_cast<unsigned char>(str_a[i])) != 
                tolower(static_cast<unsigned char>(str_b[i]))) {
                equal_ci = false;
                break;
            }
        }
    }
    printf("Рівні без урахування регістру: %s\n", equal_ci ? "так" : "ні");

    printf("Довжини: %zu і %zu\n", str_a.length(), str_b.length());

    std::string concat = str_a + " & " + str_b;
    printf("Конкатенація: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

void information(const char *textCh) {
    printf("Введіть символ: ");
    char ch;
    if (scanf(" %c", &ch) != 1) return;

    int c_clean;
    while ((c_clean = getchar()) != '\n' && c_clean != EOF);

    int code = static_cast<unsigned char>(ch);
    std::string bin = "";

    for (int i = 7; i >= 0; i--) {
        bin += ((code >> i) & 1) ? "1" : "0";
    }

    printf("Символ: '%c'\n", ch);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", code, code, code, bin.c_str());

    if (isalpha(code)) {
        if (isupper(code)) {
            printf("Тип: велика літера\n");
            printf("Інший регістр: '%c'\n", tolower(code));
        } else {
            printf("Тип: мала літера\n");
            printf("Інший регістр: '%c'\n", toupper(code));
        }
    } else if (isdigit(code)) {
        printf("Тип: цифра\n");
    } else if (isspace(code)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: '%c'\n", static_cast<char>(code + 1));

    int count_in_text = 0;
    for (size_t i = 0; textCh[i] != '\0'; i++) {
        if (textCh[i] == ch) {
            count_in_text++;
        }
    }

    const char *first_pos = strchr(textCh, ch);
    if (first_pos == nullptr) {
        printf("Символ у тексті не зустрічається\n");
    } else {
        size_t pos = (first_pos - textCh) + 1;
        printf("Входжень у тексті: %d, перше на позиції %zu\n", count_in_text, pos);
    }
}

void inputNewSentence(char *textChar, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    std::string new_sentence = "";
    std::string word;
    int read_words = 0;

    while (std::cin >> word) {
        read_words++;
        if (!new_sentence.empty()) {
            new_sentence += " ";
        }
        new_sentence += word;

        if (!word.empty() && word[word.length() - 1] == '.') {
            break;
        }
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    bool valid = true;
    size_t slen = new_sentence.length();

    if (slen == 0 || slen > 255 || new_sentence[slen - 1] != '.') {
        valid = false;
    } else {
        for (size_t i = 0; i < slen - 1; i++) {
            if (!isValidChar(new_sentence[i])) {
                valid = false;
                break;
            }
        }
    }

    if (!valid) {
        printf("Помилка: речення некоректне. Поточний текст не змінюється.\n");
        return;
    }

    printf("Прочитано слів: %d\n", read_words);
    printf("Новий текст: \"%s\"\n", new_sentence.c_str());
    printf("Довжина: %zu\n", new_sentence.length());

    strcpy(textChar, new_sentence.c_str());

    freeWords(words, count);
    words = splitWords(textChar, count);
}

int main() {
    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (!fgets(text, sizeof(text), stdin)) {
        printf("Помилка: не вдалося зчитати текст!\n");
        return 1;
    }

    size_t len = strlen(text);
    while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r')) {
        text[--len] = '\0';
    }

    bool valid = (len > 0 && text[len - 1] == '.');
    if (valid) {
        for (size_t i = 0; i < len - 1; i++) {
            if (!isValidChar(text[i])) {
                valid = false;
                break;
            }
        }
    }

    bool has_word = false;
    if (valid) {
        for (size_t i = 0; i < len - 1; i++) {
            if (text[i] != ' ') {
                has_word = true;
                break;
            }
        }
        if (!has_word) valid = false;
    }

    if (!valid) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    bool exit_program = false;
    while (!exit_program) {
        int option = menu();
        switch (option) {
            case 0:
                exit_program = true;
                break;
            case 1:
                showStatistics(text, count);
                break;
            case 2:
                showWordTable(words, count);
                break;
            case 3:
                changeWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                information(text);
                break;
            case 6:
                inputNewSentence(text, words, count);
                break;
        }
    }

    freeWords(words, count);

    return 0;
}
