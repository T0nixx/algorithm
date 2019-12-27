#include <algorithm>
#include <iostream>
#include <vector>
#define MAX_V 200
using namespace std;

int INF = 987654321;

int adj[MAX_V][MAX_V];
int V;

void floyd() {
    for (int i = 0; i < V; i++) adj[i][i] = 0;
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

void add(int a, int b) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = min(adj[i][j], adj[i][a] + adj[a][j]);
        }
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = min(adj[i][j], adj[i][b] + adj[b][j]);
        }
    }
}

bool is_necessary_highway(int a, int b, int c) {
    if (adj[a][b] == INF || adj[a][b] > c) return true;
    return false;
}

int main() {
    int current_case = 0;
    int case_count;
    cin >> case_count;
    vector<int> outputs;

    while (current_case++ < case_count) {
        cin >> V;

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = INF;
            }
        }

        int M, N;
        cin >> M;
        cin >> N;

        for (int i = 0; i < M; i++) {
            int a, b, c;
            cin >> a;
            cin >> b;
            cin >> c;
            adj[a][b] = min(adj[a][b], c);
            adj[b][a] = min(adj[b][a], c);
        }
        floyd();
        int ret = 0;
        for (int i = 0; i < N; i++) {
            int a, b, c;
            cin >> a;
            cin >> b;
            cin >> c;
            if (is_necessary_highway(a, b, c) == true) {
                adj[a][b] = c;
                adj[b][a] = c;
                add(a, b);
            } else {
                ret += 1;
            }
        }

        outputs.push_back(ret);
    }
    for (int output : outputs) cout << output << '\n';
    return 0;
}
