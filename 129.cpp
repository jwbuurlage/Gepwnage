#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

int amount[26];

void run()
{
  memset(amount, 0, sizeof(amount));

  string s;
  getline(cin, s);

  for(int i = 0; i < s.size(); ++i)
  {
    if(s[i] != ' ')
      amount[s[i] - 'A']++;
  }

  int max = 0;
  int max_id = 0;
  bool multiple = false;
  for(int i = 0; i < 26; ++i)
  {
    if(amount[i] == max)
      multiple = true;
    if(amount[i] > max)
    {
      multiple = false;
      max = amount[i];
      max_id = i;
    }
  }

  int distance = ((max_id - 4) + 26) % 26;

  if(multiple) {
    cout << "NOT POSSIBLE";
  }
  else
  {
    cout << distance << " ";
    for(int i = 0; i < s.size(); ++i)
    {
      if(s[i] == ' ')
        cout << ' ';
      else
        cout << (char)((((s[i] - 'A') + (26-distance)) % 26) + 'A');
    }
  }

  cout << endl;
}

int main()
{
  int runs;
  cin >> runs;
  string s;
  getline(cin, s);
  while(runs--)
    run();

  return 0;
}
