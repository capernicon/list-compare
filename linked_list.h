#include "shared.h"
#include <stdio.h>
#include<string.h>
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct linked_node {
    /* the pointer to the next node */
    struct linked_node *next;
    /* the word we are storing */
    struct word theword;
};

struct linked_list {
    /* pointer to the beginning of the list */
    struct linked_node *head;
    /* pointer to the end of the list */
    struct linked_node *tail;
    /* how many words we have stored */
    long word_count;
};

struct linked_list insert_word_linkedlist(struct linked_list, char*);
struct linked_list delete_word_linkedlist(struct linked_list, char*);
#endif
