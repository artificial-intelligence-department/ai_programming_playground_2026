// Algotester Lab 5, варіант 1.
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/167973
// Дошка 8x8 зберігається в одному 64-бітному числі: молодший байт - перший рядок,
// молодший біт байта - перший стовпець. Кожне заклинання (R, C) змінює стан усіх куль
// у рядку R і стовпці C (вибрана куля змінюється один раз).

#include <cstdio>

const int BOARD_SIZE = 8;

unsigned long long castSpell(unsigned long long board, int row, int column) {
    const unsigned long long rowMask = 0xFFULL << (BOARD_SIZE * row);
    const unsigned long long columnMask = 0x0101010101010101ULL << column;
    return board ^ (rowMask | columnMask);
}

int main() {
    unsigned long long board;
    int spellCount;
    int readCount = std::scanf("%llu %d", &board, &spellCount);
    if (readCount != 2) {
        return 0;
    }

    for (int i = 0; i < spellCount; ++i) {
        int row, column;
        readCount = std::scanf("%d %d", &row, &column);
        if (readCount != 2) {
            return 0;
        }
        board = castSpell(board, row - 1, column - 1);
    }

    std::printf("%llu\n", board);
    return 0;
}
