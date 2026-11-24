/*  
Задача: Self-practice. Завдання №1.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/

#include <iostream>
using namespace std;

struct Queue { //черга на кільцевому масиві
    long long data[2005];
    int head;
    int tail;
    int size;
    Queue() {
        head = 0;
        tail = 0;
        size = 0;
    }

    
    void enqueue(long long x) {//додати елемент у кінець черги
        data[tail] = x;
        tail = (tail + 1) % 2005;   //дійшли до кінця масиву - повертаємось на початок
        size++;
    }

    
    long long dequeue() {//забрати елемент з початку черги і повернути його
        long long x = data[head];
        head = (head + 1) % 2005;
        size--;
        return x;
    }
};

long long a[2005], best[2005];

int main() {
    int n;
    long long b;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> b;


    Queue q;
    for (int i = 0; i < n; i++) { //у чергу кладемо ціни в порядку корзин
        long long c;
        cin >> c;
        q.enqueue(c);
    }

    //найкраща ціна для кожної групи яблук поки що дуже велика
    for (int i = 0; i < n; i++) best[i] = 2000000000;

    long long answer = -1;

    for (int S = 0; S < n; S++) {
        long long total = (long long)S * b;   //плата за S перформансів

        
        for (int i = 0; i < n; i++) { //проходимо всю чергу: беремо ціну, використовуємо, ставимо назад в кінець
            long long price = q.dequeue();
            if (price < best[i]) best[i] = price; //найдешевша ціна для групи i
            total += a[i] * best[i];
            q.enqueue(price);
        }

        if (answer == -1 || total < answer) answer = total;

        
        q.enqueue(q.dequeue()); //перша ціна йде в кінець, усе зсувається
    }

    cout << answer << endl;
    return 0;
}