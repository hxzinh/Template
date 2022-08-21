#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
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

const int NM = 1e6 + 10;
int n, k;
int parNode = 0, result = 0;
int high[NM], child[NM], pos[NM], par[NM], ans[NM];
char com[NM];
vector<int> edges[NM];
set<int> G[NM];
bool isCen[NM], school[NM];
map<int, int> dis[NM];

void dfs(int u, int p){
    child[u] = school[u];
    for(int v : G[u]) if(v != p && !isCen[v]){
        dfs(v, u);
        child[u] += child[v];
    }
    return;
}
int centroid(int u, int p, int root){
    for(int v : G[u]) if(v != p && !isCen[v]) {
        if(child[v] > k) return centroid(v, u, root);
    }
    return u;
}
void dfs2(int u, int p, int cen, int h){
    dis[cen][u] = h;
    for(int v : G[u]) if(v != p){
        dfs2(v, u, cen, h + 1);
    }
}
void modify(int u){
    for(int v = u; v != 0; v = par[v])
        maximize(ans[v], dis[v][u]);
}
int getDist(int u){
    int res = -INF;
    for(int v = u; v != 0; v = par[v]) maximize(res, ans[v] + dis[v][u]);
    return res;
}
void build(int u, int p){
    dfs(u, u);

    int tmp = centroid(u, u, u);
    isCen[tmp] = true;

    if(!parNode) parNode = tmp;
    par[tmp] = p;
    dfs2(tmp, p, tmp, 0);

    if(p == -1) p = tmp;

    vector<int> newEdges(ALL(G[tmp]));
    for(int v : newEdges) if(!isCen[v]) {
        G[tmp].erase(v); G[v].erase(tmp);
        build(v, tmp);
    }
}
void dfs3(int u, int p, int h){
    if(school[u]) result += h;
    for(int v : edges[u]) if(v != p){
        dfs3(v, u, h + 1);
    }
}
void init(){
    for(int i = 1; i <= n; i++){
        ans[i] = -INF;
        high[i] = 0;
    }
}
int LCA(int u, int v){
    if(high[u] < high[v]) swap(u, v);
    while(high[u] > high[v]) u = par[u];

    while(u != v){
        u = par[u];
        v = par[v];
    }
    return u;
}
void xuli(){
    init();
    build(1, 0);

    high[parNode] = 0;
    dfs3(parNode, 0, -1);

    int cur = pos[1];
    for(int i = 2; i <= 2 * k; i++)
        cur = LCA(cur, pos[i]);

    modify(cur);

    int res = 0;
    for(int i = 1; i <= 2 * k; i++) res += getDist(pos[i]);
    cout << res;
}
void full(){
    init();
    dfs(1, 0);
    int cen = centroid(1, 0, 1);
    dfs3(cen, -1, 0);
    cout << result;
}
int32_t main()
{
    FastIO
    cin >> n >> k;
    for(int i = 1; i <= 2 * k; i++){
        cin >> pos[i];
        school[pos[i]] = true;
    }
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        G[u].insert(v);
        G[v].insert(u);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    full();
    //xuli();
    return 0;
}

/* Author: hxzinh */