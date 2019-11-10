#include "string.h"

/*
 * Helper functions.
 */
static String *
s_init ()
{
  String *s = malloc (sizeof (String));
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

/* To resize, we are taking the largest bit set in the current
 * string and dividing by 128^n until we find n. We are returning
 * the next bit + S_INIT_SIZE. This at worst case will double the
 * size of the current string _which could be bad, very bad_ or
 * it will grow the string ?on average? by current string * 1.5.
 * This is my goal, and will be monitoring this.
 *
 * Kind of a test to see how well this works. Hopefully we get 
 * some speed or memory savings?
 */
static size_t
resize_factor (size_t sz)
{
  assert (sz > 0);
  fprintf (stdout, "Resize starts: %zu ", sz);

  int cnt = 0;
  while (sz > 0)
    {
      sz = sz >> 8;		/* Multiples of 128 */
      ++cnt;
    }

  fprintf (stdout, "  ends: %d\n", (1 << (cnt + 1)) + S_INIT_SIZE);
  return (1 << (cnt + 1)) + S_INIT_SIZE;
}


static int
copy_string (String * s, const char *src, size_t sz)
{
  assert (s);
  if (s->capacity == 0)
    {
      /* First time initilizing string, or previously destroyed.
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

  memcpy (s->str, src, sz);
  s->size = sz;
  return 0;
}

String *
str_create (const char *src, size_t sz)
{
  if (!src || sz <= 0)
    {
      perror ("Can not initilize a string with size 0.\n");
      return NULL;
    }

  String *s = s_init ();
  if (!s)
    return NULL;		/* Error should of been logged. */
  if (copy_string (s, src, sz))
    return NULL;

  return s;
}

void
str_destroy (String ** s)
{
  if (*s)
    {
      if ((*s)->str)
	free ((*s)->str);
      free (*s);
    }

  *s = NULL;
}
