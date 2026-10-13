#include <iostream>
#include <string>
#include <random>

using namespace std;

string bar(int value) {
    int filled = value / 10;
    if (filled < 0) filled = 0;   
    if (filled > 10) filled = 10;  
    return "[" + string(filled, '#') + string(10 - filled, '-') + "]";
}

string draw_face(int health, int hunger, int energy, int mood) {
    if (health < 30) return "(x_x) вмирає.." ;
    if (hunger > 70) return "(>_<)  голодний!";
    if (energy < 30) return "(-_-)  сонний...";
    if (mood < 30) return "(T_T)  сумний";
    return "(^_^)  щасливий";
}

void status(string name, int health, int hunger, int energy, int mood) {
    cout << "\n=== " << name << " ===\n";
    cout << draw_face(health, hunger, energy, mood) << "\n";
    cout << "Здоров'я     " << bar(health) << " " << health << "\n";
    cout << "Голод        " << bar(hunger) << " " << hunger << "\n";
    cout << "Енергія      " << bar(energy) << " " << energy << "\n";
    cout << "Рівень щастя " << bar(mood) << " " << mood << "\n";
}

void check(int &value) {
    if (value > 100) value = 100;
    if (value < 0) value = 0;
}

void feed(int &hunger, int &energy) {
    hunger -= 30;
    energy += 10;
    cout << "улюблинець поїв. ням-ням\n";
}

void play(int &hunger, int &energy, int &mood) {
    hunger += 35;
    energy -= 15;
    mood += 25;
    cout << "ти побавився з улюбленцем, він щасливий!\n";
}

void sleep(int &energy) {
    energy = 100;
    cout << "улюбленець солоденько подрімав!\n";
}

bool isAlive(int health) {
    return health > 0;
}

int input() {
    string line;
    if (!getline(cin, line)) return 0;

    if (line.size() == 1 && line[0] >= '0' && line[0] <= '9') {
        return line[0] - '0';
    }
    return -1;
}

bool is_bonus_action() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);
    return (dist(gen) <= 15);
}   

int main() {
    while (true) {  
        string name;
        int health = 100;
        int hunger = 50;      
        int energy = 80;
        int mood = 50;
        int days = 0;    

        cout << "\nПридумай ім'я для улюбленця: ";
        getline(cin, name);
        if (name.empty()) name = "Бобік";

        while (isAlive(health)) {
            status(name, health, hunger, energy, mood);
            cout << "\n1) Погодувати  2) Погратись  3) Поспати  0) Вийти з гри\n> ";

            int choice = input();

            switch (choice) {
                case 1: feed(hunger, energy); break;
                case 2: play(hunger, energy, mood); break;
                case 3: sleep(energy); break;
                case 0:
                    cout << "GG\n";
                    return 0;  
                default:
                    cout << "Невідома команда, спробуй ще раз.\n";
                    continue;  
            }

            if (is_bonus_action()) {
                cout << "\n================================\n\n";
                cout << name << " поцапався з дворовим котом!" << endl;
                cout << "настрій +30, здоров'я -10" << endl;
                mood += 30;
                health -= 10;
            }

            check(health);   
            check(hunger);   
            check(energy);   
            check(mood);   
            if (hunger == 100) health -= 20;
            if (energy == 0) health -= 20;
            days++; 
        }

        cout << "\n" << name << " не вижив... ";
        if (hunger == 100 && energy == 0) cout << "(помер від голоду та виснаження)\n";
        else if (energy == 0) cout << "(помер від виснаження)\n";
        else if (hunger == 100) cout << "(помер від голоду)\n";
        else cout << "(помер за трагічних обставин)\n";
        cout << "Прожито днів: " << days << "\n";

        cout << "\nЗавести нового улюбленця?  1) Так  0) Ні\n> ";
        if (input() != 1) return 0;
    }
}