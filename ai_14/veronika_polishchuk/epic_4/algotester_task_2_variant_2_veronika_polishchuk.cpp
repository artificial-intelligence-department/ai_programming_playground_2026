/*
- Задача: Лабораторна робота алготестер 2, варіант 2
- Поліщук Вероніка
- Група 14
*/
#include <iostream>

using namespace std;

// Функція для обчислення та виведення сум сусідніх елементів масиву
void sum(int n, int arr[100000]){
    for (int i = 0; i < n-1; i++){
        int current_sum = arr[i] + arr[i+1];
        cout << current_sum << " ";
    }
}

int main(){
    int n, a, b, c, arr[100000];

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    cin >> a >> b >> c;

    // Пошук індексів першого входження значень a, b та c
    int aindex = -1, bindex = -1, cindex = -1;
    for (int i = 0; i < n; i++) {
        if (aindex == -1 && arr[i] == a) { aindex = i; continue; }
        if (bindex == -1 && arr[i] == b) { bindex = i; continue; }
        if (cindex == -1 && arr[i] == c) { cindex = i; continue; }
    }
    
    // Збереження знайдених валідних індексів у масив для подальшої обробки
    int indices[3];
    int count = 0;
    if (aindex != -1) indices[count++] = aindex;
    if (bindex != -1) indices[count++] = bindex;
    if (cindex != -1) indices[count++] = cindex;

    // Сортування масиву індексів за спаданням (бульбашкове сортування)
    // щоб видаляти елементи з кінця масиву і не порушити правильність менших індексів при зсуві
    for (int i = 0; i < count; i++){
        for (int j = 0; j < count - i - 1; j++){
            if (indices[j] < indices[j+1]){
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            } 
        }
    }
    
    // Видалення знайдених елементів шляхом зсуву всіх наступних елементів вліво
    for (int k = 0; k < count; k++){
        int idx = indices[k];
        for (int i = idx; i < n; i++){
            arr[i] = arr[i+1];
        }
        n--;
    }
    
    if (n <= 0) n = 1;
    cout << n-1 << endl;
    // Виклик функції для розрахунку та виведення самих сум
    sum(n, arr);
    
    return 0;
}