#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Graph global vars
int _V, _E;
vector<vector<int>> _adjG; // For BIG Gs: vector<list<int>> is slower on DFS
vector<vector<int>> _adjGt;

// SCC graph
enum Color { WHITE, GRAY, BLACK };
vector<vector<int>> _adjSCC; // For BIG Gs: vector<list<int>> is slower on DFS
vector<Color> _visited;
vector<int> _SCCs;
int _nSCC;

// DFSs vars
stack<int> _topologicalOrder;
vector<int> _depthSCC;

//-----------------------------------------------------------------------------
void readGraph() {
  int u, v;
  // Read Nodes
  cin >> _V >> _E;
  _adjG.resize(_V);
  _adjGt.resize(_V);
  // Read Edges
  for (int i = 0; i < _E; i++) {
    cin >> u >> v;
    _adjG[u-1].push_back(v-1);
    _adjGt[v-1].push_back(u-1);
  }
}

//-----------------------------------------------------------------------------
void firstDFS() { // Non-recursive DFS to obtain topological order
  _visited.clear(); _visited.resize(_V, WHITE);
  stack<int> s;
  for (int i = 0; i < _V; i++) {
    if (_visited[i] != WHITE) continue;
    s.push(i);
    while (!s.empty()) { // iterative DFSvisit
      int u = s.top();
      if (_visited[u] == WHITE) {
        _visited[u] = GRAY;
        for (auto v : _adjG[u])
          if (_visited[v] == WHITE) s.push(v);
      } else {
        if (_visited[u] == GRAY) _topologicalOrder.push(u);
        _visited[u] = BLACK;
        s.pop();
      }
    }
  }
}

//-----------------------------------------------------------------------------
void secondDFS() { // Non-recursive DFS to obtain SCCs
  // Init SCCs
  _SCCs.resize(_V, -1);
  _nSCC = 0;
  _visited.clear(); _visited.resize(_V, WHITE);
  stack<int> s;
  while (!_topologicalOrder.empty()) {
    int i = _topologicalOrder.top(); _topologicalOrder.pop();
    if (_visited[i] != WHITE) continue;
    s.push(i);
    while (!s.empty()) { // iterative DFSvisit
      int u = s.top();
      if (_visited[u] == WHITE) {
        _visited[u] = GRAY;
        for (auto v : _adjGt[u])
          if (_visited[v] == WHITE) s.push(v);
      } else {
        if (_visited[u] == GRAY) _SCCs[u] = _nSCC;
        _visited[u] = BLACK;
        s.pop();
      }
    }
    _nSCC++;
  }
}

//-----------------------------------------------------------------------------
void buildSCCgraph() {
  _adjSCC.resize(_nSCC);
  for (int u = 0; u < _V; u++) {
    for (int v : _adjG[u]) {
      if (_SCCs[u] != _SCCs[v]) {
        _adjSCC[_SCCs[u]].push_back(_SCCs[v]); // checking if already exists might cost more
      }
    }
  }
}

//-----------------------------------------------------------------------------
int longestPath() { // SCC vertices are in topological order
  int maxDepth = 0;
  _depthSCC.clear(); _depthSCC.resize(_nSCC, 0);
  for (int u = _nSCC-1; u >= 0; u--) {
    for (int v : _adjSCC[u]) { // explore arc (u,v) in u's topological order
      _depthSCC[u] = max(_depthSCC[u], _depthSCC[v] + 1);
    }
    maxDepth = max(maxDepth, _depthSCC[u]);
  }
  return maxDepth;
}

//-----------------------------------------------------------------------------
int main(){
  std::ios::sync_with_stdio(0); // disable sync with c libs (printf/scanf)
  std::cin.tie(0);              // discard cin buffer after each line of input

  // O(E)
  readGraph();
  // O(V + E)
  firstDFS();
  // O(V + E)
  secondDFS(); // identify SCCs
  // O(V + E)
  buildSCCgraph();
  // O(V + E)
  printf("%d\n", longestPath());
  return 0;
}
