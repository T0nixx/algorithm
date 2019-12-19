// ROUTING.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

double INF = pow(10, 5000);

int V;
int E;
vector<vector<pair<double, int>>> adj;

vector<double> get_min_coef(int src) {
    vector<double> dist(V, INF);
    dist[src] = 1.0;
    priority_queue<pair<double, int>> pq;

    pq.push(make_pair(-1.0, src));

    while (pq.empty() == false) {
        double coef = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].second;
            double next_dist = coef * adj[here][i].first;
            if (dist[there] > next_dist) {
                dist[there] = next_dist;
                pq.push(make_pair(-next_dist, there));
            }
        }
    }
    return dist;
}

vector<double> get_min_coef2(int src) {
    vector<double> dist(V, INF);
    vector<bool> visited(V, false);
    dist[src] = 1.0;

    while (true) {
        int closest = INF;
        int here;

        for (int i = 0; i < V; i++) {
            if (dist[i] < closest && visited[i] == false) {
                closest = dist[i];
                here = i;
            }
        }
        if (closest == INF) break;
        visited[here] = true;
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].second;
            if (visited[there] == true) continue;
            double next_dist = adj[here][i].first * dist[here];
            dist[there] = min(next_dist, dist[there]);
        }
    }
    return dist;
}

int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<double> outputs;

    while (current_case++ < case_count) {
        cin >> V;
        cin >> E;
        adj = vector<vector<pair<double, int>>>(V);
        for (int i = 0; i < E; i++) {
            int e1, e2;
            double coef;
            cin >> e1;
            cin >> e2;
            cin >> coef;
            adj[e1].push_back(make_pair(coef, e2));
            adj[e2].push_back(make_pair(coef, e1));
        }

        outputs.push_back(get_min_coef(0)[V - 1]);
    }
    cout << fixed;
    cout.precision(10);
    for (double output : outputs) cout << output << '\n';
    return 0;
}
