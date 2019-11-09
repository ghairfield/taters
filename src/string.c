#include "string.h"

String *
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
  s->capacity = S_INIT_SIZE;
  s->size = 0;
  return s;
}

static int
copy_string (String * s, const char *src, size_t sz)
{
  size_t init_size = S_INIT_SIZE;
  if (sz > init_size)
    {
      /* Must create large string that is multiple of S_INIT_SIZE */
    }

  s->str = malloc (sizeof (char) * init_size);
  if (!s->str)
    {
      /* Log error or something */
      return -1;
    }

  memcpy (s->str, src, sz);
  s->size = sz;
  return 0;
}

String *
str_create (const char *src, size_t sz)
{
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
      *s = NULL;
    }

  *s = NULL;
}

int
main ( /* int argc, char* argv[] */ )
{
  char test[] = "This is a test of the string thing.";
  String *s = str_create (test, strlen (test));
  fprintf (stdout, "We got back \"%s\"<S: %zu|C: %zu>\n", s->str, s->size,
	   s->capacity);
  str_destroy (&s);
  return 0;
}
