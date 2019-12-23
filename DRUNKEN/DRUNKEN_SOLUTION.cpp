#include <algorithm>
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

int V, adj[500][500];
int delay[500];
int W[500][500];
void solve() {
    vector<pair<int, int>> order;
    for (int i = 0; i < V; i++) {
        order.push_back(make_pair(delay[i], i));
    }
    sort(order.begin(), order.end());
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j)
                W[i][j] = 0;
            else
                W[i][j] = adj[i][j];
        }
    }
    int ret = INF;
    for (int k = 0; k < V; k++) {
        int w = order[k].second;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                W[i][j] = min(adj[i][w] + delay[w] + adj[w][j], W[i][j]);
            }
        }
    }
}

int main() {
    cin >> V;
    int E;
    cin >> E;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 987654321;
        }
    }

    for (int i = 0; i < V; i++) cin >> delay[i];

    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a;
        cin >> b;
        cin >> c;

        adj[a - 1][b - 1] = c;
        adj[b - 1][a - 1] = c;
    }

    solve();

    int total_case;
    cin >> total_case;
    vector<int> outputs;
    for (int i = 0; i < total_case; i++) {
        int u, v;
        cin >> u;
        cin >> v;

        outputs.push_back(W[u - 1][v - 1]);
    }

    for (int i = 0; i < outputs.size(); i++) cout << outputs[i] << '\n';
    return 0;
}
