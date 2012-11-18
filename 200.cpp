#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

char board[30][30];
int base_points[30];
int points[30];

struct Edge
{
  Edge(int _from, int _to, int _capacity)
  {
    from = _from;
    to = _to; 
    capacity = _capacity;
    flow = 0;
  };

  int from;
  int to; 
  int capacity;
  int flow;
};

void run()
{
  memset(board, 0, sizeof(board));
  memset(base_points, 0, sizeof(points));
  vector<int> winners;
  vector<int> unplayed[30];

  int n;
  cin >> n;

  for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j)
    {
      cin >> board[i][j];
      if(board[i][j] == 'd')
      {
        base_points[i] += 1;
        base_points[j] += 1;
      }
      else if(board[i][j] == '1')
        base_points[i] += 2;
      else if(board[i][j] == '0')
        base_points[j] += 2;
      else if(board[i][j] == '.')
        unplayed[i].push_back(j);
    }

  // id's for nodes
  int source = 0; 
  int unplayed_start = 1;
  int players_start = 500;
  int sink = 600;

  vector<Edge> edges;
  vector<Edge*> adj[sink + 1];

  int node_id = unplayed_start;

  for(int i = 0; i < n; ++i)
  {
    // check if player i can win
    // set points
    memcpy(points, base_points, sizeof(base_points));
    points[i] += unplayed[i].size() * 2; // wins all

    int total_unplayed = 0;

    // make graph
    // source ---> unplayed matches ---> players ---> sink
    for(int j = 0; j < n; ++j)
    {
      if(j == i) continue;
      edges.push_back(Edge(players_start + j, sink, points[i] - points[j]));

      for(int k = 0; k < unplayed[j].size(); ++k)
      {
        if(k == i) continue;
        ++total_unplayed;
        // all unplayed matches of player j
        edges.push_back(Edge(0, node_id, 2));
        adj[0].push_back(&edges.back());
        edges.push_back(Edge(node_id, players_start + j, 2));
        adj[node_id].push_back(&edges.back());
        edges.push_back(Edge(node_id, players_start + k, 2));
        adj[node_id].push_back(&edges.back());
        ++node_id;
      }
    }

    // max flow
    stack<int> s;
    s.push(0);
    int current;
    int max_flow = 0;

    Edge* parent[sink + 1];

    bool found_path = false;
    while(!s.empty())
    {
      current = s.top();
      s.pop();
      if(current == sink)
      {
        found_path = true;
        break;
      }

      for(int j = 0; j < adj[current].size(); ++j)
      {
        s.push(adj[current][j]->to);
        parent[adj[current][j]->to] = adj[current][j];
      }
    }

    if(found_path)
    {
      //rewind
      Edge* current = parent[sink];
      int available_flow = current->capacity - current->flow;
    }
    else
    {
      // no path.. find max_flow by summing everything to the sink
      max_flow = 1;
    }

    // check if max flow = unplayed * 2, else not all points were assigned, and there is no way
    // player i can win
    if(max_flow == total_unplayed * 2)
      winners.push_back(i);
  }

  for(int i = 0; i < winners.size(); ++i)
  {
    cout << winners[i] + 1;
    if(i != winners.size() - 1)
      cout << " ";
  }
  cout << endl;
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}
