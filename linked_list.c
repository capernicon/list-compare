#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

/**
 * function to add a new word to our list. We increment counts as we add words and also omit and duplicate words
 *
 **/
struct linked_list insert_word_linkedlist(struct linked_list list, char* word) {
        /* the word */
 	struct word w;
	struct linked_node* node;
	struct linked_node* cur;
	struct linked_node* prev;

	node = (struct linked_node*)malloc(sizeof(struct linked_node));

        if (!node) {
          perror("malloc");
	  return list;
        }

	w.count = 1;
	w.len = strlen(word);
	w.text = (char*)malloc(sizeof(char)*(strlen(word)+1));
	strcpy(w.text, word);

	node->theword = w;
	node->next = NULL;
	cur = list.head;

	while (cur != NULL) {
	  if (strcmp(cur->theword.text, word) == 0) {
	    node->theword.count += cur->theword.count;
	    break;
	  }
	  cur = cur->next;
	}

	/* we only want one of each unique word in the linkedlist */
	if (node->theword.count > 1) {
	  list = delete_word_linkedlist(list, word);
	}

	/* empty */
	if (!list.head) {
	  list.head = node;
	  list.word_count = 1;
	  return list;
	}

	/* add the words */
	if (list.head->theword.count <= node->theword.count) {
	  node->next = list.head;
	  list.head = node;
	  list.word_count++;
	  return list;
	}

	cur = list.head;
	prev = list.head;

	while (cur != NULL && cur->theword.count > node->theword.count) {
	  prev = cur;
	  cur = cur->next;
	}

	node->next = cur;
	prev->next = node;
	list.word_count++;
	return list;
}

/**
 * function to traverse through our linkedlist and delete the word the user has enetred
 *
 **/
struct linked_list delete_word_linkedlist(struct linked_list list, char *word){
	struct linked_node *cur;
	struct linked_node *prev;
	struct linked_node *tmp;

	if (!list.head) {
	  return list;
        }

        if (strcmp(list.head->theword.text, word) == 0) {
	  tmp = list.head;
	  list.head = list.head->next;
	  free(tmp->theword.text);
	  free(tmp);
	  list.word_count -= 1;
	  return list;
	}

	prev = list.head;
	cur = list.head->next;

	while (cur != NULL && strcmp(cur->theword.text, word) != 0) {
	  prev = cur;
	  cur = cur->next;
	}

	if (!cur) {
	  return list;
	}

	list.word_count -= 1;
	prev->next = cur->next;
	free(cur->theword.text);
	free(cur);

	return list;
}
