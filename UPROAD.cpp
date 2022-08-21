#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f
#define ALL(v) (v).begin(), (v).end()
#define pii pair<int, int>
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

const int NM = 150005;
int n, m, T;
double mid;
vector<int> trace;

struct Data {
    int u, v, id;
    double cost, prof;
};
Data a[NM];

struct DijointSet {
    int n;
    vector<int> par;

    DijointSet(int _n = 0){
        n = _n;
        par.assign(n + 7, -1);
    }

    int root(int x){
        if(par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }

    void join(int u, int v){
        u = root(u); v = root(v);
        if(u == v) return;
        if(par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }
};

bool cmp(const Data &A, const Data &B){
    return (A.prof - A.cost * mid) > (B.prof - B.cost * mid);
}
bool check(double x){
    sort(a + 1, a + m + 1, cmp);

    trace.clear();
    DijointSet dsu(n);

    double res = 0, sumCost = 0, sumProf = 0;
    for(int i = 1; i <= m; i++){
        int u = a[i].u, v = a[i].v, id = a[i].id;
        double c = a[i].cost, g = a[i].prof;

        if(dsu.root(u) != dsu.root(v)){
            sumCost += c, sumProf += g;
            dsu.join(u, v);
            trace.push_back(id);
            continue;
        }

        int newG = sumProf + g, newC = sumCost + c;
        if(sumProf - sumCost * x < newG - newC * x){
            sumCost = newC; sumProf = newG;
            trace.push_back(id);
        }
    }
    res = sumProf - double(sumCost * x);
    return (res >= 0.00);
}
void xuli(){
    vector<int> ans;
    double l = 0, r = 1e9;
    for(int k = 0; k < 70; k++){
        mid = (l + r) / 2.00;
        if(check(mid)){
            l = mid;
            ans.clear();
            ans.insert(ans.begin(), ALL(trace));
        } else r = mid;
    }
    double res = (l + r) / 2.00;
    cout << fixed << setprecision(9) << res << '\n';
    cout << ans.size() << '\n';
    for(int u : ans) cout << u << " ";
}
int32_t main()
{
    FastIO
    freopen("UPROAD.INP", "r", stdin);
    freopen("UPROAD.OUT", "w", stdout);
    cin >> T;
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v, cost, prof;
        cin >> u >> v >> cost >> prof;
        a[i] = {u, v, i, cost, prof};
    }

    xuli();
    return 0;
}
