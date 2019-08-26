#include <stdlib.h>
#include <stdio.h>
/*The program takes an input of 2 integers a and b. b must be greater than a.
  The program then prints all semiprimes between and including a and b.
  A semiprime number is a number that is the product of two prime numbers.
*/

int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b);
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)  {
  if(number==1)       //default case if number = 1 bc 1 is not prime
    return 0;
  for(int i = 2; i <= number/2; i++){
    if(number%i==0){  //if number%i==0, then it is prime bc it can be divided by that number
      return 0;       //if it does divide fully, then return 0
    }
  }
  return 1;           //otherwise, return 1
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int flag = 0;   //flag for return value
  for(int n = a; n <= b; n++){  //outer loop to check the numbers between a and b
    for(int k = 2; k < n; k++){ //inner loop to check all numbers up to n
      if(is_prime(k)==1 && is_prime(n/k)==1 && n%k==0){ //print n if k is prime, n/k is prime, and n is divisible by k
        printf("%d ",n);
        flag = 1; //set flag to 1
        break;    //break from loop
      }
    }
  }
  if(flag == 1)
    return 1;
  else
    return 0;
}



