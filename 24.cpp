#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <limits.h>

using namespace std;

void run()
{
  string src, best_word, a, s;
  cin >> src;

  int k, count, min_count;

  min_count = INT_MAX;

  cin >> k;
  for(int i = 0; i < k; ++i) {
    s = src;
    cin >> a;
    count = 0;
    for(int j = 0; j < s.length(); ++j) {
      if(a[j] != s[j]) {
        for(int p = 0; p < s.length(); ++p)
          if(s[p] == s[j])
            s[p] = a[j];
        ++count;
      }
    }
    if(count < min_count) {
      best_word = a;
      min_count = count;
    }
  }

  cout << best_word << endl;
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}
