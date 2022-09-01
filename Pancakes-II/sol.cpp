#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
#define pb push_back
 
#define f first
#define s second
 
const int maxn = 2e5 + 3;

vector<int> adj[maxn];
vector<int> full[maxn], half[maxn];
//dp_full and dp_half

int csz[maxn], blocked[maxn], par[maxn], dep[maxn], bit[maxn];
//csz, blocked are subroutines of CD
//dep and par are used to find CD tree ancestor between two nodes a and b
//bit stores the given bit values of each node
 
//DFS computes the DP Values in O(size)
//mode 0 - full, mode 1 - half
void calc(int u, int mode, int last = 0, int lastval = 0, int p = 0){
    int val = lastval;
    if(last == 0 && bit[u]) val++;
 
    if(mode) {
        half[u].pb(val);
    }else{
        full[u].pb(val);
    }    
 
    for(int n : adj[u]){
        if(!blocked[n] && n != p) {
            calc(n, mode, bit[u], val, u);
        }
    }
}
 
//finds the size of current group/component, needed for CD
int initsz(int u, int p = 0){ 
    csz[u] = 1;
    for(int n : adj[u]){
        if(!blocked[n] && n != p) csz[u] += initsz(n, u);
    }
    return csz[u];
}
 
//intialize the CD tree
int init(int u, int compsz, int p = 0, int d = 0){
    for(int n : adj[u]){
        if(n != p && !blocked[n] && csz[n] > compsz/2){
            return init(n, compsz, u, d);
        }
    }
 
    blocked[u] = 1;
    dep[u] = d;
 
    calc(u, 0);
    for(int n : adj[u]){
        if(!blocked[n]){
            calc(n, 1, bit[u]);
        }
    }
 
    for(int n : adj[u]){
        if(!blocked[n]){
            initsz(n); 
            int temp = init(n, csz[n], u, d+1);
            par[temp] = u;
        }
    }
    blocked[u] = 0;
    return u;
}
 
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    string str; cin >> str;
    for(int i = 1; i<=N; i++) bit[i] = str[i-1] == '1';
    for(int i = 0; i<N-1; i++){
        int u, v; cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    
    //Intialize CD tree and compute DP values
    initsz(1);
    init(1, csz[1]);
 
    int Q; cin >> Q;
    while(Q--){
        int u, v; cin >> u >> v;
        //Find ancestor in CD Tree
        int pu = u, pv = v;
        while(dep[pu] > dep[pv]) pu = par[pu];
        while(dep[pv] > dep[pu]) pv = par[pv];
        while(pu != pv) pu = par[pu], pv = par[pv];
 
        //Casework (not too bad thanks to dp_half)
        int ret = full[u][dep[pu]];
        if(dep[pv] < half[v].size()){
            ret += half[v][dep[pv]];
        }
        cout << ret << '\n';
    }
    return 0;
}