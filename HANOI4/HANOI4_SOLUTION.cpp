#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int get(int state, int index) { return (state >> (index * 2)) & 3; }
int set(int state, int index, int value) {
    return state & ~(3 << (index * 2)) | (value << (index * 2));
}
int incr(int x) { return x < 0 ? x - 1 : x + 1; }
int sgn(int x) {
    if (x == 0) return x;
    return x < 0 ? -1 : 1;
}
int cost[1 << 24];

int bidirectional(int initial, int last, int total_disk) {
    if (initial == last) return 0;
    queue<int> q;
    memset(cost, 0, sizeof(cost));
    cost[initial] = 1;
    cost[last] = -1;
    q.push(initial);
    q.push(last);

    while (q.empty() == false) {
        int here = q.front();
        q.pop();

        int top[4] = {-1, -1, -1, -1};
        // 큰거부터 확인 top은 제일 작아야함
        for (int i = total_disk - 1; i >= 0; i--) {
            top[get(here, i)] = i;
        }

        for (int i = 0; i < 4; i++) {
            if (top[i] == -1) continue;
            for (int j = 0; j < 4; j++) {
                if (i != j && (top[j] == -1 || top[j] > top[i])) {
                    int there = set(here, top[i], j);
                    if (cost[there] == 0) {
                        cost[there] = incr(cost[here]);
                        q.push(there);
                    } else if (sgn(cost[here]) != sgn(cost[there])) {
                        return abs(cost[here]) + abs(cost[there]) - 1;
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<int> outputs;

    while (current_case++ < case_count) {
        int total_disk;
        cin >> total_disk;
        int initial = 0;
        for (int i = 0; i < 4; i++) {
            int cnt;
            cin >> cnt;
            for (int j = 0; j < cnt; j++) {
                int disk;
                cin >> disk;
                initial = set(initial, disk - 1, i);
            }
        }
        int last = 0;
        for (int i = 0; i < total_disk; i++) {
            last = set(last, i, 3);
        }
        outputs.push_back(bidirectional(initial, last, total_disk));
    }
    for (int output : outputs) cout << output << '\n';
    return 0;
}
