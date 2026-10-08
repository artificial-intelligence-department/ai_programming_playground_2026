#include <iostream>
using namespace std;

int countVariants(int fours, int sevens);

int main() {
    char digits[17];
    int fours = 0;
    int sevens = 0;

    cin >> digits;

    for (int i = 0; digits[i] != '\0'; i++) {
        if (digits[i] == '4') {
            fours++;
        }
        else {
            sevens++;
        }
    }

    int result = countVariants(fours, sevens);
    cout << result << endl;

    return 0;
}

int countVariants(int fours, int sevens) {
    if (fours == 0 || sevens == 0) {
        return 1;
    }

    int withFour = countVariants(fours - 1, sevens);
    int withSeven = countVariants(fours, sevens - 1);

    return withFour + withSeven;
}
