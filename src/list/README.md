List
---
A queue/stack/list data structure. Initially created to supplement my typing
test game and decided this would be a seperate repo. 

#### Description
This data structure covers queue's, stacks and list operations. Internally 
everything is stored as a `void *`, and the list is a double linked list. 
Some casting might be required when reteriving a value from the list. It 
is advisable to only use a single data type per list. Mixing data types is 
possible, but not recomended.


#### Usage
To create a list:
```c
    List * myList = list_init();
```

One must also destroy the list when done.
```c
    list_destroy(myList);
```

Functionality:
Function | Description | Return value
-------------------------------------
list\_init | Initilizes an empty list | List *
list\_destroy | Distroys the contents of the list | None
list\_push | Pushes an element on the front of the list | 0 success, !0 failure
list\_enqueue | Adds element to end of list | 0 success, !0 failure
list\_pop | **Removes first element** | void * of first element
list\_dequeue | **Same as list\_pop** | void * of first element
list\_size | Get the size of the list | Number of elements
list\_find | Find a value in the list | 0 based index of item
list\_at | **Gets an elements at index `X`** | void * of element
list\_remove | **Removes an element at index `X`** | void * of element removed

See [list header](list.h) for more information. **Bolded** elements must be `free`'d
by the caller. Another note on integer return values, usually the return value will
be greater than 0 if user error, and less than 0 for program/system error.

#### License
This is freeware, I'm sure there are better implementations out there. Use at
your own peril. :worried:
