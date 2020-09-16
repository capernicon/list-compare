#include "array_list.h"
#include <stdlib.h>
#include <string.h>

/**
 * inserts a new word into our array list
 *
 **/
struct array_list insert_word_arraylist(struct array_list arr, char* word) {
	struct word w;
	struct word tmp;
	int j;
	int iterator;
	void * new_ptr;

        /* check count isn't greater than capacity */
	if (arr.word_count == arr.word_capacity) {
	  new_ptr = (struct word*)realloc(arr.words, sizeof(struct word) * (arr.word_capacity * 2));

       	  if (!arr.words) {
            perror("realloc");
	    return arr;
          }
          else {
	    arr.words = new_ptr;
            arr.word_capacity *= 2;
          }
        }

	w.text = strdup(word);
	w.len = strlen(w.text);
	w.count = 1;

        /* check if word duplicte */
        for (iterator = 0; iterator < arr.word_count; iterator++) {
	  if (strcmp(arr.words[iterator].text, word) == 0) {
            w.count += arr.words[iterator].count;
            break;
          }
        }

        /* if word unique */
	if (w.count == 1) {
   	  arr.words[arr.word_count] = w;
          arr.word_count++;
	  return arr;
	}
	else {
        /* remove duplicate words */
          arr = delete_word_arraylist(arr, word);
	  arr.words[arr.word_count] = w;
	  arr.word_count++;
          /* sort the words by word count order */
	  for (j = arr.word_count - 1; j > 0; j--) {
	    if (arr.words[j].count >= arr.words[j - 1].count) {	
	      tmp = arr.words[j - 1];
	      arr.words[j - 1] = arr.words[j];
	      arr.words[j] = tmp;
	    }
	    else {
	      break;
            }
          }
	return arr;
	}
}

/**
 * function that deletes a word from the list
 *
 **/
struct array_list delete_word_arraylist(struct array_list list, char* word) {
	int iterator;
	int j;

        /* found matching word */
	for (iterator = 0; iterator < list.word_count; iterator++) {
	  if (strcmp(list.words[iterator].text, word) == 0) {
	    break;
	  }
	}

	if (list.word_count == iterator) {
          return list;
        }

	free(list.words[iterator].text);

        /* adjust the list to account for removed word */
	for (j = iterator; j < list.word_count - 1; j++) {
	  list.words[j] = list.words[j + 1];
	}

	list.word_count--;

	return list;
}
