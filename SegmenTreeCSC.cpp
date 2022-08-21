#include <bits/stdc++.h>
#define ll long long
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define oo INFINITY
#define FastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
const int NM = 5e5 + 10;
const long long MOD =  998244353;
///-----------------------------------///
int sub,n,q;
vector<int> a[NM];
int high[NM], sta[NM], fin[NM];
int cnt = 0;
int realHigh[NM];

struct SegmentTree{
    int n;
    vector<ll> sum, lazy, coff;

    SegmentTree(int _n, int c[]){
        n = _n;
        sum.assign(4 * n + 7, 0);
        lazy.assign(4 * n + 7, 0);
        coff.assign(4 * n + 7, 0);
        build(c, 1, 1, n);
        return;
    }

    void build(int c[], int i,int l,int r){
        if(l > r) return;
        if(l == r){
            coff[i] = c[l];
            coff[i] = coff[i] % MOD;
            return;
        }
        int m = (l + r) >> 1;
        build(c, 2 * i, l, m);
        build(c, 2 * i + 1, m + 1, r);
        coff[i] = coff[2 * i] + coff[2 * i + 1];
        coff[i] = coff[i] % MOD;
    }

    void pushDown(int i){
        for(int j = 2 * i; j <= 2 * i + 1; j++){
            lazy[j] += lazy[i];
            lazy[j] = lazy[j] % MOD;
            sum[j] += lazy[i] * coff[j];
            sum[j] = sum[j] % MOD;
        }
        lazy[i] = 0;
    }

    ll getSum(int i,int l,int r,int u,int v){
        if(l > v || r < u || l > r || u > v) return 0;
        if(l >= u && r <= v) return sum[i] % MOD;
        pushDown(i);
        int m = (l + r) >> 1;
        ll sumL = getSum(2 * i, l, m, u, v);
        ll sumR = getSum(2 * i + 1, m + 1, r, u, v);
        return (sumL + sumR) % MOD;
    }

    void update(int i,int l,int r,int u,int v,int d){
        if(l > v || r < u || l > r || u > v) return;
        if(l >= u && r <= v){
            lazy[i] += d;
            lazy[i] = lazy[i] % MOD;
            sum[i] += 1LL * d * coff[i];
            sum[i] = (sum[i] % MOD + MOD) % MOD;
            return;
        }
        pushDown(i);
        int m = (l + r) >> 1;
        update(2 * i, l, m, u, v, d);
        update(2 * i + 1, m + 1, r, u, v, d);
        sum[i] = sum[2 * i] + sum[2 * i + 1];
        sum[i] = (sum[i] % MOD + MOD) % MOD;
    }

    ///LENH RUT GON
    ll getSum(int u,int v){
        return getSum(1, 1, n, u, v);
    }
    void update(int u,int v,int d){
        update(1, 1, n, u, v, d);
    }
};

void readfile(){
    freopen("TALLTREE.INP","r",stdin);
    freopen("TALLTREE.OUT","w",stdout);
    cin >> sub;
    cin >> n;
    for(int i = 2; i <= n; i++){
        int u; cin >> u;
        a[u].push_back(i);
    }
    cin >> q;
}
void dfs(int x){
    sta[x] = ++cnt;
    for(int u : a[x]){
        high[u] = high[x] + 1;
        dfs(u);
    }
    fin[x] = cnt;
}

void xuli(){

    dfs(1);
    high[1] = 0;
    for(int i = 1; i <= n; i++) realHigh[sta[i]] = high[i];
    SegmentTree mul(n, realHigh);
    for(int it = 1; it <= n; it++) realHigh[it] = 1;
    SegmentTree tree(n, realHigh);

    string type;
    int v,k,l;
    while(q--){
        cin >> type;
        if(type == "add"){
            cin >> v >> k >> l;
            k = (k % MOD + MOD) % MOD; l = (l % MOD + MOD) % MOD;
            tree.update(sta[v], fin[v], ((k + 1LL * high[v] * l) % MOD + MOD)    %MOD);
            mul.update(sta[v], fin[v], l);
        }
        if(type == "get"){
            cin >> v;
            ll resTree = tree.getSum(sta[v], sta[v]);
            ll resMul = mul.getSum(sta[v], sta[v]);
            ll res = resTree - resMul;
            cout << (res % MOD + MOD) % MOD << " ";
        }
        if(type == "sum"){
            cin >> v;
            ll resTree = tree.getSum(sta[v], fin[v]);
            ll resMul = mul.getSum(sta[v], fin[v]);
            ll res = resTree - resMul;
            cout << (res % MOD + MOD) % MOD << " ";
        }
    }
}

int32_t main()
{
    FastIO
    readfile();
    xuli();
    return 0;
}