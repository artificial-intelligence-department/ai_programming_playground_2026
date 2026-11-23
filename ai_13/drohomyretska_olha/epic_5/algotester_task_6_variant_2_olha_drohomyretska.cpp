/*
Задача: Алготестер. Лабораторна робота №6 
Варіант: 2
Автор: Ольга Дрогомирецька
Група: Ші-13
*/
#include <iostream> 
#include <string> 
#include <cstdlib>
using namespace std;

void quickSort(string& text, int left, int right);

int main () {
    char board[8][8];
    //вводимо дошку. порожня клітинка - це буква О
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> board[i][j];
        }
    }

    int queries;
    cin >> queries;

    for (int k = 0; k < queries; k++) {
        int x, y;
        cin >> x >> y;
        //переводимо координати в індекси масиву
        x--;
        y--;

        //якшо клітинка зайнята
        if (board[x][y] != 'O') {
            cout << "X\n";
            continue;
        }
        string result = ""; //створюю порожній рядок для перевірок
        //перевіряємо всі фігури на дошці
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char figure = board[i][j];

                int rowDistance = abs(x - i);
                int colDistance = abs(y - j);

                bool attacks = false;

                //пішак атакує вниз по діагоналі
                if (figure == 'P') {
                    attacks = (x == i + 1 && colDistance == 1);
                }
                //тура атакує по радку або стовпцю
                else if (figure == 'R') {
                    attacks = (x == i || y == j);
                }
                //кінь атакує ходом 2 на 1 або на 2
                else if (figure == 'N') {
                    attacks = (rowDistance == 2 && colDistance == 1) 
                    || (rowDistance == 1 && colDistance == 2);
                }
                //слон атакує по діагоналі
                else if (figure == 'B') {
                    attacks = (rowDistance == colDistance);
                }
                //король атакує сусідні клітинки
                else if (figure == 'K') {
                    attacks = (rowDistance <= 1 && colDistance <= 1);
                }
                //королева атакує як тура та слон
                else if (figure == 'Q') {
                    attacks = (x == i || y == j || rowDistance == colDistance);
                }
                //додаємо букву, якшо її ще немає у відповіді
                if (attacks && result.find(figure) == string::npos) {
                    result += figure;
                }
            }
        }
if (result.empty()) {
            cout << "O\n";
        } else {
            // Сортуємо букви за абеткою.
            int length = result.size();
            quickSort(result, 0, length - 1);

            cout << result << "\n";
        }
    }

    return 0;
}

// Швидке сортування.
void quickSort(string& text, int left, int right) {
    int i = left;
    int j = right;
    char pivot = text[(left + right) / 2];

    while (i <= j) {
        while (text[i] < pivot) {
            i++;
        }

        while (text[j] > pivot) {
            j--;
        }

        if (i <= j) {
            // Міняємо букви місцями.
            char temp = text[i];
            text[i] = text[j];
            text[j] = temp;

            i++;
            j--;
        }
    }

    // Сортуємо ліву частину.
    if (left < j) {
        quickSort(text, left, j);
    }

    // Сортуємо праву частину.
    if (i < right) {
        quickSort(text, i, right);
    }
}