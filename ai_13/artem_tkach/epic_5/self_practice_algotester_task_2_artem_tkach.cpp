// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40426

#include <cstdio>

int main() {
    int n;
    if (std::scanf("%d", &n) != 1) {
        return 0;
    }

    long long prefix = 0;
    long long answer = 0;

    for (int i = 0; i < n; ++i) {
        long long value;
        if (std::scanf("%lld", &value) != 1) {
            return 0;
        }

        prefix += value;
        answer += prefix;
    }

    std::printf("%lld\n", answer);
    return 0;
}