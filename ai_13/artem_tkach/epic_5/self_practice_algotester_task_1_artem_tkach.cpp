// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40856

#include <cstdio>

int findRoot(int city, int *parent) {
    while (city != parent[city]) {
        parent[city] = parent[parent[city]];
        city = parent[city];
    }
    return city;
}

int main() {
    int n, m;
    if (std::scanf("%d %d", &n, &m) != 2) return 0;

    int *parent = new int[n + 1];
    int *size = new int[n + 1];
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        size[i] = 1;
    }

    int components = n;
    for (int i = 0; i < m; ++i) {
        int a, b;
        if (std::scanf("%d %d", &a, &b) != 2) {
            delete[] parent;
            delete[] size;
            return 0;
        }
        a = findRoot(a, parent);
        b = findRoot(b, parent);

        if (a != b) {
            if (size[a] < size[b]) {
                int temp = a;
                a = b;
                b = temp;
            }
            parent[b] = a;
            size[a] += size[b];
            --components;
        }
        std::printf("%d\n", components);
    }

    delete[] parent;
    delete[] size;
    return 0;
}
