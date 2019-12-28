#include "list.h"

#include <stdio.h>  // printf
#include <stdlib.h> // rand, srand
#include <string.h> // strlen
#include <time.h>   // time

/* * * * * * * * * * * * * * * * 
    C string data type tests
* * * * * * * * * * * * * * * */ 
int callbackString(const void *a, const void *b, int sz)
{
  // @a is the value stored in the list
  // @b comes as the user supplied string
  // sz is provided by the list as the number of elements in @a
  return strncmp(a, b, sz);
}

void test_string(int printVals)
{
  // Create a new list
  List * s = list_init();
  if ( !s) {
    perror("Could not allocate memory for the list.\n");
    return;
  }

  // Create some strings
  char s1[] = "This is the first string";
  char s2[] = "This is the second string";
  char s3[] = "This is the third string";
  char s4[] = "This is the fourth string";
  char s5[] = "This is the fifth string";

  // It is _important_ to make sure the '\0' character is copied. 
  list_enqueue(s, s1, sizeof(char), strlen(s1) + 1);
  list_enqueue(s, s2, sizeof(char), strlen(s2) + 1);
  list_enqueue(s, s3, sizeof(char), strlen(s3) + 1);
  list_enqueue(s, s4, sizeof(char), strlen(s4) + 1);
  list_enqueue(s, s5, sizeof(char), strlen(s5) + 1);

  if (printVals) {
    // Find a string
    int val = list_find(s, "This is the third string", callbackString);
    if (val == -1) printf("Could not find the string.\n");
    else printf("Found string at location %d = %s.\n", val, (char *)list_at(s, val));
    
    // List all strings
    char *r = list_pop(s); 
    while (r) {
      printf("We got the string \"%s\" back.\n", r);
      free(r);
      r = list_pop(s);
    }
  }
  // _must_ destroy the list
  list_destroy(s);
}


/* * * * * * * * * * * * * * * * 
    Int data type tests
* * * * * * * * * * * * * * * */ 

#define UNUSED(x) (void)(x)// Since we are comparing ints, we don't need sz
int callbackInt(const void *a, const void *b, int sz)
{
  UNUSED(sz);
  // As long as we are not sorting the list, the callback can return
  // anything non-zero if not a match and 0 if they match.
  if (*(int *)a == *(int *)b) return 0;
  else return -1;

  /*
  This would be the other way to properly return the values. 

  int dif = *(int *)a - *(int *)b;
  if (dif == 0) return 0;
  else if (dif > 0) return 1;
  else return -1;
  */ 
}

void test_int(int printVals)
{
  // Create an initial list and initialize it.
  List * p = list_init();
  if ( !p) {
    printf("Could not allocate a list.\n");
    return;
  }

  int t, i;
  srand(time(NULL));

  // Lets create some numbers and add them to the list
  for (i = 0; i < 30; ++i) {
    t = rand() % 100;
    list_push(p, &t, sizeof(int), 1);
  }

  // Now that we have a list, we can do somethings with it. See the callback
  // above this function. We will use that to search the list for number. This
  // might not find anything (since we are using rand), but we can try.
  // TODO: Make this find some values.
  if (printVals) {
    for (i = 0; i < 10; ++i) {
      t = rand() % 100;
      int pos = list_find(p, &t, callbackInt);
      if (pos == -1) printf("Could not find the number.\n");
      else {
        printf("Found number at location %d = %d.\n", pos, *(int *)list_at(p, pos));

        // And finally we will remove the found value
        int * x = list_remove(p, pos);
        printf("Removed from list %d.\n", *x);
        free(x);
      }
    }
    
    // Loop through the list, when the list is empty
    // list_pop and list_dequeue will return NULL.
    int *d;
    d = list_pop(p);
    while (d) {
      printf("We got back %d\n", *d);
      free(d);
      d = list_pop(p);
    }
  }
  // Must destroy the list or it becomes a memory leak
  list_destroy(p);
}

int main()
{
  test_int(1);
//  test_string(1);
  return 0;
}
