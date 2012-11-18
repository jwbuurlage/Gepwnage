#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

void run()
{
  string name;
  cin >> name;
  cout << "Hello " << name << "!" << endl;
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
    run();

  return 0;
}
