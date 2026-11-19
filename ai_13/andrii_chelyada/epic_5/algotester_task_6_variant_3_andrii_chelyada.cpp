// algotester lab 6v3, Челяда Андрій, ШІ-13
#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    // розмір поля N x N
    int N;
    cin >> N;
    // поле в динамічній пам'яті: масив адрес рядків з числами
    int **field = new int*[N];
    for(int i = 0; i < N; i++){
        // кожен рядок поля - окремий блок з N чисел
        field[i] = new int[N];
        // читаємо рядок цифр як текст у тимчасовий масив (9 цифр + '\0')
        char row[10];
        scanf("%s", row);
        // перетворюємо кожен символ на число: '3' - '0' = 3
        for(int j = 0; j < N; j++){
            field[i][j] = row[j] - '0';
        }
    }

    // кількість запитів
    int Q;
    cin >> Q;
    int x, y;
    // обробляємо кожен запит
    for(int i = 0; i < Q; i++){
        cin >> x >> y;
        // у задачі нумерація з 1, а в масиві з 0
        x--;
        y--;
        // клітинка вже заповнена: можна вписати лише цю цифру
        if(field[x][y] != 0){
            cout << 1 << endl;
            cout << field[x][y] << endl;
        }
        // клітинка порожня (0): шукаємо цифри, яких немає ні в рядку, ні в стовпці
        else{
            // used[d] == true означає, що цифра d уже зайнята
            bool used[10] = {false};
            // проходимо рядок x і стовпець y одночасно
            for (int k = 0; k < N; k++) {
                // клітинка з рядка x: якщо там цифра, позначаємо її зайнятою
                if (field[x][k] != 0) {
                    used[field[x][k]] = true;
                }
                // клітинка зі стовпця y
                if (field[k][y] != 0) {
                    used[field[k][y]] = true;
                }
            }
            // рахуємо вільні цифри від 1 до N
            int count = 0;
            for(int d = 1; d <= N; d++){
                if(!used[d]){
                    count++;
                }
            }
            // спершу кількість, потім самі цифри
            cout << count << endl;
            for(int d = 1; d <= N; d++){
                if(!used[d]){
                    cout << d << " ";
                }
            }
            cout << endl;
        }
    }

    // звільняємо пам'ять: спершу кожен рядок, потім масив адрес
    for(int i = 0; i < N; i++){
        delete[] field[i];
    }
    delete[] field;

    return 0;
}