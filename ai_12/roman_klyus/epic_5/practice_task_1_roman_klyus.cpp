#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

const char* const error_message = "слово має складатись лише з латинських літер та цифр (до 31 символу).";

// ======================================================================
// ВВІД
// ======================================================================

bool invalid_input(char* text, const int max_symbols) {
    if (fgets(text, max_symbols + 1, stdin) == nullptr) {
        text[0] = '\0';
        return true;
    }

    char* newline = strchr(text, '\n');
    if (newline != nullptr) {
        *newline = '\0';
        return false;
    }

    int ch = getchar();
    if (ch == '\n' || ch == EOF) return false;

    while (ch != '\n' && ch != EOF) ch = getchar();

    return true;
}

void clear_input() {
    int ch = getchar();
    while (ch != '\n' && ch != EOF) ch = getchar();
}

bool is_valid_word(const char* word) {
    if (word[0] == '\0') return false;

    for (const char* p = word; *p != '\0'; p++) {
        if (!isalnum((unsigned char)*p)) return false;
    }
    return true;
}

bool is_valid_text(const char* text) {
    int len = strlen(text);
    if (len == 0 || text[len - 1] != '.') {
        return false;
    }

    int words = 0;
    bool current_is_word = false;

    for (int i = 0; i < len - 1; i++) {
        char ch = text[i];
        if (isalnum((unsigned char)ch)) {
            if (!current_is_word) {
                words++;
                current_is_word = true;
            }
        }
        else if (ch == ' ') current_is_word = false;
        else return false;
    }

    return words > 0;
}

bool rest_of_line_is_empty() {
    bool empty = true;
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        if (!isspace((unsigned char)c)) empty = false;
    return empty;
}

bool read_menu_choice(int &choice) {
    int res = scanf("%d", &choice);
    if (res == EOF) {
        choice = 0;
        return true;
    }

    if (res != 1) {
        printf("Помилка: введіть номер пункту меню.\n");
        clear_input();
        return false;
    }

    if (!rest_of_line_is_empty()) {
        printf("Помилка: введіть лише одне число.\n");
        return false;
    }

    if (choice < 0 || choice > 6) {
        printf("Помилка: пункту %d немає в меню.\n", choice);
        return false;
    }
    return true;
}

bool read_word_with_prompt(const char* prompt, char* word, const char* error_message) {
    printf("%s: ", prompt);
    if (invalid_input(word, 31) || !is_valid_word(word)) {
        printf("Помилка: %s\n", error_message);
        return false;
    }
    return true;
}

bool read_symbol(char &ch) {
    char buffer[2];
    if (invalid_input(buffer, 1) || strlen(buffer) != 1) return false;
    ch = buffer[0];
    return true;
}

char **splitWords(const char* text, int &count) {
    char copy[256];

    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';

    count = 0;

    for (char *w = strtok(copy, " "); w != nullptr; w = strtok(nullptr, " ")) {
        count++;
    }

    char **words = new char*[count];

    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';
    int i {0};

    for (char *w = strtok(copy, " "); w != nullptr; w = strtok(nullptr, " ")) {
        words[i] = new char[strlen(w) + 1];
        strcpy(words[i], w);
        i++;
    }

    return words;
}

void freeWords(char **&words, int &count) {
    for (int i {0}; i < count; i++) {
        delete[] words[i];
    }

    delete[] words;
    words = nullptr;
    count = 0;
}

bool init_text(char *text, char **&words, int &count) {
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (invalid_input(text, 255) || !is_valid_text(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return false;
    }

    words = splitWords(text, count);
    return true;
}

// ======================================================================
// ПУНКТ 1
// ======================================================================

void countChars(const char* text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) letters++;
        else if (isdigit((unsigned char)*p)) digits++;
        else if (isspace((unsigned char)*p)) spaces++;
    }
}

