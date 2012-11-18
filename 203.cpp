// 203: FIRE

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

char map[1000][1000]; // i, j
bool visited[1000][1000];

int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};

struct point
{
  point(int _i, int _j) {
    i = _i;
    j = _j;
  }

  int i;
  int j;
};

void run()
{
  memset(visited, false, sizeof(visited));

  int w, h;
  cin >> w >> h;

  queue<point> fire;
  queue<point> player;

  for (int i = 0; i < h; i++)
    for(int j = 0; j < w; j++)
    {
      cin >> map[i][j];
      if(map[i][j] == '@')
        player.push(point(i, j));
      else if(map[i][j] == '*')
        fire.push(point(i, j));
    }

  int steps = 0;
  bool found = false;

  while(true)
  {
    // simulate turn
    queue<point> new_fire;
    queue<point> new_player;

    // spread fire
    while(!fire.empty())
    {
      point f = fire.front();
      fire.pop();

      for(int k = 0; k < 4; ++k)
      {
        if(f.i + di[k] >= h || f.i + di[k] < 0 || f.j + dj[k] < 0 || f.j + dj[k] >= w)
          continue;

        if(map[f.i + di[k]][f.j + dj[k]] == '#' || map[f.i + di[k]][f.j + dj[k]] == '*')
          continue;

        map[f.i + di[k]][f.j + dj[k]] = '*';
        new_fire.push(point(f.i + di[k], f.j + dj[k]));
      }
    }

    while(!player.empty())
    {
      point p = player.front();
      player.pop();


      for(int k = 0; k < 4; ++k)
      {
        if(p.i + di[k] >= h || p.i + di[k] < 0 || p.j + dj[k] < 0 || p.j + dj[k] >= w)
        {
          found = true;
          cout << steps + 1 << endl;
          break;
        }

        if(map[p.i + di[k]][p.j + dj[k]] == '#' || map[p.i + di[k]][p.j + dj[k]] == '*')
          continue;

        if(!visited[p.i + di[k]][p.j + dj[k]])
        {
          visited[p.i + di[k]][p.j + dj[k]] = true;
          new_player.push(point(p.i + di[k], p.j + dj[k]));
        }
      }

      if(found)
        break;
    }

    if(found)
      break;

    // check for available moves
    if(new_player.empty())
    {
      cout << "IMPOSSIBLE" << endl;
      break;
    }

    fire = new_fire;
    player = new_player;

    ++steps;
  }
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}
