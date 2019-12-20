#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int V;
int E;
int INF = 987654321;
using namespace std;

vector<vector<pair<int, int>>> adj;

vector<int> dijkstra(int src) {
    vector<int> dist(V + 1, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, src));

    while (pq.empty() == false) {
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].second;
            int next_dist = cost + adj[here][i].first;

            if (next_dist < dist[there]) {
                dist[there] = next_dist;
                pq.push(make_pair(-next_dist, there));
            }
        }
    }
    return dist;
}

int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<int> outputs;

    while (current_case++ < case_count) {
        cin >> V;
        cin >> E;
        int fire_scene_cnt;
        cin >> fire_scene_cnt;
        int fire_station_cnt;
        cin >> fire_station_cnt;

        adj = vector<vector<pair<int, int>>>(V + 1);
        for (int i = 0; i < E; i++) {
            int scene1, scene2;
            cin >> scene1;
            cin >> scene2;
            int cost;
            cin >> cost;
            adj[scene1].push_back(make_pair(cost, scene2));
            adj[scene2].push_back(make_pair(cost, scene1));
        }
        vector<int> fire_scenes(fire_scene_cnt);
        for (int i = 0; i < fire_scene_cnt; i++) cin >> fire_scenes[i];
        vector<int> fire_stations(fire_station_cnt);
        for (int i = 0; i < fire_station_cnt; i++) {
            int fire_station;
            cin >> fire_station;
            adj[0].push_back(make_pair(0, fire_station));
            adj[fire_station].push_back(make_pair(0, 0));
        };
        /*
        vector<vector<int>> distances(fire_station_cnt);
        for (int i = 0; i < fire_station_cnt; i++) {
                distances[i] = dijkstra(fire_stations[i]);
        }
        

        int ret = 0;
        for (int i = 0; i < fire_scene_cnt; i++) {
                int min_cost_for_scene_i = INF;
                for (int j = 0; j < fire_station_cnt; j++) {
                        min_cost_for_scene_i = min(min_cost_for_scene_i,
        distances[j][fire_scenes[i]]);
                }
                ret += min_cost_for_scene_i;
        }
        */
        int ret = 0;
        vector<int> distances = dijkstra(0);
        for (int i = 0; i < fire_scene_cnt; i++) {
            ret += distances[fire_scenes[i]];
        }
        outputs.push_back(ret);
    }
    for (int output : outputs) cout << output << '\n';
    return 0;
}
