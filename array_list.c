#include "array_list.h"
#include<stdlib.h>
#include<string.h>

/**
 * inserts a new word into our array list
 *
 **/
struct array_list insert_word_arraylist(struct array_list arr, char* word) {
	struct word w;
	struct word tmp;
	int j;
	int iterator;

	w.text = (char*)malloc(sizeof(char)*(strlen(word) + 1));
	strcpy(w.text, word);
	w.len = strlen(word);
	w.count = 1;

	for (iterator = 0; iterator < arr.word_count; iterator++) {
	  if (strcmp(arr.words[iterator].text, word) == 0) {
	    w.count += arr.words[iterator].count;  /*count word*/
	    break;
	  }
	}

        /* if word unique */
	if (w.count == 1) {
          /* check count isn't greater than capacity */
	  if (arr.word_count == arr.word_capacity) {
	    arr.words = (struct word*)realloc(arr.words, sizeof(struct word)*(arr.word_count + MIN_ARRAY_SIZE));
	    /* if array full grow by 16 and then add*/
	    arr.word_count += 1;
	    arr.words[arr.word_count - 1] = w;
	  }
	  else {
	    arr.word_count += 1;
	    arr.words[arr.word_count - 1] = w;	
	  }
	  return arr;
	}
        /* remove dupliate words */
	else {
	  arr = delete_word_arraylist(arr, word);
	  arr.word_count += 1;
	  arr.words[arr.word_count - 1] = w;
          /* sort the words by word count order */
	  for (j = arr.word_count - 1 ; j > 0 ; j--) {
	    if (arr.words[j].count >= arr.words[j - 1].count) {	
	      tmp=arr.words[j - 1];
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
