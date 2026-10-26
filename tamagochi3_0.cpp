#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <utility>
#include <regex>

using namespace std;

const int min_stat = 0;
const int max_stat = 100;

const int start_health = 100;
const int start_hunger = 50;
const int start_energy = 80;
const int start_mood = 50;

const int feed_hunger = 30;
const int feed_energy = 10;
const int play_hunger = 35;
const int play_energy = 15;
const int play_mood = 25;

const int starve_penalty = 20;
const int exhaust_penalty = 20;

const int low_stat = 30;
const int high_hunger = 70;

const int bar_width = 10;

const bool events_on = true;
const int event_chance = 15;
const int treat_hunger = 20;
const int treat_mood = 15;
const int sick_health = 20;

const bool fixed_directions = false;
const int game_rounds = 5;
const int game_win_mood = 40;
const int game_lose_mood = 10;
const int game_hunger = 10;
const int game_energy = 10;

const int log_size = 30;
const int hungry_limit = 80;
const double bad_avg = 70.0;

const int child_day = 3;
const int teen_day = 7;
const int adult_day = 12;
const int final_stage = 3;
const string stage_names[] = {"малюк", "дитина", "підліток", "дорослий"};

const int max_pets = 10;

string word_form(int n, const string& one, const string& few, const string& many) {
    
    int last2 = n % 100;
    int last1 = n % 10;
    if (last2 >= 11 && last2 <= 14) return many;
    if (last1 == 1) return one;
    if (last1 >= 2 && last1 <= 4) return few;
    return many;
}

string days_word(int n) {
    return word_form(n, "день", "дні", "днів");
}

int read_choice() {
    string line;
    if (!getline(cin, line)) return 0;
    if (line.size() == 1 && line[0] >= '0' && line[0] <= '9') {
        return line[0] - '0';
    }
    return -1;
}

bool is_valid_name(const string &name) {
    regex pattern("^[a-zA-zа-яА-ЯіІєЄїЇ]+([ \\-'’][a-zA-Zа-яА-ЯіІєЄїЇґҐ]+)*$");

    return regex_match(name, pattern);
}

string ask_name() {
    string name;
    while (true) {
        cout << "\nПридумай ім'я для улюбленця: ";
        if (!getline(cin, name)) return "Бобік";
        if (name.empty()) return "Бобік";
        if (is_valid_name(name)) return name;
        cout << "Ім'я може містити лише літери (ще можна пробіл, дефіс, апостроф). Спробуй ще раз.\n";
    }
}

bool ask_new_egg(int pets_count) {
    if (pets_count >= max_pets) {
        cout << "\nУ династії вже " << max_pets << " вихованців, яєць більше немає.\n";
        return false;
    }
    cout << "\nНове яйце? 1 - так, 0 - ні\n> ";
    return read_choice() == 1;
}

void print_bar(const string& label, int value) {
    int filled = value * bar_width / max_stat;
    cout << label << "[";
    for (int i = 0; i < bar_width; i++) {
        cout << (i < filled ? '=' : ' ');
    }
    cout << "] " << value << "\n";
}

string draw_face(int health, int hunger, int energy, int mood) {
    if (health < low_stat) return "(x_x) вмирає..";
    if (hunger > high_hunger) return "(>_<) голодний!";
    if (energy < low_stat) return "(-_-) сонний...";
    if (mood < low_stat) return "(T_T) сумний";
    return "(^_^) щасливий";
}

int safe_plays(int hunger, int energy) {
    if (hunger + play_hunger >= max_stat || energy - play_energy <= min_stat) return 0;
    return 1 + safe_plays(hunger + play_hunger, energy - play_energy);
}

int safe_plays_loop(int hunger, int energy) {
    int count = 0;
    while (hunger + play_hunger < max_stat && energy - play_energy > min_stat) {
        hunger += play_hunger;
        energy -= play_energy;
        count++;
    }
    return count;
}

void print_status(const string& name, int health, int hunger, int energy, int mood) {
    cout << "\n=== " << name << " ===\n";
    cout << draw_face(health, hunger, energy, mood) << "\n";
    print_bar("Здоров'я ", health);
    print_bar("Голод    ", hunger);
    print_bar("Енергія  ", energy);
    print_bar("Настрій  ", mood);

    int n = safe_plays(hunger, energy);
    cout << name << ": можу погратися ще " << n << " "
         << word_form(n, "раз", "рази", "разів") << ", потім захочу їсти\n";
}

void print_menu() {
    cout << "\n1) Погодувати  2) Погратись  3) Поспати  4) Міні-гра  5) Журнал  6) Ветеринар  0) Вийти\n> ";
}

int count_mistakes(const bool m[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (m[i]) count++;
    }
    return count;
}

