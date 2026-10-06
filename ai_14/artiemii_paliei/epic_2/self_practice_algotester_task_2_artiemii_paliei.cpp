// Музикант мобільний

#include <iostream>

int main()
{
    int n, price;

    const int TARIFF = 11;
    const int SEVEN_MINS = 7;
    const int TARIFF_7MINS = 9;
    const int TARRIF_MORE7 = 5;
    const int SECS_IN_MIN = 60;

    std::cin >> n;

    int mins = n / SECS_IN_MIN;
    if (n % SECS_IN_MIN > 0)
        mins++;

    if (mins <= SEVEN_MINS)
        price = TARIFF + mins * TARIFF_7MINS;
    else
        price = TARIFF + (mins - SEVEN_MINS) * TARRIF_MORE7 + SEVEN_MINS * TARIFF_7MINS;

    std::cout << price;

    return 0;
}