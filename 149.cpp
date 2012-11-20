#include <iostream>
#include <vector>
#include <queue>

#include <math.h>
#include <algorithm>

#include <cstring>
#include <iomanip>

using namespace std;

int pirates[100][3]; // x, y, v
int tentacles[100][2];
double times[101][101];

bool visited[101];
int match[101];
double t = 0.0;
int n, p;

double dist(int x1, int y1, int x2, int y2, int v)
{
  return sqrt((double)((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2))) / (double)v;
}

bool augment(int node)
{
  for(int i = 0; i < p; ++i) {
    if(visited[i]) continue;
    if(times[node][i] > t) continue;
    visited[i] = true;
    if(match[i] == -1 || augment(match[i])) {
      match[i] = node;
      return true;
    }
  }
  return false;
}

void run()
{
  memset(visited, false, sizeof(visited));
  memset(times, 0, sizeof(times));

  cin >> n >> p;

  int xc, yc, vc;
  cin >> xc >> yc >> vc;

  for(int i = 0; i < p; ++i)
    cin >> pirates[i][0] >> pirates[i][1] >> pirates[i][2];

  int xh, yh;
  cin >> xh >> yh;

  for(int i = 0; i < n; ++i)
    cin >> tentacles[i][0] >> tentacles[i][1];

  // build graph
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < p; ++j)
      times[i][j] = dist(tentacles[i][0], tentacles[i][1], pirates[j][0], pirates[j][1], pirates[j][2]);

  double possibilities[10001];
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < p; ++j)
      possibilities[i*p + j] = times[i][j];
  sort(&possibilities[0], &possibilities[n*p]);

  bool matching_exists = false;

  int min = 0;
  int max = n*p;

  double total_time = 0.0;

  int current;

  while(true)
  {
    bool matching = true;
    memset(match, -1, sizeof(match));

    current = (min + max) / 2;
    t = possibilities[current];

    // is there a matching?
    for(int j = 0; j < n; ++j) {
      memset(visited, false, sizeof(visited));
      //match tentacle j
      if(!augment(j)) {
        matching = false;
        break;
      }
    }

    if(matching) {
      max = current;
    } else {
      min = current + 1;
    }

    if(min == max)
      break;
  }

  total_time = possibilities[min];
  total_time += dist(xh, yh, xc, yc, vc);

  cout << setprecision(10) << total_time << endl;
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}