void point_1(const char* text, int words_count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    size_t total {strlen(text)};

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6zu\n", total);
    printf("Слів:%10d\n", words_count);
    printf("Літер:%9d (%5.1f%%)\n", letters, 100.0 * letters / total);
    printf("Цифр:%10d (%5.1f%%)\n", digits, 100.0 * digits / total);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, 100.0 * spaces / total);
}

// ======================================================================
// ПУНКТ 2
// ======================================================================

void show_words_table(char** words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i {0}; i < count; i++) {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");
}

void show_words_len(char** words, int count) {
    int longest = 0, shortest = 0;
    int max_len = strlen(words[0]);
    int min_len = max_len;
    int sum = 0;

    for (int i {0}; i < count; i++) {
        int len = strlen(words[i]);
        if (len > max_len) { max_len = len; longest = i; }
        if (len < min_len) { min_len = len; shortest = i; }
        sum += len;
    }

    printf("Найдовше слово: %s (%d)\n", words[longest], max_len);
    printf("Найкоротше слово: %s (%d)\n", words[shortest], min_len);
    printf("Середня довжина: %.2f\n", 1.0 * sum / count);
}

void sort_words(char** words, int count) {
    for (int i {0}; i < count - 1; i++) {
        for (int j {0}; j < count - 1 - i; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char* temp = words[j + 1];
                words[j + 1] = words[j];
                words[j] = temp;
            }
        }
    }
}

void show_sorted_and_most_frequent(char** words, int count) {
    char** sorted = new char*[count];
    for (int i {0}; i < count; i++) sorted[i] = words[i];

    sort_words(sorted, count);

    printf("За абеткою: ");
    for (int i {0}; i < count; i++) printf("%s ", sorted[i]);

    int streak = 1, best_streak = 1, best_streak_idx = 0;
    for (int i {0}; i < count - 1; i++) {
        if (strcmp(sorted[i], sorted[i + 1]) == 0) streak++;
        else streak = 1;
        if (streak > best_streak) {
            best_streak = streak;
            best_streak_idx = i;
        }
    }

    printf("\nНайчастіше слово: %s (%d)\n", sorted[best_streak_idx], best_streak);
    delete[] sorted;
}

void point_2(char** words, int count) {
    show_words_table(words, count);
    show_words_len(words, count);
    show_sorted_and_most_frequent(words, count);
}

// ======================================================================
// ПУНКТ 3
// ======================================================================

string replace_words(const string &text, const string &from, const string &to, int &replaced_count) {
    string res = text;
    replaced_count = 0;
    size_t idx = res.find(from);
    while (idx != string::npos) {
        bool left_ok = idx == 0 || isspace(res[idx - 1]);
        size_t end_idx = idx + from.length();
        bool right_ok = !isalnum(res[end_idx]);
        if (left_ok && right_ok) {
            res.replace(idx, from.length(), to);
            replaced_count++;
            idx = res.find(from, idx + to.length());
        } else idx = res.find(from, idx + from.length());
    }
    return res;
}

void apply_new_text(char* text, char** &words, int &count, const string &new_text) {
    strcpy(text, new_text.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}

void show_replaced_res(const string &before, const string &after, int replaced_count) {
    printf("Замін виконано: %d\n", replaced_count);
    printf("Було:  \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", after.c_str());
    printf("Нова довжина: %d\n", (int)after.length());
}

void point_3(char *text, char **&words, int &count) {
    char from[32], to[32];
    if (!read_word_with_prompt("Замінити слово", from, error_message)) return;
    if (!read_word_with_prompt("На слово", to, error_message)) return;

    int replaced_count = 0;
    string before = text;
    string after = replace_words(before, from, to, replaced_count);

    if (after.length() > 255) {
        printf("Помилка: новий текст занадто довгий (має бути менше 256 символів).\n");
        return;
    }

    apply_new_text(text, words, count, after);
    show_replaced_res(before, after, replaced_count);

}

// ======================================================================
// ПУНКТ 4
// ======================================================================

bool equal_words_no_register(const string &a, const string &b) {
    if (a.length() != b.length()) return false;

    for (size_t i {0}; i < a.length(); i++) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return false;
    }
    return true;
}

