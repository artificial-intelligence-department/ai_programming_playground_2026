//сет
#include <iostream>

using namespace std;

enum Color { RED = 0, GREEN = 1, BLUE = 2 };
enum Texture { FILLED = 0, PARTIAL = 1, EMPTY = 2 };
enum Shape { DIAMOND = 0, SQUIGGLE = 1, OVAL = 2 };


struct Card {
    int count;    
    Color color;
    Texture texture;
    Shape shape;


    int toIndex() const {
        return count * 27 + color * 9 + texture * 3 + shape;
    }


    static Card fromIndex(int id) {
        Card c;
        c.count = (id / 27) % 3;
        c.color = static_cast<Color>((id / 9) % 3);
        c.texture = static_cast<Texture>((id / 3) % 3);
        c.shape = static_cast<Shape>(id % 3);
        return c;
    }


    Card operator+(const Card& other) const {
        Card res;
        res.count = (6 - this->count - other.count) % 3;
        res.color = static_cast<Color>((6 - this->color - other.color) % 3);
        res.texture = static_cast<Texture>((6 - this->texture - other.texture) % 3);
        res.shape = static_cast<Shape>((6 - this->shape - other.shape) % 3);
        return res;
    }
};


istream& operator>>(istream& in, Card& c) {
    char s[8];
    if (!(in >> s)) return in;

    c.count = s[0] - '1';

    if (s[1] == 'R') c.color = RED;
    else if (s[1] == 'G') c.color = GREEN;
    else c.color = BLUE;

    if (s[2] == 'F') c.texture = FILLED;
    else if (s[2] == 'P') c.texture = PARTIAL;
    else c.texture = EMPTY;

    if (s[3] == 'D') c.shape = DIAMOND;
    else if (s[3] == 'S') c.shape = SQUIGGLE;
    else c.shape = OVAL;

    return in;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    long long cnt[81] = {0};

    for (int i = 0; i < n; ++i) {
        Card c;
        cin >> c; 
        cnt[c.toIndex()]++;
    }

    long long ans = 0;

    for (int i = 0; i < 81; ++i) {
        if (cnt[i] == 0) continue;
        Card card1 = Card::fromIndex(i);

        for (int j = i; j < 81; ++j) {
            if (cnt[j] == 0) continue;
            Card card2 = Card::fromIndex(j);

            Card card3 = card1 + card2;
            int k = card3.toIndex();

            if (k < j || cnt[k] == 0) continue;

            if (i == j) {
                ans += cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / 6;
            } else {
                ans += cnt[i] * cnt[j] * cnt[k];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}