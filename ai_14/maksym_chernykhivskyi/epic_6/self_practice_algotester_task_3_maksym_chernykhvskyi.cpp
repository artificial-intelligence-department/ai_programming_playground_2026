/*Epic 6 - Нормальні числа
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

const int MAXV = 500000; // Максимальне значення елемента послдовності

bool isComposite[MAXV + 1]; // true якщо число складене або 0 чич 1
bool seen[MAXV + 1]; // true якщо просте число вже зустрічалось зліва

class Tree {
    private:
        int tree_arr[MAXV + 1]; // зберігає кількість доданих чисел на відрізку довжиною (i & -i), що
// закінчується в i.

    public: // Конструктор
        Tree() {
            for (int i = 0; i <= MAXV; i++) {
                tree_arr[i] = 0;
            }
        }
        // Додає число i: збільшує лічильник у всіх вузлах, чиї відрізки містять i.
        void add(int i) {
            for (; i <= MAXV; i += i & -i) { // i & -i - це значення наймолодшого одиничного біта числа i
                tree_arr[i]++;
            }
        }
        // Повертає кількість доданих чисел, які <= i.
        int count(int i) const {
            int result = 0;
            for (; i > 0; i -= i & -i) { // Відрізок [1..i] розбивається на готові відрізки вузлів
                result += tree_arr[i];
            }
            return result;
        }
};

int main() {
    // Решето Ератосфена: позначаємо складені числа до MAXV.
    isComposite[0] = isComposite[1] = true;
    for (int i = 2; (long long)i * i < MAXV; i++) {
        if (!isComposite[i]) {
            // Усі кратні i, починаючи з i * i, складені
            for (int j = i * i; j <= MAXV; j += i) {
                isComposite[j] = true;
            }
        }
    }
    int n;
    cin >> n;

    Tree tree; // Зберігає різні прості числа, що вже були зліва

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        // Нормальність числа a: скільки різних простих, менших за a, було зліва.
        cout << tree.count(a - 1);
        if (i + 1 < n) {
            cout << " ";
        }

        if (!isComposite[a] && !seen[a]) {
            seen[a] = true;
            tree.add(a);
        }
    }
}