/*Epic 6 - Сет
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

enum Color { RED, GREEN, BLUE };
enum Texture { FILLED, PARTIAL, EMPTY };
enum Shape { DIAMOND, SQUIGGLE, OVAL };

struct Card {
    int count;
    Color color;
    Texture texture;
    Shape shape;

    // Перетворює карту на число від 0 до 80.
    int cardToIndex() const {
        return count * 27 + color * 9 + texture * 3 + shape;
    }
    
    // З числа 0..80 відновлює карту.
    static Card indexToCard(int id) {
        Card c;
        c.count = (id / 27) % 3;
        c.color = static_cast<Color>((id / 9) % 3);
        c.texture = static_cast<Texture>((id / 3) % 3);
        c.shape = static_cast<Shape>(id % 3);
        return c;
    } 
    
    // Повертає третю карту, яка разом із цими двома утворює сет.
    Card operator+(const Card &card) const {
        Card result;
        result.count = (6 - count - card.count) % 3;
        result.color = static_cast<Color>((6 - color - card.color) % 3);
        result.texture = static_cast<Texture>((6 - texture - card.texture) % 3);
        result.shape = static_cast<Shape>((6 - shape - card.shape) % 3);
        return result;
    }
};

istream &operator>>(istream &is, Card &c) {
    char s[5];
    is >> s;
    
    c.count = s[0] - '1';
    
    if (s[1] == 'R') {
        c.color = RED;
    } else if (s[1] == 'G') {
        c.color = GREEN;
    } else {
        c.color = BLUE;
    }

    if (s[2] == 'F') {
        c.texture = FILLED;
    } else if (s[2] == 'P') {
        c.texture = PARTIAL;
    } else {
        c.texture = EMPTY;
    }

    if (s[3] == 'D') {
        c.shape = DIAMOND;
    } else if (s[3] == 'S') {
        c.shape = SQUIGGLE;
    } else {
        c.shape = OVAL;
    }

    return is;
}

int main() {
    int n;
    cin >> n;
    
    long long count[81] = {0};

    // Перебираємо пари типів карт i <= j.
    for (int i = 0; i < n; i++) {
        Card c;
        cin >> c;
        count[c.cardToIndex()]++;
    }
    
    long long answer = 0;
    
    for (int i = 0; i < 81; i++) {
        if (count[i] == 0) {
            continue;
        }
        Card card_1 = Card::indexToCard(i);
        
        for (int j = i; j < 81; j++) {
            if (count[i] == 0) {
                continue;
            }
            Card card_2 = Card::indexToCard(j);
            
            Card card_3 = card_1 + card_2;
            int k = card_3.cardToIndex();
            
            if (k < j || count[k] == 0) {
                continue;
            }
            
            if (j == i) {
                answer += count[i] * (count[i] - 1) * (count[i] - 2) / 6; 
            } else {
                answer += count[i] * count[j] * count[k];
            }
        }
    }
    cout << answer;
    return 0;
}