#include "../src/string.h"
#include <stdio.h>


/*************************************************
 * REMOVE List backwards.
 */
/*
static void * list_remove_rev(List *h, int index)
{
  if (index < -(h->size - 1)) return NULL;

  struct ListNode *cur = h->tail, *tmp = NULL;
  void * ret;
  for (; index < -1; ++index) cur = cur->p;

  if (cur->n && cur->p) {
    // Remove in the middle of the list
    ret = cur->data;
    tmp = cur->p;
    tmp->n = cur->n;
    tmp = tmp->n;
    tmp->p = cur->p;
    free(cur); 
  }
  else if ( !cur->n) {
    // Remove the last element
    ret = cur->data;
    tmp = cur->p;
    tmp->n = NULL;
    free(cur);
  }
  else if ( !cur->p) {
    // Remove from the begnining of the list
    ret = cur->data;
    h->head = cur->n; // Should set head to NULL
    if (h->tail == cur) h->tail = NULL;
    free(cur);
  }

  return ret;
}

*/


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
