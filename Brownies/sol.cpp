#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;

#define pb push_back

#define f first
#define s second

int rDir[4] = {1, -1, 0, 0}, cDir[4] = {0, 0, 1, -1};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int N, M, hasZero = 0; cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M)), res(N, vector<int>(M));
    queue<array<int, 3>> bfs;
    for(int i = 0; i<N; i++){
        string str; cin >> str;
        for(int j = 0; j<M; j++){
            grid[i][j] = str[j] == 'X';
            if(!grid[i][j]) hasZero = 1, bfs.push({i, j, 1});
        }
    }
    //edge case if every cell is X -- one of the elements must be 0
    if(!hasZero){
        for(int i = 0; i<N; i++){
            for(int j = 0; j<M; j++){
                int farthestRow = max(i, N - 1 - i);
                int farthestCol = max(j, M - 1 - j);
                cout << (farthestRow + farthestCol + 1) << " ";
            }
            cout << '\n';
        }
        return 0;
    }

    while(!bfs.empty()){
        array<int, 3> cur = bfs.front(); bfs.pop();
        if(res[cur[0]][cur[1]] != 0) continue;
        res[cur[0]][cur[1]] = cur[2];
        for(int i = 0; i < 4; i++){
            int dR = cur[0] + rDir[i], dC = cur[1] + cDir[i];
            if(dR >= 0 && dC >= 0 && dR < N && dC < M){
                bfs.push({dR, dC, cur[2] + 1});
            }
        }
    }

    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            cout << res[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}