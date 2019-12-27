// LAN.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
int N;

const int MAX_N = 500;
const int INF = 987654321;
vector<pair<int, double>> adj[MAX_N];

vector<int> xs;
vector<int> ys;

double get_distance(int u, int v) {
    int x_diff = xs[u] - xs[v];
    int y_diff = ys[u] - ys[v];

    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

struct Disjoint_Set {
    vector<int> parent, rank;
    Disjoint_Set(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) rank[v]++;
    }
};

double kruskal(vector<pair<int, int>>& selected) {
    double ret = 0;
    selected.clear();

    vector<pair<double, pair<int, int>>> edges;
    for (int u = 0; u < N; u++) {
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            double cost = adj[u][i].second;
            edges.push_back(make_pair(cost, make_pair(u, v)));
        }
    }
    sort(edges.begin(), edges.end());
    Disjoint_Set set(N);
    for (int i = 0; i < edges.size(); i++) {
        double cost = edges[i].first;
        int u = edges[i].second.first, v = edges[i].second.second;

        if (set.find(u) == set.find(v)) continue;
        set.merge(u, v);
        selected.push_back(make_pair(u, v));
        ret += cost;
    }
    return ret;
}
int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<double> outputs;

    while (current_case++ < case_count) {
        cin >> N;
        int M;
        cin >> M;
        xs = vector<int>(N);
        ys = vector<int>(N);
        for (int i = 0; i < N; i++) adj[i].clear();
        for (int i = 0; i < N; i++) {
            cin >> xs[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> ys[i];
        }
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a;
            cin >> b;

            adj[a].push_back(make_pair(b, 0.0));
            adj[b].push_back(make_pair(a, 0.0));
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                adj[i].push_back(make_pair(j, get_distance(i, j)));
            }
        }
        vector<pair<int, int>> selected;
        outputs.push_back(kruskal(selected));
    }

    cout << fixed;
    cout.precision(10);
    for (double output : outputs) cout << output << '\n';
    return 0;
}
