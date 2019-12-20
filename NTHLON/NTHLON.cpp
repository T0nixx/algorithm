#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int INF = 987654321;

void init(const vector<int>& A, const vector<int>& B) {}
int M;

vector<pair<int, int>> get_next(int cur_diff, vector<pair<int, int>>& pluses,
                                vector<pair<int, int>>& minuses) {
    vector<pair<int, int>> ret;
    if (cur_diff >= 0) {
        for (int i = 0; i < minuses.size(); i++) {
            ret.push_back(
                make_pair(cur_diff + minuses[i].first, minuses[i].second));
        }
    }
    if (cur_diff <= 0) {
        for (int i = 0; i < pluses.size(); i++) {
            ret.push_back(
                make_pair(cur_diff + pluses[i].first, pluses[i].second));
        }
    }
    return ret;
}

int get_index(int x) { return x < 0 ? x * -1 + 200 : x; }

int dijkstra(int src, vector<pair<int, int>>& pluses,
             vector<pair<int, int>>& minuses) {
    priority_queue<pair<int, int>> pq;
    vector<int> minutes(401, INF);

    pq.push(make_pair(0, src));

    vector<vector<pair<int, int>>> adj(401);

    while (pq.empty() == false) {
        int minute = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        int here_index = get_index(here);
        adj[here_index] = get_next(here, pluses, minuses);

        for (int i = 0; i < adj[here_index].size(); i++) {
            int there = adj[here_index][i].first;
            int there_index = get_index(there);
            int next_minute = adj[here_index][i].second + minute;
            if (next_minute < minutes[there_index]) {
                pq.push(make_pair(-next_minute, there));
                minutes[there_index] = next_minute;
            }
        }
    }
    return minutes[0];
}

int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<int> outputs;

    while (current_case++ < case_count) {
        cin >> M;
        vector<pair<int, int>> diff_and_minutes(M);
        vector<pair<int, int>> pluses;
        vector<pair<int, int>> minuses;
        int time_A, time_B;
        for (int i = 0; i < M; i++) {
            cin >> time_A;
            cin >> time_B;
            int diff = time_B - time_A;
            if (diff < 0)
                minuses.push_back(make_pair(diff, time_B));
            else
                pluses.push_back(make_pair(diff, time_B));
        }
        outputs.push_back(dijkstra(0, pluses, minuses));
    }
    for (int output : outputs) {
        if (output == INF)
            cout << "IMPOSSIBLE" << '\n';
        else
            cout << output << '\n';
    }
    return 0;
}
