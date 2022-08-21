#include bitsstdc++.h
#define int long long
#define INF 0x3f3f3f3f
#define pii pairint, int
#define fi first
#define se second
#define ALL(v) (v).begin(), (v).end()
#define popcount(x) __builtin_popcount(x)
#define set(x) setprecision(x)
#define MASK(x) (1LL  (x))
#define BIT(x, i) ((x)  (i) & 1)
#define FastIO ios_basesync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

templateclass X, class Y
	inline bool maximize(X &x, const Y &y) {return (x  y  x = y, 1  0);}
templateclass X, class Y
	inline bool minimize(X &x, const Y &y) {return (x  y  x = y, 1  0);}

const int NM = 1e3 + 10;
int n, k, T;
string s;
int cntBit = 0;
int a[NM];
int f[NM];

int Mex(vectorint U){
    int res = 0;
    sort(ALL(U));
    for(int x  U) if(x == res) res++;
    return res;
}
int getVal(int u){
    if(f[u] > -1) return f[u];

    int res = 0;
    vectorint U;
    for(int i = 1; i + k - 1 = u; i++){
        int v = i + k - 1;
        int x = 0, y = 0;
        if(i - 1 = k) x = getVal(i - 1);
        if(u - v = k) y = getVal(u - v);
        U.push_back(x ^ y);
    }

    res = Mex(U);
    f[u] = res;
    return res;
}
bool isFirstWin(){
    int res = 0;
    for(int i = 1; i = cntBit; i++){
        res ^= f[a[i]];
        cout  res   ;
    }
    return (res  0);
}
int32_t main()
{
    FastIO
    freopen(QTBIT.INP, r, stdin);
    freopen(QTBIT.OUT, w, stdout);
    cin  T;
    while(T--){
        cin  k  s;
        n = s.size();
        s = '#' + s;

        int u = 1;
        cntBit = 0;
        while(u = n){
            if(s[u] == '1'){
                a[++cntBit] = 0;
                while(s[u] == '1'){
                    a[cntBit]++;
                    u++;
                }
            }
            u++;
        }

        memset(f, -1, sizeof f);
        for(int i = 1; i = cntBit; i++) getVal(a[i]);
        cout  (isFirstWin()  1  2)  'n';
    }
    return 0;
}
