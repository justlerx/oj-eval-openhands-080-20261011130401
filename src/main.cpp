#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create adjacency list for the graph
    vector<set<int>> adj(n + 1);
    
    // Read m edges
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].insert(y);
        adj[y].insert(x);
    }
    
    // Count vertices that can be part of an odd cycle
    vector<bool> canBeInOddCycle(n + 1, false);
    
    // For each vertex, check if it can be in an odd cycle
    // A vertex can be in an odd cycle if it's part of a connected component that is not bipartite
    vector<bool> visited(n + 1, false);
    
    for (int start = 1; start <= n; start++) {
        if (visited[start]) continue;
        
        // Check if this connected component is bipartite
        vector<int> color(n + 1, -1);
        vector<int> queue = {start};
        color[start] = 0;
        bool isBipartite = true;
        
        for (int i = 0; i < queue.size(); i++) {
            int u = queue[i];
            visited[u] = true;
            
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    queue.push_back(v);
                } else if (color[v] == color[u]) {
                    isBipartite = false;
                }
            }
        }
        
        // If the component is not bipartite, all vertices in it can be in odd cycles
        if (!isBipartite) {
            for (int u : queue) {
                canBeInOddCycle[u] = true;
            }
        }
    }
    
    // Count vertices that cannot be in any odd cycle
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!canBeInOddCycle[i]) {
            count++;
        }
    }
    
    cout << count << endl;
    
    return 0;
}