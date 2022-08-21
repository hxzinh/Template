#include <bits/stdc++.h>
#define oo 20000000000000
#define FASTIO                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = b; i >= a; i--)
#define REP(i, a) for (int i = 0; i < a; i++)
#define MASK(i) (1LL << (i))
#define BIT(i, a) (((a) >> (i)) & 1)
#define fi first
#define se second
using namespace std;

template <class T>
T Abs(const T &x) {
    return (x < 0 ? -x : x);
}
template <class X, class Y>
bool minimize(X &x, const Y &y) {
    X eps = 1e-9;
    if (x > y + eps) {
        x = y;
        return true;
    } else
        return false;
}
template <class X, class Y>
bool maximize(X &x, const Y &y) {
    X eps = 1e-9;
    if (x + eps < y) {
        x = y;
        return true;
    } else
        return false;
}

template <typename T>
inline void Read(T &x) {
    bool Neg = false;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-')
            Neg = !Neg;
    x = c - '0';
    for (c = getchar(); c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    if (Neg)
        x = -x;
}
template <typename T>
inline void Write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T p = 1;
    for (T temp = x / 10; temp > 0; temp /= 10) p *= 10;
    for (; p > 0; x %= p, p /= 10) putchar(x / p + '0');
}

using ii = pair<int, int>;
using ll = long long;
using ld = long double;
const int Nmax = 100100;
int n, a[Nmax], f[Nmax];
struct FenwickTree {
    vector<int> v;
    int n;

    FenwickTree(int n_ = 0) {
        n = n_;
        v.assign(n + 8, -oo);
    }

    void update(int x, int c) {
        maximize(v[x], c);
        for (; x <= n; x += x & -x) maximize(v[x], c);
    }

    int getMax(int x) const {
        int res = 0;
        for (; x >= 1; x &= x - 1) maximize(res, v[x]);
        return res;
    }
};
FenwickTree bits(Nmax);
void readfile() {
    FASTIO
    cin >> n;
    FOR(i, 1, n) {
        cin >> a[i];
        bits.update(i, 0);
    }
    vector<int> values;
    FOR(i, 1, n) values.push_back(a[i]);
    sort(values.begin(), values.end());
    values.resize(unique(values.begin(), values.end()) - values.begin());

    FOR(i, 1, n)
    a[i] = lower_bound(values.begin(), values.end(), a[i]) - values.begin() + 1;

    FOR(i, 1, n) {
        f[i] = bits.getMax(a[i] - 1) + 1;
        bits.update(a[i], f[i]);
    }

    int res = -oo;
    FOR(i, 1, n) maximize(res, f[i]);
    cout << res;
}
int32_t main() {
    readfile();
    return 0;
}