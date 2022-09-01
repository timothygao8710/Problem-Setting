#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;

#define pb push_back

#define f first
#define s second

const int maxn = 1005;
int matrix[maxn][maxn];
int dp[maxn][maxn];
int triangle[maxn];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int N, M; cin >> N >> M;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            cin >> matrix[i][j];
        }
    }

    //dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(matrix[i][j] == 0) continue;
            dp[i][j] = min(
                i == 0 ? 0 : matrix[i-1][j],    
                j == 0 ? 0 : matrix[i][j-1]
            );  
            dp[i][j]++;
            triangle[dp[i][j]]++;
        }
    }
    
    //suffix sums
    for(int i = max(N, M)-1; i>=0; i--){
        triangle[i] += triangle[i+1];
    }
    
    int Q; cin >> Q;
    while(Q--){
        int x; cin >> x;
        cout << triangle[x] << '\n';
    }

    return 0;
}