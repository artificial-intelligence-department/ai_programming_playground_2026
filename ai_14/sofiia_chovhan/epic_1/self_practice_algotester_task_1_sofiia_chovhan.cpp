/*Hot Days of Penguins
Sofiia Chovhan AI 14
You can’t even imagine how hot it is on the Madagascar. To cool themselves just a little bit down penguins decided to drink some non-alcoholic 
cocktails but even that is a problem – their hands aren’t used to activities like that. Your task is to find out whether the penguins can drink a cocktail on a table.
For the sake of simplicity we’ll consider a cocktail on a table as a circle of diameter 𝐿 and a penguin’s mouth at any moment of time as a rectangle 
𝑊 inches wide rectangle. The sides of the rectangle are parallel to the axes. In the beginning the penguin’s mouth is closed so the rectangle is degenerate - it’s just a horizontal segment 𝑊 inches long segment. The upper jaw of the penguin can move at most 𝑈 inches up while the bottom one - at most 𝐷 inches down.
The penguin is considered to be able to drink the cocktail if the circle can be completely placed inside the penguin’s rectangular 
mouth. Help the penguin to find if he can drink the cocktail.
*/

#include <iostream>

int main() {
    int L, W, U, D;

    std::cin >> L >> W >> U >> D;

    if (L > 109 || W > 109 || U > 109 || D > 109) {
        return 1;
    }

    if (L <= U + D && L <= W) {
        std::cout << "Three times Sex on the Beach, please!";
    }
    else {
        std::cout << "Forget about the cocktails, man!";
    }

    return 0;
}