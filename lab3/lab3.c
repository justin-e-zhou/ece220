#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
    // Declare variables
  int n, x;
  float w1, w2, f, xi;
  float pi = M_PI;
    // Prompt user for input
  printf("Enter the values of n, omega1, and omega2 in that order\n");
    // Get user input
  scanf("%d %f %f", &n, &w1, &w2);
    // Compute function output
    /* for i from 0 to n-1
     *     compute and print xi and f(xi)
     *     use sin() function from math.h
     */
    for(x = 0; x < n; x++){
      xi = (x*pi)/n;
      f = sin(w1*xi) + .5*sin(w2*xi);
      printf("(%f,%f)\n", xi, f);
    }

    return 0;
}

