#include <iostream>

int main() {
    std::cout << std::fixed;

    // Варіант 25: a = 1000, b = 0.0001.
    {
        float a = 1000.0f;
        float b = 0.0001f;
        float difference = a - b;
        float difference2 = difference * difference;
        float difference3 = difference2 * difference;
        float a2 = a * a;
        float a3 = a2 * a;
        float term = 3.0f * a2 * b;
        float subtrahend = a3 - term;
        float numerator = difference3 - subtrahend;
        float b2 = b * b;
        float b3 = b2 * b;
        float denominatorTerm = 3.0f * a * b2;
        float denominator = b3 - denominatorTerm;
        float result = numerator / denominator;

        std::cout << "float\n";
        std::cout << "(a-b)^3 = " << difference3 << '\n';
        std::cout << "a^3-3*a^2*b = " << subtrahend << '\n';
        std::cout << "Чисельник = " << numerator << '\n';
        std::cout << "Знаменник = " << denominator << '\n';
        std::cout << "Результат = " << result << "\n\n";
    }

    {
        double a = 1000.0;
        double b = 0.0001;
        double difference = a - b;
        double difference2 = difference * difference;
        double difference3 = difference2 * difference;
        double a2 = a * a;
        double a3 = a2 * a;
        double term = 3.0 * a2 * b;
        double subtrahend = a3 - term;
        double numerator = difference3 - subtrahend;
        double b2 = b * b;
        double b3 = b2 * b;
        double denominatorTerm = 3.0 * a * b2;
        double denominator = b3 - denominatorTerm;
        double result = numerator / denominator;

        std::cout << "double\n";
        std::cout << "(a-b)^3 = " << difference3 << '\n';
        std::cout << "a^3-3*a^2*b = " << subtrahend << '\n';
        std::cout << "Чисельник = " << numerator << '\n';
        std::cout << "Знаменник = " << denominator << '\n';
        std::cout << "Результат = " << result << '\n';
    }

    return 0;
}