void print_finale(const string& name, bool died, int hunger, int energy, int mood, int days, int mistakes) {
    cout << "\n";
    if (died) {
        cout << name << " не вижив... ";
        if (hunger == max_stat && energy == min_stat) cout << "(помер від голоду та виснаження)\n";
        else if (energy == min_stat) cout << "(помер від виснаження)\n";
        else if (hunger == max_stat) cout << "(помер від голоду)\n";
        else cout << "(помер за трагічних обставин)\n";
    } else {
        cout << "Ти попрощався з " << name << ". Гру завершено.\n";
    }
    cout << name << " прожив " << days << " " << days_word(days) << "\n";
    cout << "Помилок догляду: " << mistakes << "\n";
    print_bar("Настрій  ", mood);
}

void feed_pet(int& hunger, int& energy) {
    hunger -= feed_hunger;
    energy += feed_energy;
    cout << "Улюбленець поїв. Ням-ням\n";
}

void play_pet(int& hunger, int& energy, int& mood) {
    hunger += play_hunger;
    energy -= play_energy;
    mood += play_mood;
    cout << "Ти побавився з улюбленцем, він щасливий!\n";
}

void sleep_pet(int& energy) {
    energy = max_stat;
    cout << "Улюбленець солоденько подрімав!\n";
}

bool is_alive(int health) {
    return health > 0;
}

void clamp_stat(int& value) {
    if (value < min_stat) value = min_stat;
    else if (value > max_stat) value = max_stat;
}

void clamp_all(int& health, int& hunger, int& energy, int& mood) {
    clamp_stat(health);
    clamp_stat(hunger);
    clamp_stat(energy);
    clamp_stat(mood);
}

bool apply_survival(int& health, int& hunger, int& energy) {
    bool mistake = false;
    if (hunger == max_stat) { health -= starve_penalty; mistake = true; }
    if (energy == min_stat) { health -= exhaust_penalty; mistake = true; }
    clamp_stat(health);
    return mistake;
}

void random_event(const string& name, int& health, int& hunger, int& mood) {
    if (rand() % 100 >= event_chance) return;

    cout << "\n================================\n";
    if (rand() % 2 == 0) {
        cout << name << " знайшов ласощі! голод -" << treat_hunger
             << ", настрій +" << treat_mood << "\n";
        hunger -= treat_hunger;
        mood += treat_mood;
    } else {
        cout << name << " захворів... здоров'я -" << sick_health << "\n";
        health -= sick_health;
    }
    cout << "================================\n";
}

bool end_of_turn(const string& name, int& health, int& hunger, int& energy, int& mood) {
    if (events_on) random_event(name, health, hunger, mood);
    clamp_all(health, hunger, energy, mood);
    return apply_survival(health, hunger, energy);
}

void log_day(int hunger_log[], bool mistake_log[], int& entries, int hunger, bool mistake) {
    if (entries >= log_size) return;
    hunger_log[entries] = hunger;
    mistake_log[entries] = mistake;
    entries++;
}

void print_journal(const int h[], const bool m[], int n, bool only_mistakes = false) {
    for (int i = 0; i < n; i++) {
        if (only_mistakes && !m[i]) continue;
        cout << "День " << (i + 1) << ": голод " << h[i];
        if (m[i]) cout << "   <- помилка догляду";
        cout << "\n";
    }
}

void show_journal(const int h[], const bool m[], int n) {
    cout << "\n=== Журнал догляду ===\n";
    if (n == 0) {
        cout << "Журнал порожній: ще не було жодного ходу.\n";
        return;
    }
    cout << "1) усі дні  2) лише помилки\n> ";
    int mode = read_choice();
    if (mode != 1 && mode != 2) {
        cout << "Невідомий вибір, журнал не відкрито.\n";
        return;
    }
    print_journal(h, m, n, mode == 2);
    cout << "Помилок догляду: " << count_mistakes(m, n) << "\n";
    if (n == log_size) cout << "(журнал заповнений: нові дні вже не записуються)\n";
}

int hits_to_win(int rounds) {
    return rounds / 2 + 1;
}

int guess_game(int rounds = game_rounds) {
    int need = hits_to_win(rounds);
    int hits = 0;
    int misses = 0;

    for (int i = 0; i < rounds; i++) {
        int direction = (fixed_directions ? i : rand()) % 2 + 1;

        int guess;
        do {
            cout << "Раунд " << (i + 1) << ": куди дивиться вихованець? 1 - ліворуч, 2 - праворуч\n> ";
            guess = read_choice();
        } while (guess != 1 && guess != 2 && !cin.eof());

        if (guess != 1 && guess != 2) break;

        cout << "Вихованець дивився " << (direction == 1 ? "ліворуч" : "праворуч") << ". ";
        if (guess == direction) { hits++; cout << "Влучив!\n"; }
        else { misses++; cout << "Промах.\n"; }
        cout << "Рахунок " << hits << ":" << misses << "\n";

        if (hits == need || misses == need) break;
    }
    return hits;
}

void play_mini_game(int& hunger, int& energy, int& mood) {
    cout << "\nМіні-гра \"Ліво чи право\": вихованець відвертається, вгадай куди!\n";
    int hits = guess_game();

    if (hits >= hits_to_win(game_rounds)) {
        cout << "Перемога! Вихованець у захваті.\n";
        mood += game_win_mood;
    } else {
        cout << "Цього разу не пощастило, але було весело.\n";
        mood += game_lose_mood;
    }
    hunger += game_hunger;
    energy -= game_energy;
}

