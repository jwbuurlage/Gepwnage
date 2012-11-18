// 0 -- 6
// 1 -- 2
// 2 -- 5
// 3 -- 5
// 4 -- 4
// 5 -- 5
// 6 -- 6
// 7 -- 3
// 8 -- 7
// 9 -- 6

#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

void cout_lowest(int a)
{
  if(a == 2)
    cout << '1';
  else if(a == 3)
    cout << '7';
  else if(a == 4)
    cout << '4';
  else if(a == 5)
    cout << '2';
  else if(a == 6)
    cout <<  '6';
  else if(a == 7)
    cout << '8';
  else if(a == 8)
    cout << '1' << '0';
  else if(a == 9)
    cout << '1' << '8';
  else if(a == 10)
    cout << '2' << '2';
  else if(a == 11)
    cout << '2' << '0';
  else if(a == 12)
    cout << '2' << '8';
  else if(a == 13)
    cout << '6' << '8';
  else if(a == 14)
    cout << '8' << '8';
  else if(a == 15)
    cout << '1' << '0' << '8';
  else if(a == 16)
    cout << '1' << '8' << '8';
  else if(a == 17)
    cout << '2' << '0' << '0';
  else if(a == 18)
    cout << '2' << '0' << '8';
  else if(a == 19)
    cout << '2' << '8' << '8';
  else if(a == 20)
    cout << '6' << '8' << '8';
  else if(a == 21)
    cout << '8' << '8' << '8';
}

void run()
{
  int n;
  cin >> n;

  int smallest, largest;

  // smallest
  int k = n;
  int digits = k/7 + 1;
  if(k % 7 == 0) digits--;

  if(digits <= 3)
    cout_lowest(k);
  else
  {
    cout_lowest(k - (digits - 3) * 7);
    for(int i = 3; i < digits; ++i)
      cout << '8';
  }

  cout << " ";

  // largest
  if(n % 2 == 1)
    cout << '7';
  else
    cout << '1';

  for(int i = 0; i < (n / 2) - 1; ++i)
    cout << '1';

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
