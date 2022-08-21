#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
#define ALL(v) (v).begin(), (v).end()
#define popcount(x) __builtin_popcount(x)
#define setp(x) setprecision(x)
#define MASK(x) (1LL << (x))
#define BIT(x, i) ((x) >> (i) & 1)
#define FastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

template<class X, class Y>
	inline bool maximize(X &x, const Y &y) {return (x < y ? x = y, 1 : 0);}
template<class X, class Y>
	inline bool minimize(X &x, const Y &y) {return (x > y ? x = y, 1 : 0);}

const int NM = 1e3 + 10;
int n, m, q;
int a[NM][NM];

struct FenwickTree {
    int n;
    vector<vector<int>> val[4];

    FenwickTree(int _n = 0){
        n = _n;
        val[0].assign(n + 7, vector<int>(n + 7, 0));
        val[1].assign(n + 7, vector<int>(n + 7, 0));
        val[2].assign(n + 7, vector<int>(n + 7, 0));
        val[3].assign(n + 7, vector<int>(n + 7, 0));
    }

    void update(int x, int y, int w){
        for(int i = x; i <= n; i += i & -i)
            for(int j = y; j <= n; j += j & -j){
                val[0][i][j] += w;
                val[1][i][j] += x * w;
                val[2][i][j] += y * w;
                val[3][i][j] += x * y * w;
            }
    }

    void updateMatrix(int x, int y, int u, int v, int w){
        update(x, y, w);
        update(x, v + 1, -w);
        update(u + 1, y, -w);
        update(u + 1, v + 1, w);
    }

    int queryPoint(int x, int y){
        int res = 0;
        for(int i = x; i > 0; i -= i & -i)
            for(int j = y; j > 0; j -= j & -j)
                res += (x + 1) * (y + 1) * val[0][i][j] - (y + 1) * val[1][i][j] - (x + 1) * val[2][i][j] + val[3][i][j];
        return res;
    }

    int queryMatrix(int x, int y, int u, int v){
        return queryPoint(u, v) - queryPoint(x - 1, v) - queryPoint(u, y - 1) + queryPoint(x - 1, y - 1);
    }
};

void full(){
    FenwickTree tree(m);

    while(q--){
        int type, x, y, u, v, w;
        cin >> type >> x >> y >> u >> v;
        if(type == 1){
            cin >> w;
            tree.updateMatrix(x, y, u, v, w);
        } else cout << tree.queryMatrix(x, y, u, v) << '\n';
    }
}
int32_t main()
{
    FastIO
    freopen("CNT.INP", "r", stdin);
    freopen("CNT.OUT", "w", stdout);
    cin >> n >> m >> q;

    full();
    return 0;
}

/* Author: hxzinh */
