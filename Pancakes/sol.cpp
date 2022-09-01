#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, ll> pii;

#define pb push_back

#define f first
#define s second

const int maxn = 400005;

int cost[maxn], init[maxn];
pii dp[maxn][2];
vector<int> adj[maxn];

//Select best cost: we wish to maximize ones, then minimize the cost
pii best(pii a, pii b){
    if(a.f == b.f){
        return (a.s < b.s ? a : b);
    }
    return (a.f < b.f ? b : a);
}

pii dfs(int u, int p = -1, int mode = 0){
    if(dp[u][mode] != pii(-1, -1)) return dp[u][mode];
    pii flip(init[u] ^ mode ^ 1, cost[u]);
    pii noflip(init[u] ^ mode, 0);
    for(int n : adj[u]){
        if(n == p) continue;
        pii flipped = dfs(n, u, mode ^ 1);
        pii noflipped = dfs(n, u, mode);
        flip.f += flipped.f; flip.s += flipped.s;
        noflip.f += noflipped.f; noflip.s += noflipped.s;
    }
    if(cost[u] == -1){ //are we able to flip this node?
        dp[u][mode] = noflip;
    }else{
        dp[u][mode] = best(flip, noflip);
    }
    return dp[u][mode];
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    string str; cin >> str; //indicating the intial bit values
    for(int i = 0; i<N; i++){
        init[i] = str[i] == '1';
        dp[i][0] = dp[i][1] = pii(-1, -1); //this is a marker that the dp state hasn't been visited
        cin >> cost[i]; //indicating the cost to flip, -1 means no switch
    }

    for(int i = 0; i<N-1; i++){
        int u, v; cin >> u >> v; --u, --v;
        adj[u].pb(v); adj[v].pb(u);
    }

    pii ret = dfs(0);
    cout << ret.f << " " << ret.s << '\n';
    return 0;
}