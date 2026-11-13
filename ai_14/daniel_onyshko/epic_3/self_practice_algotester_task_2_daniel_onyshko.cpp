   /* Перехід дороги
   Онишко Даніель
   */
   #include <iostream>
    #include <vector>

    using namespace std;

    int main() {
        int n;
        if (!(cin >> n)) return 0;

        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        int road_crossings = 0;
        
        // проходимо по списку однокласників і рахуємо кількість переходів дороги
        for (int i = 1; i < n; ++i) {
            // якщо попередній будинок був на іншому боці вулиці, ніж поточний
            bool prev_even = (a[i - 1] % 2 == 0);
            bool curr_even = (a[i] % 2 == 0);
            
            if (prev_even != curr_even) {
                road_crossings++;
            }
        }

        cout << road_crossings << "\n";

        return 0;
    }