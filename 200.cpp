#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <string.h>
#include <limits.h>

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

  int unplayed_count[30];
  memset(unplayed_count, 0, sizeof(unplayed_count));

  int n;
  cin >> n;

  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      cin >> board[i][j];

  for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j)
    {
      if(board[i][j] == 'd') {
        base_points[i] += 1;
        base_points[j] += 1;
      }
      else if(board[i][j] == '1')
        base_points[i] += 2;
      else if(board[i][j] == '0')
        base_points[j] += 2;
      else if(board[i][j] == '.')
      {
        unplayed[i].push_back(j);
        unplayed_count[i]++;
        unplayed_count[j]++;
      }
    }

  // id's for nodes
  int source = 0; 
  int unplayed_start = 1;
  int players_start = 500;
  int sink = 600;

  for(int i = 0; i < n; ++i)
  {
    vector<Edge> edges;
    vector<int> adj[sink + 1];

    int node_id = unplayed_start;

    // check if player i can win
    // set points
    memcpy(points, base_points, sizeof(base_points));
    points[i] += unplayed_count[i] * 2; // wins all

    int total_unplayed = 0;

    bool hopeless = false;
    for(int j = 0; j < n; ++j)
      if(points[j] > points[i])
        hopeless = true;
    if(hopeless) continue;

    // make graph
    // source ---> unplayed matches ---> players ---> sink
    for(int j = 0; j < n; ++j)
    {
      if(j == i) continue;
      edges.push_back(Edge(players_start + j, sink, points[i] - points[j]));
      adj[players_start + j].push_back(edges.size() - 1);
      adj[sink].push_back(edges.size() - 1);

      for(int k = 0; k < unplayed[j].size(); ++k)
      {
        if(unplayed[j][k] == i) continue;
        ++total_unplayed;
        // all unplayed matches of (home) player j
        edges.push_back(Edge(0, node_id, 2));
        adj[0].push_back(edges.size() - 1);
        adj[node_id].push_back(edges.size() - 1);
        edges.push_back(Edge(node_id, players_start + j, 2));
        adj[node_id].push_back(edges.size() - 1);
        adj[players_start + j].push_back(edges.size() - 1);
        edges.push_back(Edge(node_id, players_start + unplayed[j][k], 2));
        adj[node_id].push_back(edges.size() - 1);
        adj[players_start + unplayed[j][k]].push_back(edges.size() - 1);
        ++node_id;
      }
    }

    // max flow
    int max_flow = 0;
    bool visited[sink + 2];

    bool found_path = false;
    while(true)
    {
      memset(visited, false, sizeof(visited));

      found_path = false;

      stack<int> s;
      s.push(0);
      int current;
      int parent[sink + 2];

      while(!s.empty())
      {
        current = s.top();
        s.pop();

        visited[current] = true;

        if(current == sink) {
          found_path = true;
          break;
        }

        for(int j = 0; j < adj[current].size(); ++j)
        {
          if(current == edges[adj[current][j]].from) {
            if(visited[edges[adj[current][j]].to]) continue;
            if(edges[adj[current][j]].capacity - edges[adj[current][j]].flow > 0) {
              s.push(edges[adj[current][j]].to);
              parent[edges[adj[current][j]].to] = adj[current][j];
            }
          } else if(current == edges[adj[current][j]].to) {
            if(visited[edges[adj[current][j]].from]) continue;
            if(edges[adj[current][j]].flow > 0) {
              s.push(edges[adj[current][j]].from);
              parent[edges[adj[current][j]].from] = adj[current][j];
            }
          }
        }
      }

      if(found_path)
      {
        //rewind
        int current = sink;
        int available_flow = INT_MAX;
        while(current != source)
        {
          Edge e = edges[parent[current]];
          if(current == e.to) {
            if(e.capacity - e.flow < available_flow)
              available_flow = e.capacity - e.flow;
            current = e.from;
          } else if (current == e.from) {
            if(e.flow < available_flow)
              available_flow = e.flow;
            current = e.to;
          }
        }

        // we're flowing available flow along our path.. update edges
        current = sink;
        while(current != source)
        {
          Edge e = edges[parent[current]];
          if(current == e.to) {
            edges[parent[current]].flow += available_flow;
            current = e.from;
          }
          else if(current == e.from) {
            edges[parent[current]].flow -= available_flow;
            current = e.to;
          }
        }
      }
      else
      {
        // no path.. find max_flow by summing everything to the sink
        for(int j = 0; j < adj[sink].size(); ++j)
          if(sink == edges[adj[sink][j]].to) {
            max_flow += edges[adj[sink][j]].flow;
          }
        break;
      }
    }

    // check if max flow = unplayed * 2, else not all points were assigned, and there is no way
    // player i can win
    if(max_flow == total_unplayed * 2)
      winners.push_back(i); 
  }

  for(int i = 0; i < winners.size(); ++i) {
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
