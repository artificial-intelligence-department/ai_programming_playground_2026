// Algotester, задача "Squaring the Cube"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40450
// Ткач Артем, ШІ-13
//
// Умова: з усіх одиничних кубиків паралелепіпеда h x w x d потрібно скласти прямокутник
// a x b (a >= b) так, щоб різниця a - b була найменшою.
//
// Ідея: a * b = h * w * d, тому b - це дільник добутку. Розкладаємо h, w, d на прості
// множники, перебираємо всі дільники b, що не перевищують квадратний корінь добутку,
// і обираємо той, для якого a = (h * w * d) / b найближче до b. Добуток може сягати 10^42,
// тому використовуємо __int128 і long double для відсікання.

#include <iostream>

typedef unsigned __int128 BigNumber;

const int MAX_PRIMES = 64;
const BigNumber LIMIT = ((BigNumber)1) << 126;

long long primes[MAX_PRIMES];
int powers[MAX_PRIMES];
int primeCount = 0;

bool found = false;
BigNumber bestSmall = 0;
BigNumber bestBig = 0;
long double productApprox = 1;

// Додає простий множник prime у загальний розклад добутку.
void addPrime(long long prime, int times) {
    for (int i = 0; i < primeCount; i++) {
        if (primes[i] == prime) {
            powers[i] += times;
            return;
        }
    }
    primes[primeCount] = prime;
    powers[primeCount] = times;
    primeCount++;
}

// Розкладає number на прості множники.
void factorize(long long number) {
    for (long long p = 2; p * p <= number; p++) {
        int times = 0;
        while (number % p == 0) {
            number /= p;
            times++;
        }
        if (times > 0) {
            addPrime(p, times);
        }
    }
    if (number > 1) {
        addPrime(number, 1);
    }
}

// Запам'ятовує пару (small, big), якщо вона краща за поточну найкращу.
void recordCandidate(BigNumber small, BigNumber big, bool overflow) {
    if (overflow || small > big) {
        return;
    }
    if (!found || big - small < bestBig - bestSmall) {
        found = true;
        bestSmall = small;
        bestBig = big;
    }
}

// big *= prime^times із перевіркою переповнення.
void multiplyBig(BigNumber &big, bool &overflow, long long prime, int times) {
    for (int k = 0; k < times; k++) {
        if (!overflow) {
            if (big > LIMIT / (BigNumber)prime) {
                overflow = true;
            } else {
                big = big * (BigNumber)prime;
            }
        }
    }
}

// Перебирає дільники small. big - добуток тих степенів, що залишилися (V / small),
// overflow = true, якщо big вже не вміщується у число.
void search(int index, BigNumber small, BigNumber big, bool overflow) {
    if ((long double)small * (long double)small > productApprox * 1.000001L) {
        return;
    }
    if (index == primeCount) {
        recordCandidate(small, big, overflow);
        return;
    }

    BigNumber smallValue = small;
    int taken = 0;
    while (taken <= powers[index] && (long double)smallValue <= 2e21L) {
        BigNumber newBig = big;
        bool newOverflow = overflow;
        multiplyBig(newBig, newOverflow, primes[index], powers[index] - taken);
        search(index + 1, smallValue, newBig, newOverflow);
        smallValue *= (BigNumber)primes[index];
        taken++;
    }
}

void printNumber(BigNumber number) {
    char digits[50];
    int length = 0;
    if (number == 0) {
        std::cout << "0";
        return;
    }
    while (number > 0) {
        digits[length] = (char)('0' + (int)(number % 10));
        number /= 10;
        length++;
    }
    for (int i = length - 1; i >= 0; i--) {
        std::cout << digits[i];
    }
}

int main() {
    long long h, w, d;
    std::cin >> h >> w >> d;

    factorize(h);
    factorize(w);
    factorize(d);
    productApprox = (long double)h * (long double)w * (long double)d;

    search(0, 1, 1, false);

    printNumber(bestBig);
    std::cout << " ";
    printNumber(bestSmall);
    std::cout << "\n";
    return 0;
}
