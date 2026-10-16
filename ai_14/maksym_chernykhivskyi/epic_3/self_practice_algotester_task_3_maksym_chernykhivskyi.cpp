/*Epic 3 - Summer School
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    
    if (n < k || n > 3 * k) {
        cout << "Impossible";
        return 0;
    }
        
    int teams_of_3, teams_of_2, teams_of_1;
    
    // Умовно призначаємо кожній команді по 1 студенту
    // remaining — це кількість непризначених студентів
    int remaining = n - k;
    
    // Оскільки до команди з 1 людини можна додати ще максимум 2 студентів,
    // ділимо залишок на 2. Це дасть кількість команд, які будуть заповнені повністю
    teams_of_3 = remaining / 2;
    
    // Якщо після формування трійок залишився ще 1 "зайвий" студент,
    // він піде в окрему команду, де стане 2 людини
    teams_of_2 = remaining % 2;
    
    // Усі команди, що залишилися, так і залишаться з 1 студентом.
    teams_of_1 = k - teams_of_3 - teams_of_2;
    
    for (int i = 0; i < teams_of_3; i++) {
        cout << 3 << " ";
    }
    for (int i = 0; i < teams_of_2; i++) {
        cout << 2 << " ";
    }
    for (int i = 0; i < teams_of_1; i++) {
        cout << 1 << " ";
    }
}