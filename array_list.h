#include "shared.h"
#include "helpers.h"
#include <stdio.h>
#ifndef ARRAY_LIST
#define ARRAY_LIST

#define MIN_ARRAY_SIZE 16

struct array_list {
    /* array of words */
    struct word *words;
    /* count of words currently stored */
    long word_count;
    /* total current capacity for the data structure */
    long word_capacity;
};

/**
 * insert function prototypes for managing the array list here.
 **/
struct array_list insert_word_arraylist(struct array_list, char*);
struct array_list delete_word_arraylist(struct array_list , char *);
#endif