int growth_stage(int days) {
    if (days >= adult_day) return 3;
    if (days >= teen_day) return 2;
    if (days >= child_day) return 1;
    return 0;
}

string adult_type(int mistakes) {
    if (mistakes == 0) return "Зірочка";
    if (mistakes <= 2) return "Добряк";
    return "Бешкетник";
}

void print_portrait(int stage) {
    int r = stage + 1;
    for (int i = 0; i <= 2 * r; i++) {
        for (int j = 0; j <= 2 * r; j++) {
            cout << (abs(i - r) + abs(j - r) <= r ? '@' : ' ');
        }
        cout << "\n";
    }
}

void check_growth(int days, int mistakes) {
    static int prev_stage = 0;

    if (days == 0) {
        prev_stage = 0;
        return;
    }

    int stage = growth_stage(days);
    if (stage == prev_stage) return;
    prev_stage = stage;

    cout << "\n*** Вихованець виріс: тепер " << stage_names[stage];
    if (stage == final_stage) cout << " - " << adult_type(mistakes);
    cout << "! ***\n";
    print_portrait(stage);
}

void hunger_stats(const int a[], int n, int& mn, int& mx, double& avg) {
    mn = a[0];
    mx = a[0];
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
        sum += a[i];
    }
    avg = static_cast<double>(sum) / n;
}

int first_mistake(const bool m[], int n) {
    int day = -1;
    for (int i = 0; i < n; i++) {
        if (m[i]) {
            day = i + 1;
            break;
        }
    }
    return day;
}

int longest_streak(const int a[], int n, int limit = hungry_limit) {
    int best = 0;
    int current = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= limit) {
            current++;
            if (current > best) best = current;
        } else {
            current = 0;
        }
    }
    return best;
}

void vet_exam(const int h[], const bool m[], int n) {
    cout << "\n=== Ветеринар ===\n";
    if (n == 0) {
        cout << "Оглядати нічого: журнал порожній.\n";
        return;
    }

    int mn, mx;
    double avg;
    hunger_stats(h, n, mn, mx, avg);
    int first = first_mistake(m, n);

    cout << "Голод: мін " << mn << ", макс " << mx
         << ", середній " << fixed << setprecision(1) << avg << defaultfloat << "\n";
    if (first == -1) cout << "Помилок догляду немає.\n";
    else cout << "Перша помилка догляду: день " << first << "\n";
    cout << "Найдовша серія голодних днів поспіль: " << longest_streak(h, n) << "\n";
    cout << "Діагноз: " << (avg >= bad_avg ? "недогодований" : "здоровий") << "\n";
}

int live_once(const string& name) {
    int health = start_health;
    int hunger = start_hunger;
    int energy = start_energy;
    int mood = start_mood;
    int days = 0;

    int hunger_log[log_size];
    bool mistake_log[log_size];
    int entries = 0;

    check_growth(0, 0);

    while (is_alive(health)) {
        print_status(name, health, hunger, energy, mood);
        print_menu();
        int choice = read_choice();

        if (choice == 0) break;

        switch (choice) {
            case 1: feed_pet(hunger, energy); break;
            case 2: play_pet(hunger, energy, mood); break;
            case 3: sleep_pet(energy); break;
            case 4: play_mini_game(hunger, energy, mood); break;
            case 5: show_journal(hunger_log, mistake_log, entries); continue;
            case 6: vet_exam(hunger_log, mistake_log, entries); continue;
            default:
                cout << "Невідома команда, спробуй ще раз.\n";
                continue;
        }

        bool mistake = end_of_turn(name, health, hunger, energy, mood);
        log_day(hunger_log, mistake_log, entries, hunger, mistake);
        days++;
        if (is_alive(health)) check_growth(days, count_mistakes(mistake_log, entries));
    }

    print_finale(name, !is_alive(health), hunger, energy, mood, days, count_mistakes(mistake_log, entries));
    return days;
}

void sort_dynasty(string names[], int lives[], int n) {
    for (int pass = 0; pass < n - 1; pass++) {
        for (int j = 0; j < n - 1 - pass; j++) {
            if (lives[j] < lives[j + 1]) {
                swap(lives[j], lives[j + 1]);
                swap(names[j], names[j + 1]);
            }
        }
    }
}

void print_dynasty(const string names[], const int lives[], int n) {
    cout << "\n=== Династія ===\n";
    for (int i = 0; i < n; i++) {
        cout << (i + 1) << ". " << names[i] << " - " << lives[i] << " " << days_word(lives[i]) << "\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    string names[max_pets];
    int lives[max_pets];
    int pets = 0;

    bool again;
    do {
        names[pets] = ask_name();
        lives[pets] = live_once(names[pets]);
        pets++;
        again = ask_new_egg(pets);
    } while (again);

    sort_dynasty(names, lives, pets);
    print_dynasty(names, lives, pets);
    return 0;
}