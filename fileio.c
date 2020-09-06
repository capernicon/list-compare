#include "fileio.h"
#include "helpers.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/**
 * modified clear_buffer() function to work with file input
 **/
static void clear_buffer(FILE *fp) {
    int ch;
    while (ch = getc(fp), ch != '\n' && ch != EOF)
        ;
    clearerr(fp);
}

/**
 * loads the data into the appropriate list type according to the value
 * passed in.
 **/
struct file_data load_file(const char filename[], enum list_type type) {
    struct file_data data;
    FILE* input;
    char* token;
    char* delims;
    char* delimiter;
    char line[BUFSIZ];

    /* open file */
    if (!(input = fopen(filename, "r"))) {
      fprintf(stderr, "The operation failed but ");
      data.valid = FALSE;
      return data;
    }

    /* set type of list that was passed in */
    data.type = type;

    /* initialise room for tokens on a line */
    delimiter = malloc(sizeof(char) * (strlen(PUNCTUATION) + strlen(SPACES) + strlen(NUMBERS) + 1));

    delims = delimiter;

    delims = strcpy(delims, PUNCTUATION);
    delims += strlen(delims);
    delims = strcpy(delims, SPACES);
    delims += strlen(delims);
    delims = strcpy(delims, NUMBERS);

    if (data.type == LINKEDLIST) {
      data.whichlist.linked_list.head = NULL;
      data.whichlist.linked_list.tail = NULL;
      data.whichlist.linked_list.word_count = 0;

      /* read in the line and tokenise the first  word */
      while (fgets(line, BUFSIZ + EXTRACHARS, input)) {
        token = strtok(line, delimiter);

	/* tokenise rest of line (if applicable)*/
        while (token != NULL) {
	  data.whichlist.linked_list = insert_word_linkedlist(data.whichlist.linked_list, token);
	  token = strtok(NULL, delimiter);
	}
      }
    }
    else {
      data.whichlist.array_list.word_capacity = MIN_ARRAY_SIZE;
      data.whichlist.array_list.word_count = 0;
      data.whichlist.array_list.words = (struct word*)malloc(sizeof(struct word) * data.whichlist.array_list.word_capacity);

      /* read in the line and tokenise the first  word */
      while (fgets(line, BUFSIZ + EXTRACHARS, input)) {
	token = strtok(line, delimiter);

	/* tokenise rest of line (if applicable)*/
	while (token != NULL) {
	  data.whichlist.array_list = insert_word_arraylist(data.whichlist.array_list, token);
	  token = strtok(NULL, delimiter);
	}
      }
    }

    fclose(input);

    free(delimiter);

    data.valid = TRUE;

    return data;
}

/**
 * saves data from the current list type to the output file that was specified
 * as part of the command line args.
 **/
BOOLEAN save_data(struct file_data *data, const char filename[]) {
    struct linked_node *cur;
    FILE* output;
    int iterator;

    /* open file */
    if (!(output = fopen(filename, "w"))) {
      fprintf(stderr, "Error: could not open input file.\n\n");
      data->valid = FALSE;
      return data->valid;
    }

    clear_buffer(output);

    if (data->type == LINKEDLIST) {
      cur = data->whichlist.linked_list.head;
      while (cur != NULL) {
	fputs(cur->theword.text, output);
	fputs(" ", output);
	fprintf(output, "%ld", cur->theword.count);
	fputs("\n", output);
	cur = cur->next;
      }
    }
    else {
      for (iterator = 0; iterator < data->whichlist.array_list.word_count; iterator++) {
	fputs(data->whichlist.array_list.words[iterator].text, output);
	fputs(" ", output);
	fprintf(output, "%ld", data->whichlist.array_list.words[iterator].count);
	fputs("\n", output);
      }
    }

    fclose(output);

    return TRUE;
}
