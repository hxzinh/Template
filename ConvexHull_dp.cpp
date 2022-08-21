#include <bits/stdc++.h>
#define ll long long
#define db double
#define INF 0x3f3f3f3f3f3f3f3f
#define ALL(v) (v).begin(), (v).end()
#define pii pair<int, int>
#define pil pair<int, long long>
#define fi first
#define se second
#define MASK(x) (1LL << (x))
#define BIT(i, x) ((x) >> (i) & 1)
#define FastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

template<class X, class Y>
	inline bool maximize(X &x, const Y &y) {return (x < y ? x = y, 1 : 0);}
template<class X, class Y>
	inline bool minimize(X &x, const Y &y) {return (x > y ? x = y, 1 : 0);}

const int NM = 1e6 + 10;
int n;
long long top = 0;
long long a[NM], f[NM];
pair<long long, long long> lines[NM];

int getRand(int l, int r){
    return rand() % (r - l + 1) + l;
}
long long eval(pil line, long long x) {
    return line.fi * x + line.se;
}
bool bad(pil a, pil b, pil c){
    return (double)(b.se - a.se) / (a.fi - b.fi) >= (double)(c.se - a.se) / (a.fi - c.fi);
}
long long getMin(long long coord) {
    int l = 0, r = top - 1;
    long long ans = eval(lines[l], coord);
    while (l < r) {
        int mid = l + r >> 1;
        long long x = eval(lines[mid], coord);
        long long y = eval(lines[mid + 1], coord);
        if (x > y) l = mid + 1; else r = mid;
        ans = min(ans, min(x, y));
    }
    return ans;
}

bool insertLine(pil newLine) {
    int l = 1, r = top - 1, k = top;
    while (l <= r) {
        int mid = l + r >> 1;
        if (bad(lines[mid - 1], lines[mid], newLine)) {
            k = mid; r = mid - 1;
        }
        else l = mid + 1;
    }
    top = k + 1;
    lines[k] = newLine;
    return 1;
}
void sub6(){
    insertLine(make_pair(0, 0));
    long long Maxx = 0;
    for(int i = 1; i <= n; i++){
        maximize(Maxx, a[i]);
        f[i] = getMin(Maxx) + Maxx * n;
        insertLine(make_pair(-i, f[i]));
    }
    cout << f[n];
}
int32_t main()
{
    FastIO
    freopen("DISCHARG.INP", "r", stdin);
    freopen("DISCHARG.OUT", "w", stdout);
    cin >> n;
    bool cx = true, ok = true;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sub6();
    //for(int i = 1; i <= n; i++) cout << getRand(500000, 1000000) << " ";
    return 0;
}
