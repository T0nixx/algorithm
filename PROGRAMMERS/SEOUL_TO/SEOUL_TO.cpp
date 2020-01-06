
// TILE.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int cache[100001][101];

const int INF = 987654321;
int solve(int here, int time_left, vector<vector<int>>& travel) {
    if (time_left < 0) return -INF;
    int& ret = cache[time_left][here];
    if (ret != -1) return ret;
    if (here == travel.size()) {
        return 0;
    }

    int walk_time = travel[here][0];
    int walk_money = travel[here][1];
    int bike_time = travel[here][2];
    int bike_money = travel[here][3];

    return ret =
               max(solve(here + 1, time_left - bike_time, travel) + bike_money,
                   solve(here + 1, time_left - walk_time, travel) + walk_money);
}

int solution(int K, vector<vector<int>> travel) {
    int answer = 0;
    memset(cache, -1, sizeof(cache));
    return solve(0, K, travel);
}

int main() {
    vector<vector<int>> travel = {{1000, 2000, 300, 700},
                                  {1100, 1900, 400, 900},
                                  {900, 1800, 400, 700},
                                  {1200, 2300, 500, 1200}};
    cout << solution(3000, travel);

    return 0;
}
