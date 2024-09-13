#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isTree(int n, int m, const vector<vector<int>> &adj)
{
    if (m != n - 1)
    {
        return false;
    }

    vector<bool> visited(n + 1, false);
    int visitedCount = 0;

    queue<int> q;
    q.push(1);
    visited[1] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        visitedCount++;

        for (int neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return (visitedCount == n);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (isTree(n, m, adj))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}
