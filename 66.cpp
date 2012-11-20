#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

bool mem[16];

bool works(int bm, int* v)
{
  if(mem[bm]) return false;

  int one = 0, two = 0;
  for(int i = 0; i < 4; ++i)
    if(bm & (1 << i)) one += v[i];
    else two += v[i];

  if(one == two) return true;
  else mem[bm] = true;

  for(int i = 0; i < 4; ++i)
    if((bm & (1 << i)) == 0) {
      if(works(bm | (1 << i), v)) return true;
    }

  return false;
}

void run()
{
  memset(mem, 0, sizeof(mem));

  int occ[10];
  memset(occ, 0, sizeof(occ));

  int d, m, y, d2, m2, y2, count;
  cin >> d2 >> m2 >> y2;
  d = d2; m = m2; y = y2;

  do { occ[d % 10]++; d /= 10; } while (d > 0);
  do { occ[m % 10]++; m /= 10; } while (m > 0);
  do { occ[y % 10]++; y /= 10; } while (y > 0);

  count = occ[d2 % 10];
  for(int i = 0; i < 10; ++i) if(occ[i] != count && occ[i] != 0) { cout << "no" << endl; return; }

  int v[4];
  v[0] = d2; v[1] = m2; v[2] = (y2 / 100); v[3] = (y2 % 100);

  int bitmask = 0;

  if(works(bitmask, v)) { cout << "yes" << endl; }
  else { cout << "no" << endl; }
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}
