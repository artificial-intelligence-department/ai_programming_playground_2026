// Algotester, задача "Zenyk and happiness"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/81483
// Ткач Артем, ШІ-13
//
// Умова: у таблиці n x m Зеник іде з (1,1) в (n,m), роблячи кроки вправо або вниз, і збирає
// значення клітинок. Марічка обирає стовпець, Зеник обирає в ньому клітинку, і її значення
// стає нулем. Зеник хоче зібрати якомога більше, Марічка - якомога менше.
//
// Ідея: якщо шлях не проходить весь стовпець зверху донизу, Зеник обирає клітинку, на яку
// шлях не потрапляє, і нічого не втрачає. Якщо шлях проходить весь стовпець, Зеник обнуляє
// найменшу клітинку стовпця. Шлях, що проходить весь стовпець c, єдиний: рядок 1 до c,
// стовпець c, рядок n від c. Тому для кожного стовпця потрібні сума цього шляху та
// найкраща сума серед усіх інших шляхів. Для цього в таблиці зберігаємо дві найкращі суми
// шляхів до кожної клітинки.

#include <iostream>

const long long NONE = -1;

// Додає кандидата до пари найкращих сум (first >= second).
void addCandidate(long long value, long long &first, long long &second) {
    if (value == NONE) {
        return;
    }
    if (value > first) {
        second = first;
        first = value;
    } else if (value > second) {
        second = value;
    }
}

// Рахує дві найкращі суми шляхів до клітинки (i, j) за значеннями сусідніх клітинок.
void computeCell(const long long *table, long long *best, long long *second, int m, int i, int j) {
    int cell = i * m + j;
    long long first = NONE;
    long long other = NONE;
    if (i == 0 && j == 0) {
        first = 0;
    }
    if (i > 0) {
        addCandidate(best[cell - m], first, other);
        addCandidate(second[cell - m], first, other);
    }
    if (j > 0) {
        addCandidate(best[cell - 1], first, other);
        addCandidate(second[cell - 1], first, other);
    }
    best[cell] = first + table[cell];
    second[cell] = NONE;
    if (other != NONE) {
        second[cell] = other + table[cell];
    }
}

// Дві найкращі суми шляхів від (1,1) до клітинки (n,m).
void findTopPaths(const long long *table, int n, int m, long long &bestSum, long long &secondSum) {
    long long *best = new long long[n * m];
    long long *second = new long long[n * m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            computeCell(table, best, second, m, i, j);
        }
    }
    bestSum = best[n * m - 1];
    secondSum = second[n * m - 1];
    delete[] best;
    delete[] second;
}

// Префіксні суми першого рядка та суфіксні суми останнього рядка.
void buildRowSums(const long long *table, int n, int m, long long *firstRow, long long *lastRow) {
    firstRow[0] = 0;
    for (int j = 0; j < m; j++) {
        firstRow[j + 1] = firstRow[j] + table[j];
    }
    lastRow[m] = 0;
    for (int j = m - 1; j >= 0; j--) {
        lastRow[j] = lastRow[j + 1] + table[(n - 1) * m + j];
    }
}

// Сума та мінімум елементів стовпця c.
void scanColumn(const long long *table, int n, int m, int c, long long &columnSum, long long &columnMin) {
    columnSum = 0;
    columnMin = table[c];
    for (int i = 0; i < n; i++) {
        columnSum += table[i * m + c];
        if (table[i * m + c] < columnMin) {
            columnMin = table[i * m + c];
        }
    }
}

// Результат гри, якщо Марічка обрала стовпець c.
long long columnValue(const long long *table, int n, int m, int c, const long long *firstRow, const long long *lastRow, long long bestSum, long long secondSum) {
    long long columnSum = 0;
    long long columnMin = 0;
    scanColumn(table, n, m, c, columnSum, columnMin);

    // Сума єдиного шляху, що проходить весь стовпець c.
    long long fullColumnPath = firstRow[c + 1] + (columnSum - table[c]) + lastRow[c + 1];

    // Найкраща сума серед шляхів, які не проходять весь стовпець.
    long long otherPaths = bestSum;
    if (fullColumnPath == bestSum && secondSum < bestSum) {
        otherPaths = secondSum;
    }

    long long value = otherPaths;
    if (fullColumnPath - columnMin > value) {
        value = fullColumnPath - columnMin;
    }
    return value;
}

// Розв'язує задачу: мінімум за стовпцями результату гри.
long long playGame(const long long *table, int n, int m) {
    long long bestSum = 0;
    long long secondSum = 0;
    findTopPaths(table, n, m, bestSum, secondSum);

    long long *firstRow = new long long[m + 1];
    long long *lastRow = new long long[m + 2];
    buildRowSums(table, n, m, firstRow, lastRow);

    long long answer = -1;
    for (int c = 0; c < m; c++) {
        long long value = columnValue(table, n, m, c, firstRow, lastRow, bestSum, secondSum);
        if (answer == -1 || value < answer) {
            answer = value;
        }
    }

    delete[] firstRow;
    delete[] lastRow;
    return answer;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    long long *table = new long long[n * m];
    for (int i = 0; i < n * m; i++) {
        std::cin >> table[i];
    }

    long long answer = playGame(table, n, m);
    std::cout << answer << "\n";

    delete[] table;
    return 0;
}
