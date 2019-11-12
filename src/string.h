/*
 * Introduction and stuff
 * 30 Oct 2019
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define S_INIT_SIZE 128		/* Size of the initial string */
#define S_GROW_SIZE 2		/* Growth multiplier          */

/*
 * Main string structure. The user is responsible for
 * the pointer. 
 */
typedef struct String_t *String;

/*
 * str_create Creates a string from the source parameter
 *
 * @param src Source string
 * @param sz  Size of the source string
 * Returns:   A pointer to a String structure
 * @see       void str_delete(String *s)
 */
String str_create (const char *src, size_t sz);

/*
 * str_destroy Deletes all the memory of the String parameter.
 *
 * @s String to destroy
 * Returns: None
 */
void str_destroy (struct String_t **s);


void str_print (const struct String_t *s, FILE * f);
