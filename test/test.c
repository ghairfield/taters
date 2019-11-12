#include "../src/string.h"
#include <stdio.h>


int
main ()
{
  char sen1[] = "This is the first test string of the public string class.";
  String s = NULL;
  s = str_create (sen1, strlen (sen1));

  str_print(s, stdout);
  str_destroy (&s);
  return 0;
}
