#include <stdio.h>
#include <iostream>
using namespace std;
int counter = 0;
#define sqrt2 0.41421356

int main()
{
  int runs;
  cin >> runs;
  while(runs--) {
    cout << "Scenario #" << ++counter << ":" << endl;
    int n, m;
    cin >> n >> m;
    if((n % 2 == 0 && m % 2 == 0) || (n % 2 != 0 && m % 2 == 0) || (n % 2 == 0 && m % 2 != 0)) { printf("%.2f\n\n", (double)(n * m)); }
    else { printf("%.2f\n\n", (double)(n * m) + sqrt2); }
  }

  return 0;
}
