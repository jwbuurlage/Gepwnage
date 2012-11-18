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
int times[100][100];

bool visited[100];

bool recur(int node)
{

}

void run()
{
  memset(visited, false, sizeof(visited));

  int n, p;
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
      times[i][j] = sqrt(pow((tentacles[i][0] - pirates[j][0]), 2) + pow((tentacles[i][0] - pirates[j][0]), 2)) / pirates[j][2];

  int* possibilities = (int*)malloc(sizeof(int) * p);
  memcpy(times, possibilities, sizeof(possibilities));
  sort(&possibilities[0], &possibilities[p]);

  // binary search
  float time = 0.0;

  bool done = false;
  bool matching_exists = false;

  int min = 0;
  int max = p;

  int current;

  while(!done)
  {
    current = (min + max) / 2;

    if(matching_exists)
      current = current / 2;

    // is there a matching?
    for(int j = 0; j < n; ++j)
    {
      if(times[j][current] < possibilities[current] && !visited[j])
      {
        visited[j] = true;
        break;
      }

      if(!visited[j])
      {
        // was no free match
        // try switching one around
        for(int j = 0; j < n; ++j)
          if(times[current][j] < times[0][current])
            if(recur(j))
              visited[j] = true;
            else
              done = true; // no match
      }
    }

  }

  time += sqrt(pow(xh - xc, 2) + pow(yh - yc, 2)) / vc;

  cout << setprecision(6) << time << endl;
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}


