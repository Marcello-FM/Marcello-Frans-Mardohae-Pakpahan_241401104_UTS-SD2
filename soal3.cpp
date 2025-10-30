#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

map<char, string> namaCafe;
map<char, vector<pair<char, int>>> adj;

void setupGraph() {
    namaCafe['A'] = "Warung Kopi Pak Harry";
    namaCafe['B'] = "Kedai Coding IKLC";
    namaCafe['C'] = "Catfe Alya";
    namaCafe['D'] = "Studio Fasilkom-TI";
    namaCafe['E'] = "Wi-Fi Gratis Sejagat";

    adj['A'].push_back({'B', 4});
    adj['A'].push_back({'C', 2});
    
    adj['B'].push_back({'A', 4});
    adj['B'].push_back({'D', 3});

    adj['C'].push_back({'A', 2});
    adj['C'].push_back({'D', 1});

    adj['D'].push_back({'B', 3});
    adj['D'].push_back({'C', 1});
    adj['D'].push_back({'E', 5});

    adj['E'].push_back({'D', 5});
}

void dfs(char u, map<char, bool>& visited) {
    visited[u] = true;
    cout << "- " << namaCafe[u] << " (" << u << ")" << endl;

    for (auto& edge : adj[u]) {
        char v = edge.first;
        if (!visited[v]) {
            dfs(v, visited);
        }
    }
}

void bfs(char start, char end) {
    queue<char> q;
    map<char, bool> visited;
    map<char, char> parent;
    map<char, int> totalJarak;
    map<char, int> edgeJarak;

    q.push(start);
    visited[start] = true;
    parent[start] = '\0';
    totalJarak[start] = 0;
    edgeJarak[start] = 0;

    while (!q.empty()) {
        char u = q.front();
        q.pop();

        if (u == end) {
            break;
        }

        for (auto& edge : adj[u]) {
            char v = edge.first;
            int weight = edge.second;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                totalJarak[v] = totalJarak[u] + weight;
                edgeJarak[v] = weight;
                q.push(v);
            }
        }
    }

    if (!visited[end]) {
        cout << "Jalur ke " << end << " tidak ditemukan." << endl;
        return;
    }

    vector<char> path;
    char curr = end;
    while (curr != '\0') {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());

    cout << "JALUR TERCEPAT PARUL (BFS):" << endl;
    cout << namaCafe[path[0]] << " (" << path[0] << ")" << endl;
    for (size_t i = 1; i < path.size(); i++) {
        cout << edgeJarak[path[i]] << "m" << endl;
        cout << namaCafe[path[i]] << " (" << path[i] << ")" << endl;
    }

    cout << "\nJalur terpendek: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
    }

    cout << "\nTotal langkah: " << path.size() - 1 << " edge" << endl;
    cout << "Total jarak: " << totalJarak[end] << " meter" << endl;
}

int main() {
    setupGraph();

    cout << "1. Hasil penelusuran DFS dari kafe A:" << endl;
    map<char, bool> visitedDfs;
    dfs('A', visitedDfs);

    cout << "\n----------------------------------------\n" << endl;

    cout << "2. Hasil BFS dari kafe A ke kafe E:" << endl;
    bfs('A', 'E');

    return 0;
}