#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;

#define pb push_back

#define f first
#define s second

const int maxn = 2e5 + 10;
map<int, vector<int>> adj[maxn];
set<pii> state_vis;
int node_vis[maxn];

void dfs(int A, int B){
    if(state_vis.count(pii(A, B))){
        return;
    }
    state_vis.insert(pii(A, B));
    node_vis[A] = 1; node_vis[B] = 1;
    for(int n : adj[A][B]){
        //Where A can move to given that B stays
        dfs(n, B);
    }
    for(int n : adj[B][A]){
        //Where B can move to given that A stays
        dfs(B, n);
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, M, A, B; cin >> N >> M >> A >> B;
    for(int i = 0; i<M; i++){
        int u, v, other; cin >> u >> v >> other;
        adj[u][other].pb(v);
        adj[v][other].pb(u);
    }
    dfs(A, B);
    int tot = 0;
    for(int i = 1; i<=N; i++){
        tot += node_vis[i];
    }
    cout << tot << '\n';
    return 0;
}