#include "string.h"

struct String_t
{
  size_t capacity;		/* Capacity of str from 1 to N */
  size_t size;			/* sizeof str                  */
  char *str;			/* sizeof capacity             */
};

/*
 * Helper functions.
 */
static struct String_t *
s_init ()
{
  struct String_t *s = malloc (sizeof (struct String_t));
  if (!s)
    {
      /* Log error or something */
      perror ("Could not create the string, out of memory.\n");
      return NULL;
    }

  s->str = NULL;
  s->capacity = 0;
  s->size = 0;
  return s;
}

/* 
 * Calculate the growth size of the string.
 * Other options:
 *    sz *= 1.5
 *
 */

static size_t
resize_factor (size_t sz)
{
  assert (sz > 0);
  return sz + S_INIT_SIZE;
}


static int
copy_string (struct String_t *s, const char *src, size_t sz)
{
  assert (s);
  if (s->capacity == 0)
    {
      /* First time initializing string, or previously destroyed.
       * We are assuming if s->capacity == 0 then s->str = NULL;
       */
      assert (!s->str);

      int size = (sz > S_INIT_SIZE - 1) ? resize_factor (sz) : S_INIT_SIZE;
      s->str = malloc (sizeof (char) * size);
      if (!s->str)
        {
          perror ("System out of memory.\n");
          return -1;
        }
      s->capacity = size;
    }
  else if (s->capacity < sz)
    {
      // Grow string
      assert (s->str);

      free (s->str);
      int size = resize_factor (sz);
      char *tmp = malloc (sizeof (char) * size);
      if (!tmp)
	{
	  perror ("System out of memory.\n");
	  return -1;
	}
      s->capacity = size;
      s->str = tmp;
    }

  strcpy (s->str, src);
  s->size = sz;
  return 0;
}

struct String_t *
str_create (const char *src, size_t sz)
{
  if (!src || sz <= 0)
    {
      perror ("Can not initialize a string with size 0.\n");
      return NULL;
    }

  struct String_t *s = s_init ();
  if (!s)
    return NULL;		/* Error should of been logged. */
  if (copy_string (s, src, sz))
    return NULL;

  return s;
}

void
str_destroy (struct String_t **s)
{
  if (*s)
    {
      if ((*s)->str)
        free ((*s)->str);
      free (*s);
    }

  *s = NULL;
}

void
str_print (const struct String_t *s, FILE * f)
{
  fprintf (f, "%s <sz: %zu|cap: %zu>\n", s->str, s->size, s->capacity);
}
