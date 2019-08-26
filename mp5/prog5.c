/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */


/***************************INTRO PARAGRAPH***************************
 * This program implements the set_seed, start_game, and make_guess
 * code for the codebreaker game.
 *
 * THe set_seed function takes in a use inputted integer value and
 * sets it as a seed for the random number generator. If the inputted
 * value is not an integer or contains more than one value, the input
 * is invalid.
 *
 * The start_game function takes in four memory locations of integers
 * which are the four solutions to the game. It then generates four
 * randon numbers between 1-8 based on a previosly set seed. These
 * four values are then assigned to the four pointers and static
 * solution variables to be used later.
 *
 * The make_guess function takes in a guess and four memory locations
 * for the guess to be stored to. The function first checks if there are
 * only four values entered. If not, the input is invalid and returns an
 * error. If there are only four values, it then checks if those values
 * are allbetween 1-8. If not, the input is also invalid and returns an
 * error. If they are between 1-8, the function stores each number to its
 * corresponding pointer and then checks for perfect and mismatched numbers
 * to the solution. Finally, it outputs the number of perfect and mismatched
 * numbers and returns a 1.
**********************************************************************/



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below

  int seed;   //declare int seed to store seed variable for later use in setting seed
  char post[2];   //declare array post to store extra results from input string
  if(sscanf (seed_str, "%d%1s", &seed, post)==1) {  //check if seed_str has only one value
    srand(seed);
    return 1;   //set seed and return 1 if seed_str has only one value
  }
  else {
    printf("set_seed: invalid seed\n");   //otherwise, print error and return 0
    return 0;
  }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
    //your code here
  *one = (rand()%8)+1;    //generate four random numbers 1-8 and store them to one, two, three, and four
  *two = (rand()%8)+1;
  *three = (rand()%8)+1;
  *four = (rand()%8)+1;
  solution1 = *one;     //store the numbers to static ints solution1-4 for later use
  solution2 = *two;
  solution3 = *three;
  solution4 = *four;
  guess_number = 1;     //set guess_number counter to 1

//  printf("start_game solution: %d %d %d %d\n",solution1, solution2, solution3, solution4);
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

  int w, x, y, z;         //declare variables and flags for checks
  int flag1 = solution1;
  int flag2 = solution2;
  int flag3 = solution3;
  int flag4 = solution4;
  int flagw = 1;
  int flagx = 1;
  int flagy = 1;
  int flagz = 1;
  int p = 0;            //declare counter variables for perfect and mismatched numbers
  int m = 0;
  char post[2];
  if(sscanf(guess_str,"%d%d%d%d%1s",&w,&x,&y,&z,post) == 4){    //check if four values are entered
    if((1<=w && w<=8) && (1<=x && x<=8) && (1<=y && y<=8) && (1<=z && z<=8)){   //check if all the values are numbers between 1 and 8
      *one = w;   //if the numbers match the criteria, set one, two, three, and four equal to them
      *two = x;
      *three = y;
      *four = z;
      //check for perfect matches
      if(w==solution1){   //check each input if it matches with corresponding solution
        p++;              //if it does, increment perfect counter and flip the corresponding flags
        flag1 = -1;
        flagw = 0;
      }
      if(x==solution2){
        p++;
        flag2 = -1;
        flagx = 0;
      }
      if(y==solution3){
        p++;
        flag3 = -1;
        flagy = 0;
      }
      if(z==solution4){
        p++;
        flag4 = -1;
        flagz = 0;
      }
      //check for mismatched solutions
      if(flagw==1){       //enter check only if corresponding flag has not flipped
        if(w==solution2 && solution2==flag2){   //now check all other values for this input
         m++;                                   //if it matches, increment mismatched counter and flip corresponding flags
         flag2 = -1;
         flagw = 0;
        }
        else if(w==solution3 && solution3==flag3){
          m++;
          flag3 = -1;
          flagw = 0;
        }
        else if(w==solution4 && solution4==flag4){
          m++;
          flag4 = -1;
          flagw = 0;
        }
      }
      //repeat above process for the rest of the inputs
      if(flagx==1){
       if(x==solution1 && solution1==flag1){
          m++;
          flag1 = -1;
          flagx = 0;
        }
        else if(x==solution3 && solution3==flag3){
          m++;
          flag3 = -1;
          flagx = 0;
        }
        else if(x==solution4 && solution4==flag4){
          m++;
          flag4 = -1;
          flagx = 0;
        }
      }

      if(flagy==1){
       if(y==solution1 && solution1==flag1){
          m++;
          flag1 = -1;
          flagy = 0;
        }
        else if(y==solution2 && solution2==flag2){
          m++;
          flag2 = -1;
          flagy = 0;
        }
        else if(y==solution4 && solution4==flag4){
          m++;
          flag4 = -1;
          flagy = 0;
        }
      }

      if(flagz==1){
       if(z==solution1 && solution1==flag1){
          m++;
          flag1 = -1;
          flagz = 0;
        }
        else if(z==solution2 && solution2==flag2){
          m++;
          flag2 = -1;
          flagz = 0;
        }
        else if(z==solution3 && solution3==flag3){
          m++;
          flag3 = -1;
          flagz = 0;
        }
      }   //print number of pefect and mismatched guesses
      printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number, p, m);

      ++guess_number; //increment round counter
      return 1; //return 1 if valid guess
    }
    printf("make_guess: invalid guess\n");  //invalid if numbers are not within 1-8
  }
  else{
    printf("make_guess: invalid guess\n");  //invalid if more/less than 4 numbers, or if not integers
    return 0;   //return 0 if invaid guess
  }
  return 0;
}


