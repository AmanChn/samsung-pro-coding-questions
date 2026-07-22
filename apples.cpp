/*
🍎 Apple Game - Right Turn Only

Mr. Sam-Sung Na purchased a newly released game.

This game is played on an N x N map. The goal of the game is to eat the apples in order.

Rules:
- Apples appear on the map according to their number, starting from 1.
- Apple 2 appears only after Apple 1 is eaten, Apple 3 after Apple 2, and so on.
- You cannot eat an apple out of order.
- You cannot move into cells marked as traps (-1 on the map).

Movement:
- The player starts at the top-left corner of the map (0, 0).
- The player initially moves to the right (→).
- The player continues to move in the current direction unless:
    - They hit a wall
    - They hit a trap
    - They make a right turn
- Due to a keyboard malfunction, the player can only make right turns.
- Left turns and backward movement are not possible.

Goal:
- Eat all apples in order while making the minimum number of right turns.
- If it's impossible to eat all the apples in order, return -1.

Input:
- First line: T, number of test cases.
- For each test case:
  - First line: N (size of the map)
  - Next N lines: N integers each representing the map
    - 0: empty cell
    - -1: trap
    - Positive integers: apple numbers (1 to M)

Output:
- For each test case, print "#t ans"
  - t = test case number starting from 1
  - ans = minimum number of right turns needed to eat all apples
  - If impossible, print -1

Constraints:
- 5 ≤ N < 60
- 2 ≤ M ≤ 150

*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct State {
    int x, y, dir, nxt;
};

// direction must be stored in clockwise direction
// idx 0:right, 1:down, 2:left, 3:up 
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {

        int N;
        cin >> N;

        vector<vector<int>> grid(N, vector<int>(N));

        int M = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> grid[i][j];
                if (grid[i][j] > 0)
                    M = max(M, grid[i][j]); // max apple number
            }
        }

        int startApple = 1;

        if (grid[0][0] == 1)
            startApple = 2;

        // dist[x][y][dir][nextApple]
        vector<vector<vector<vector<int>>>> dist
            (N,vector<vector<vector<int>>>(N,vector<vector<int>>(4,vector<int>(M + 2, INF))));

        deque<State> dq;

        dist[0][0][0][startApple] = 0;
        dq.push_front({0, 0, 0, startApple});

        int ans = -1;

        while (!dq.empty()) {

            State cur = dq.front();
            dq.pop_front();

            int d = dist[cur.x][cur.y][cur.dir][cur.nxt];

            if (cur.nxt == M + 1) {
                ans = d;
                break;
            }

            // Move Forward (cost = 0)
            int nx = cur.x + dx[cur.dir];
            int ny = cur.y + dy[cur.dir];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != -1) {
                int nnxt = cur.nxt;

                if (grid[nx][ny] == cur.nxt)
                    nnxt++;

                if (dist[nx][ny][cur.dir][nnxt] > d) {
                    dist[nx][ny][cur.dir][nnxt] = d;
                    dq.push_front({nx, ny, cur.dir, nnxt});
                }
            }

            // Right Turn (cost = 1)
            int ndir = (cur.dir + 1) % 4;

            if (dist[cur.x][cur.y][ndir][cur.nxt] > d + 1) {
                dist[cur.x][cur.y][ndir][cur.nxt] = d + 1;
                dq.push_back({cur.x, cur.y, ndir, cur.nxt});
            }
        }

        cout << "#" << tc << " " << ans << "\n";
    }

    return 0;
}
