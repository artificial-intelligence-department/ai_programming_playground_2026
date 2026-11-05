/*
Лабораторна робота №4, Завдання №1, Варіант №16.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
using namespace std;

const int MAX = 100;

void enqueue(int *queue, int &count, int value){
        if (count >= MAX){
                cout << "Помилка: черга переповнена. Не вдалося додати елемент. " << value << endl;
                return;
        }
        queue[count] = value;
        count++;
        cout << "Додано: " << value << endl;
}

void dequeue(int *queue, int &count){
        if (count == 0){
                cout << "Помилка: черга порожня. Нічого видаляти." << endl;
                return;
        }

        int remvalue = queue[0];

        for (int i = 0; i < count - 1; i++){
                queue[i] = queue[i + 1];
        }
        count--;
        cout << "Видалено: " << remvalue << endl;
}

void printqueue(int *queue, int count){
        if (count == 0){
                cout << "Черга порожня." << endl;
                return;
        }
        cout << "Поточний стан черги: ";
        for (int i = 0; i < count; i++){
                cout << queue[i] << " ";
        }
        cout << endl;
}

int main(){
        int queue[MAX];
        int count = 0;
        int choice = 0, value = 0;

        do{
                cout << "===Меню керування чергою===" << endl;
                cout << "1. Додати елемент" << endl;
                cout << "2. Видалити елемент" << endl;
                cout << "3. Вивести стан черги" << endl;
                cout << "4. Вийти" << endl;
                cout << "Виберіть дію: ";
                if (!(cin >> choice)){
                        cout << "Помилка: введено некоректне значення. Спробуйте ще раз." << endl;
                        cin.clear();
                        cin.ignore(6769, '\n');
                        continue;
                }

                switch (choice){
                        case 1:
                                cout << "Введіть значення: ";
                                if(!(cin >> value)){
                                        cout << "Помилка: введено некоректне значення. Спробуйте ще раз." << endl;
                                        cin.clear();
                                        cin.ignore(6769, '\n');
                                        continue;
                                }
                                enqueue(queue, count, value);
                                printqueue(queue, count);
                                break;
                        case 2:
                                dequeue(queue, count);
                                printqueue(queue, count);
                                break;
                        case 3:
                                printqueue(queue, count);
                                break;
                        case 4:
                                cout << "Вихід з програми." << endl;
                                break;
                        default:
                                cout << "Невірний вибір. Спробуйте ще раз." << endl;
                }
        } while (choice != 4);
        return 0;
}
