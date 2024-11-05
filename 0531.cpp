#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

struct Station {
    int id;
    int line;
    string name;
    int time;
};

struct Edge {
    int to;
    int time;
};

unordered_map<int, string> station_names;
unordered_map<int, vector<Edge>> graph;

const int INF = 1000000; // 최대값으로 충분히 큰 값

void dijkstra(int start, vector<int>& dist, vector<int>& prev) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int u_dist = pq.top().first;
        pq.pop();

        if (u_dist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.time;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printShortestPath(int start, int dest, const vector<int>& prev) {
    stack<int> path;
    int at = dest;
    while (at != -1) {
        path.push(at);
        at = prev[at];
    }

    cout << path.size() << " ";
    while (!path.empty()) {
        cout << station_names[path.top()] << " ";
        path.pop();
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<Station> stations(n);
    for (int i = 0; i < n; ++i) {
        cin >> stations[i].id >> stations[i].line >> stations[i].name >> stations[i].time;
        station_names[stations[i].id] = stations[i].name;
    }

    for (int i = 1; i < n; ++i) {
        if (stations[i].line == stations[i - 1].line && stations[i].name != stations[i - 1].name) {
            graph[stations[i - 1].id].push_back({stations[i].id, stations[i].time});
            graph[stations[i].id].push_back({stations[i - 1].id, stations[i].time});
        }
    }
    for (int i = 0; i < q; ++i) {
        char choice;
        int start, dest;
        cin >> choice >> start >> dest;

        vector<int> dist(n + 1, INF);
        vector<int> prev(n + 1, -1);
        
        dijkstra(start, dist, prev);

        if (choice == 'A') {
            if (dist[dest] == INF) {
                cout << "None" << endl;
            } else {
                cout << dist[dest] << endl;
            }
        } else if (choice == 'B') {
            if (dist[dest] == INF) {
                cout << "None" << endl;
            } else {
                printShortestPath(start, dest, prev);
            }
        }
    }

    return 0;
}
