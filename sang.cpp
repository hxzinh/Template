#include <bits/stdc++.h>
#define ll long long
#define FastIO

using namespace std;
const int NM=1e9+5;
ll n;

void xuli(ll L,ll R)
{
    ll dem=0;
    vector <bool> prime(R-L+1,true);
    for(ll i=2;i*i<=R;i++)
    {
        for(ll j=max(i*i,(L+i-1)/i*i);j<=R;j+=i)
        {
            prime[j-L]=false;
        }
    }
    if(1>=L) prime[1-L]=false;
    for(ll i=L;i<=R;i++)
    {
        if(prime[i-L]==true)
        {
            ///cout << i << '\n';
            dem++;
        }
    }
    cout << dem;
}
void readfile()
{
    freopen("PRIMECOUNT.INP","r",stdin);
    freopen("PRIMECOUNT.OUT","w",stdout);
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        ll u,v;
        cin >> u >> v;
        xuli(u,v);
        cout << '\n';
    }
}
int main()
{
    readfile();
    return 0;
}