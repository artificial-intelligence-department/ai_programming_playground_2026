// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40484

#include <cstdio>
#include <cstring>

const int STATE_COUNT = 362880; // 9! permutations
const int factorial[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
char states[STATE_COUNT][10];
int distanceTo[STATE_COUNT];

int getIndex(const char *state) {
    int index = 0;
    for (int i = 0; i < 9; ++i) {
        int smaller = 0;
        for (int j = i + 1; j < 9; ++j) {
            if (state[j] < state[i]) ++smaller;
        }
        index += smaller * factorial[8 - i];
    }
    return index;
}

int main() {
    char row[4];
    for (int i = 0; i < 3; ++i) {
        if (std::scanf("%3s", row) != 1) return 0;
        for (int j = 0; j < 3; ++j) states[0][3 * i + j] = row[j];
    }
    states[0][9] = '\0';

    for (int i = 0; i < STATE_COUNT; ++i) distanceTo[i] = -1;
    distanceTo[getIndex(states[0])] = 0;

    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    int head = 0, tail = 1;

    while (head < tail) {
        char current[10];
        std::strcpy(current, states[head++]);
        int distance = distanceTo[getIndex(current)];
        if (std::strcmp(current, "123456780") == 0) {
            std::printf("%d\n", distance);
            return 0;
        }

        int empty = 0;
        while (current[empty] != '0') ++empty;

        for (int direction = 0; direction < 4; ++direction) {
            int x = empty / 3 + dx[direction];
            int y = empty % 3 + dy[direction];
            if (x < 0 || x >= 3 || y < 0 || y >= 3) continue;

            int next = x * 3 + y;
            current[empty] = current[next];
            current[next] = '0';

            int index = getIndex(current);
            if (distanceTo[index] == -1) {
                distanceTo[index] = distance + 1;
                std::strcpy(states[tail++], current);
            }

            current[next] = current[empty];
            current[empty] = '0';
        }
    }

    std::printf("-1\n");
    return 0;
}
