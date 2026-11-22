/*Epic 6 - Фокус
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <cstdio>

using namespace std;

class tree {
    private:
        struct Node { // Вузол дерева
            long long key;
            int left, right;
            int size;
        };

        Node *nodes;
        int total;
        int root;

    public:
        // Конструктор: виділяє пам'ять під capacity вузлів (по одному на кожне число)
        tree(int capacity): total(0), root(0) {
            nodes = new Node[capacity + 1];
            nodes[0].size = 0;
            nodes[0].left = nodes[0].right = 0;
        }

        // Деструктор: звільняє масив вузлів
        ~tree() {
            delete[] nodes;
        }

        // Додає число key
        void insert(long long key) {
            total++;
            nodes[total].key = key;
            nodes[total].left = nodes[total].right = 0;
            nodes[total].size = 1;

            if (root == 0) {
                root = total;
                return;
            }

            // Спускаємося від кореня до місця вставки
            int t = root;
            while (true) {
                nodes[t].size++; // новий вузол потрапить у піддерево t, тож його розмір росте
                if (key < nodes[t].key) {
                    if (nodes[t].left == 0) {  // Менші числа йдуть ліворуч
                        nodes[t].left = total;
                        return;
                    }
                    t = nodes[t].left;
                } else {
                    if (nodes[t].right == 0) { // Більші та рівні числа йдуть праворуч
                        nodes[t].right = total;
                        return;
                    }
                    t = nodes[t].right;
                }
            }
        }
        // Повертає кількість доданих чисел, строго менших за x
        int countLess(long long x) {
            int t = root;
            int result = 0;
            while (t != 0) {
                if (nodes[t].key < x) {
                    // Вузол t і все його ліве піддерево менше за x: додаємо їх разом, а решту шукаємо праворуч
                    result += nodes[nodes[t].left].size + 1;
                    t = nodes[t].right;
                } else {
                    // Вузол t не менший за x, тож усе потрібне лежить ліворуч
                    t = nodes[t].left;
                }
            }
            return result;
        }
};

int main() {
    char line[128];

    fgets(line, sizeof(line), stdin);
    int n = 0;
    sscanf(line, "%d", &n);

    tree t(n);

    int processed = 0;
    while (processed < n && fgets(line, sizeof(line), stdin) != NULL) {
        long long x, y;
        // sscanf повертає кількість успішно прочитаних чисел: 1 або 2
        int numbers = sscanf(line, "%lld %lld", &x, &y);

        if (numbers == 1) {
            t.insert(x);
            processed++;
        } else if (numbers == 2) {
            int answer = t.countLess(y) - t.countLess(x + 1);
            if (answer < 0) {
                answer = 0;
            }
            cout << answer << "\n";
            processed++;
        }
    }
    return 0;
}