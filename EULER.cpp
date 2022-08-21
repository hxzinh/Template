#include <bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
#define pii pair<int, int>
#define mp make_pair
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

const int NM = 2e5 + 10;
int n, m;
int deg[NM];
bool used[NM];
vector<pii> edges[NM], ans;

bool check() {
    if(edges[1].size() != deg[1] + 1 || edges[n].size() != deg[n] - 1) return false;
    for(int i = 2; i < n; i++) {
        if(edges[i].size() != deg[i]) return false;
    }
    return true;
}
list<int> Euler(int u) {
    list<int> ans;
    ans.push_back(u);

    while(edges[u].size()) {
        int v = edges[u].back().fi;
        int id = edges[u].back().se;

        edges[u].pop_back();
        if(used[id]) continue;
        used[id] = true;

        u = v;
        ans.push_back(u);
    }

    for(auto it = ++ans.begin(); it != ans.end(); ++it) {
        auto t = Euler(*it);
        t.pop_back();
        ans.splice(it, t);
    }

    return ans;
}
void xuli() {
    if(!check()) {
        cout << "IMPOSSIBLE";
        return;
    }

    edges[n].push_back(mp(1, m));

    list<int> ans = Euler(1);

    if(ans.size() < m + 1) cout << "IMPOSSIBLE";
    else {
        for(auto u1 = ans.begin(), u2 = ++ans.begin(); u2 != ans.end(); u1++, u2++) {
            if(*u1 == n && *u2 == 1) {
                for(auto i = u2; i != ans.end(); i++) cout << *i << " ";
                for(auto i = ++ans.begin(); i != u2; i++) cout << *i << " ";
                break;
            }
        }
    }

    return;
}
int32_t main()
{
    FastIO
    freopen("EULER.INP", "r", stdin);
    freopen("TELEPATH.OUT", "w", stdout);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        edges[u].push_back(mp(v, i));
        //edges[v].push_back(mp(v, i));
        //deg[u]++;
        deg[v]++;
    }

    xuli();
    return 0;
}

/* Author: hxzinh */

/*
-----code ko bug-----code ko bug-----code ko bug--------------

          _.-/`)
         // / / )
      .=// / / / )
     //`/ / / / /
    // /     ` /
   ||         /
    \\       /
     ))    .'
    //    /
         /
*/
