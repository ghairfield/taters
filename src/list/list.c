#include "list.h"

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, free */

typedef unsigned int uint;

struct ListNode {
  
  void *data;
  uint count; 
  uint nmem;  

  struct ListNode *n, *p;
};

struct List {
  struct ListNode *head, *tail;
  uint size;
};

static struct ListNode * listnode_malloc()
{
  struct ListNode *cur = malloc(sizeof(struct ListNode));
  if ( !cur) return NULL;

  cur->data  = NULL;
  cur->p     = NULL;
  cur->n     = NULL;
  cur->count = 0;
  cur->nmem  = 0;

  return cur;
}

int list_push(List *h, void *d, int nmem, int ct)
{
  if ( !h || !d || nmem <= 0 || ct <= 0) return 1;

  struct ListNode * cur = listnode_malloc();
  if ( !cur) return -1;

  cur->data = malloc(ct * nmem);
  if ( !cur->data) {
    free(cur);
    return -1;
  }

  cur->count = ct;
  cur->nmem = nmem;
  memcpy(cur->data, d, nmem * ct);

  if ( !h->head) {
    h->head = cur;
    h->tail = cur;
    cur->n = NULL;
    cur->p = NULL;
  }
  else {
    cur->n = h->head;
    h->head->p = cur;
    h->head = cur;
  }

  h->size += 1;
  return 0;
}

void * list_pop(List *h)
{
  if ( !h->head) return NULL; /* Nothing in list */

  struct ListNode *cur = h->head;
  void *ret = cur->data;
  if (h->head->n) { 
    h->head = h->head->n;
    h->size -= 1;
    free(cur);
  }
  else {
    /* Only 1 item in the list */
    free(cur);
    h->head = NULL;
    h->tail = NULL;
    h->size = 0;
  }

  return ret;  
}

int list_enqueue(List *h, void *d, int nmem, int ct)
{
  if ( !h || !d || nmem <= 0 || ct <= 0) return 1;

  struct ListNode * cur = listnode_malloc();
  if ( !cur) return -1;

  cur->data = malloc(ct * nmem);
  if ( !cur->data) {
    free(cur);
    return -1;
  }

  cur->count = ct;
  cur->nmem = nmem;
  memcpy(cur->data, d, nmem * ct);

  if ( !h->head) {
    h->head = cur;
    h->tail = cur;
    cur->n = NULL;
    cur->p = NULL;
  }
  else {
    h->tail->n = cur;
    cur->p = h->tail;
    cur->n = NULL;
    h->tail = cur;
  }

  h->size += 1;
  return 0;
}

void * list_dequeue(List *h)
{
  return list_pop(h);
}

void list_destroy(List *h)
{
  if ( !h->head) {
    free(h);
    return;
  }

  struct ListNode *cur = h->head;
  while (cur) {
    h->head = h->head->n;
    free(cur->data);
    free(cur);
    cur = h->head;
  }

  free(h);
  h = NULL;
  return;
}

List * list_init()
{
  List *l = malloc(sizeof(List));
  if ( !l) return NULL;

  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
  return l;
}

int list_size(List *h)
{
  return h->size;
}

int list_find(List *h, const void *val, 
              int (*compfunc)(const void *a, const void *b, int sz))
{
  if ( !h || !val || !compfunc) return -1;

  int ret = -1;
  uint i;
  struct ListNode *cur = h->head;

  for (i = 0; i < h->size && cur && ret == -1; ++i) {
    int v = compfunc(cur->data, val, cur->count);
    if (v == 0) ret = i;
    else cur = cur->n;
  }

  return ret;
}

void * list_at(List *h, uint index)
{
  if ( !h || index > h->size) return NULL;
  
  struct ListNode *cur = h->head;

  for (; index > 0; --index) cur = cur->n; 

  if (cur->data) return cur->data;
  else return NULL;
}

void * list_remove(List *h, uint index)
{
  if ( !h || index > h->size - 1) return NULL;

  struct ListNode *cur = h->head, *tmp = NULL;
  void * ret;
  for (; index > 0; --index) cur = cur->n;

  if (cur->n && cur->p) {
    /* Remove in the middle of the list */
    ret = cur->data;
    tmp = cur->p;
    tmp->n = cur->n;
    tmp = tmp->n;
    tmp->p = cur->p;
    free(cur); 
  }
  else if ( !cur->n && cur->p) {
    /* Remove the last element */
    ret = cur->data;
    tmp = cur->p;
    tmp->n = NULL;
    free(cur);
  }
  else if (cur->n && !cur->p) {
    /* Remove from the beginning of the list */
    ret = list_pop(h);
  }

  return ret;
}
