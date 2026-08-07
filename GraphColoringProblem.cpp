#include <climits>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class Graph {
  map<int, list<int>> mp;

public:
  void addEdge(int x, int y) {
    mp[x].push_back(y);
    mp[y].push_back(x);
  }

  bool dfs_helper(int scr, int parent, int color, map<int, int> &visited) {
    // Jab bhi kisi node par aaye hain that means this node is not visited.
    // We need to make this node as visited and assign a color to this node.

    visited[scr] = color;

    // Aap iske nbr par jao and same process repeat karo.
    for (int nbr : mp[scr]) {

      if (visited[nbr] == 0) {

        // Now I ask recursion to check if I am able to color the graph from
        //  this nbr or not?
        bool smallAns = dfs_helper(nbr, scr, 3 - color, visited);
        if (smallAns == 0) {
          return false;
        }

      } else if (nbr != parent and visited[nbr] == color) {
        return false;
      }
    }

    return true;
  }

  // Kya mera graph bipartite hain ki nahi?
  bool dfs(int scr) {
    map<int, int> visited;
    // visited[x]=0 that means node x is unvisited.
    // visited[x]= 1/2 that means this node is visisted and also has a color
    // respectively.

    // Initialisation of your visited.
    // Useless as in map by default a new will always have zero as the starting
    //  value.
    for (pair<int, list<int>> x : mp) {
      int Node = x.first;
      visited[Node] = 0;
    }

    int color = 1;

    return dfs_helper(scr, 0, color, visited);
  }

  void Print() {

    for (pair<int, list<int>> x : mp) {
      int Node = x.first;
      list<int> nbr = x.second;

      cout << Node << " : ";

      for (int y : nbr) {
        cout << y << " ";
      }

      cout << endl;
    }
    cout << endl << "---------------------------------" << endl;
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  Graph g;
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g.addEdge(x, y);
  }

  g.Print();
  cout << g.dfs(1) << endl;

  return 0;
}
