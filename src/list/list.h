/* Basic C89 list data structure. It should be able to be
 * used with any data type. 
 *
 * Greg Hairfield
 * 26/12/2019
 */
#ifndef _LIST_H_
#define _LIST_H_

/**
 * List
 *    List handle. An opaque handle for the user. Must be passed
 *    to the list functions as the first argument. Contains pointers
 *    to the actual list and the size of the list. 
 */
typedef struct List List;

/**
 * list_init
 *    Must be called before using the list functions. Creates
 *    an empty list and returns it. 
 *    returns empty list or NULL on failure.
 */
List * list_init();

/**
 * list_destroy
 *    Deletes any nodes that exist in the list and their data. Must
 *    be called to free any memory that has been allocated for the 
 *    list.
 *    @param h List to destroy
 */
void list_destroy(List * h);

/** 
 * list_push
 *    Add an element at the beginning of the list.
 *    @param h Initialized list
 *    @param d Data to add
 *    @param nmem Size of the data type
 *    @param ct Number of items
 *    returns 0 if success, -1 if no memory could be allocated
 *
 *    Note that the size of @d will be nmem * ct
 *    When using strings, the ct must include the null terminator.
 *    If using strlen() then you must add 1 to the length.
 */
int list_push(List *h, void *d, int nmen, int ct);

/**
 * list_pop
 *    Pop's off the first element of the list
 *    @param h Initialized list
 *    returns the data pointer or NULL
 *
 *    User _must_ free return value
 */
void * list_pop(List *h);

/**
 * list_enqueue
 *    Inserts an element at the end of the list.
 *    @param h Initialized list
 *    @param d Data to add
 *    @param nmem Size of the data type
 *    @param ct Number of items
 *    returns 0 if success, -1 if no memory could be allocated
 *
 *    Note that the size of @d will be nmem * ct
 *    When using strings, the ct must include the null terminator.
 *    If using strlen() then you must add 1 to the length.
 */
int list_enqueue(List *h, void *d, int nmem, int ct);

/**
 * list_dequeue
 *    Dequeue's the first element of the list. Same as calling
 *    list_pop.
 *    @param h Initialized list
 *    returns the data pointer or NULL
 *
 *    User _must_ free return value
 */
void * list_dequeue(List *h);

/**
 * list_size
 *    Returns the size of the list.
 *    @param h Initialized list
 *    returns Size of the list
 */
int list_size(List *h);

/**
 * list_find
 *    Searches the list using compfunc to compare the values. 
 *    @param h List to search
 *    @param val Value to search for
 *    @param compfunc Compare function. This function needs the signature:
 *      int funcName(const void *a, const void *b, int sz) -- and should return:
 *      1 if a > b
 *      0 if a == b
 *      -1 if b > a
 *      Where @a will be the value stored in the list, @b is @val, supplied by
 *      the user. @sz will be the number of elements in @a. This is only used
 *      for c-strings, see list_test.c for examples.
 *    returns The 0 based index where the item is or -1 if the item is not in
 *      the list. 
 */
int list_find(List *h, const void *val, 
              int (*compfunc)(const void *a, const void *b, int sz)); 

/**
 * list_at
 *    Gets the value at position @pos which is 0 based index. 
 *    @h List where index is stored
 *    @index 0 based position for the index
 *    returns Value at location or NULL if pos is invalid. Does not remove
 *      any items from list.
 */
void * list_at(List *h, unsigned int index);

/**
 * list_remove
 *    Removes an item from the list at the given index. If the index is negative
 *    we remove from the end of the list (similar to Python list).
 *    @param h List where the index is stored
 *    @param index >= 0 remove the position starting from the beginning of the list.
 *    returns Value stored at @index or NULL if invalid @index
 */
void * list_remove(List *h, unsigned int index);

#endif /* List include guard */
