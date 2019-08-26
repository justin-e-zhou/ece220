/*This program prints a specified row of the Pascal's
  triangle. It will take an integer input for row and
  print the corresponding row of the triangle.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n, k;
  unsigned long long x;

  printf("Enter a row index: ");
  scanf("%d",&n);

  // Write your code here
  for(k = 0; k <= n; k++){
    x = 1;
    for(float i = 1; i <= k; i++){
      x = x*(n+1-i)/i;
    }
    printf("%llu ",x);
  }
  return 0;
}
