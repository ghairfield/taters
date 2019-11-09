#include "../src/string.h"
#include <stdio.h>


int main()
{
  char sen1[] = "This is the first test string of the public string class.";
  String *s = str_create(sen1, strlen(sen1));

  fprintf (stdout, "We got back \"%s\"<S: %zu|C: %zu>\n", s->str, s->size, 
           s->capacity);
  str_destroy (&s);
  return 0;
}