void point_4() {
    char a[32], b[32];

    if (!read_word_with_prompt("Перше слово", a, error_message)) return;
    if (!read_word_with_prompt("Друге слово", b, error_message)) return;

    int cmp = strcmp(a, b);
    if (cmp > 0) cmp = 1;
    else if (cmp < 0) cmp = -1;
    
    string stra = a, strb = b;

    printf("strcmp: %d -> %s\n", cmp, (cmp == 0) ? "слова рівні" : (cmp < 0) ? "перше слово менше" : "друге слово менше");
    printf("Рівні (==): %s\n", (stra == strb) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equal_words_no_register(stra, strb) ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", stra.length(), strb.length());

    string joined = stra + " & " + strb;

    printf("Конкатенація: \"%s\" (%zu)\n", joined.c_str(), joined.length());
}

// ======================================================================
// ПУНКТ 5
// ======================================================================

string to_binary(const char &c) {
    unsigned ch = (unsigned char)c;
    string res = "";

    while (ch > 0) {
        char bit = (ch % 2) + '0';
        res = bit + res;
        ch /= 2;
    }

    while (res.length() < 8) res = '0' + res;
    return res;
}

void point_5(const char *text) {
    char c;
    printf("Введіть символ: ");
    if (!read_symbol(c)) {
        printf("Помилка: потрібно ввести один символ.\n");
        return;
    }

    int code = (unsigned char)c;
    string bin = to_binary(c);

    printf("Символ: \'%c\'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", code, code, code, bin.c_str());
    string type = "";
    if (isalpha(code)) {
        if (isupper(code)) type = "велика літера";
        if (islower(code)) type = "мала літера";
    }
    else if (isdigit(code)) type = "цифра";
    else if (isspace(code)) type = "пробільний символ";
    else type = "інший символ";

    printf("Тип: %s\n", type.c_str());
    if (isalpha(code)) printf("Інший регістр: \'%c\'\n", isupper(code) ? tolower(c) : toupper(c));
    printf("Наступний символ: \'%c\'\n", (char)(code + 1));

    int found_count = 0, first_in = 0, i = 1;
    for (const char *p = text; *p != '\0'; p++, i++) {
        if (*p == c) {
            found_count++;
            if (found_count == 1) first_in = i;
        }
    }

    if (found_count > 0) printf("Входжень у тексті: %d, перше на позиції %d\n", found_count, first_in);
    else printf("Входжень не виявлено\n");
}

// ======================================================================
// ПУНКТ 6
// ======================================================================

void point_6(char *text, char **&words, int &count) {
    printf("Введіть нове речення по словах (завершіть слово крапкою '.'):\n");

    string candidate;
    string word;

    while (cin >> word) {
        if (!candidate.empty()) candidate += ' ';

        candidate += word;
        
        if (word.back() == '.') break;
    }

    clear_input();

    if (candidate.length() > 255 || !is_valid_text(candidate.c_str())) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    apply_new_text(text, words, count, candidate);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

// ======================================================================
// МЕНЮ
// ======================================================================

void print_menu() {
    printf("==============Меню==============\n");
    printf("1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
    printf("================================\n");
}

void run_menu(char* text, char **&words, int &count) {
    int choice = -1;
    do {
        print_menu();
        printf("Ваш вибір: ");
        if (!read_menu_choice(choice)) {
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: point_1(text, count);         break;
            case 2: point_2(words, count);        break;
            case 3: point_3(text, words, count);  break;
            case 4: point_4();                    break;
            case 5: point_5(text);                break;
            case 6: point_6(text, words, count);  break;
            case 0: printf("Роботу програми завершено.\n"); break;
        }
    } while (choice != 0);
}

int main() {
    char text[256];
    char** words {nullptr};
    int count {0};

    if (!init_text(text, words, count)) return 1;

    run_menu(text, words, count);
    freeWords(words, count);
}