#include <stdio.h>
#include <vector>
using namespace std;

vector<int> a[230997]; //
int parent[230997];    //
int l[230997];
int M[230997][23];
int n;

void dfs(int u) {
    for (int v : a[u])
        if (v != parent[u]) {
            parent[v] = u;
            l[v] = l[u] + 1;
            dfs(v);
        }
}

void make_lca() {
    for (int i = 1; i <= n; i++)
        M[i][0] = parent[i];

    for (int k = 1; k <= 20; k++)
        for (int i = 1; i <= n; i++)
            M[i][k] = M[M[i][k - 1]][k - 1];
}

int lca(int p, int q) {
    // ensure l[p]=l[q]
    for (int i = 20; i >= 0; i--)
        if (l[M[p][i]] >= l[q])
            p = M[p][i];
    for (int i = 20; i >= 0; i--)
        if (l[M[q][i]] >= l[p])
            q = M[q][i];

    if (p == q)
        return p;
    for (int i = 20; i >= 0; i--)
        if (M[p][i] != M[q][i]) {
            p = M[p][i], q = M[q][i];
        }
    return parent[p];
}

main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            a[i].clear();
            parent[i] = 0;
        }
        printf("Case %d:\n", t);

        for (int i = 1; i <= n; i++) {
            int m;
            scanf("%d", &m);
            for (int j = 1; j <= m; j++) {
                int p;
                scanf("%d", &p);
                a[i].push_back(p);
            }
        }

        for (int i = 1; i <= n; i++)
            if (parent[i] == 0) {
                parent[i] = i;
                l[i] = 1;
                dfs(i);
            }
        make_lca();
        int nQuery;
        scanf("%d", &nQuery);
        while (nQuery--) {
            int p, q;
            scanf("%d%d", &p, &q);
            printf("%d\n", lca(p, q));
        }
    }
}