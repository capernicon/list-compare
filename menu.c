#include "menu.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

/**
 * reads the leftover bytes from stdin and throws them away, resetting
 * the error state
 **/
static void clear_buffer(void) {
    int ch;
    while (ch = getc(stdin), ch != '\n' && ch != EOF)
        ;
    clearerr(stdin);
}

/**
 * function to retrive the user input and output the correct menu choice
 *
 **/
void get_string_input(const char prompt[], char output[], long len) {
    char buf[LINELEN + 1];

    /* output prompt to screen */
    printf(prompt);

    if (fgets(buf, len, stdin) == NULL) {
      fprintf(stderr, "You have exited the program.\n\n");
      exit(EXIT_FAILURE);
    }

    /* buffer overflow */
    if (buf[strlen(buf) -1] != '\n') {
      fprintf(stderr, "Line too long!\n\n");
      clear_buffer();
      exit(EXIT_FAILURE);
    }

    /* add null terminator and copy */
    buf[strlen(buf) - 1] = '\0';
    strcpy(output, buf);
}

#define STRTOL 10
/**
 * function that passes in the string and converts to an int
 **/
void get_int_input(const char prompt[], int* output) {
    char buf[LINELEN + 1];
    char * long_ptr;
    int number;

    printf(prompt);

    get_string_input("", buf, LINELEN + EXTRACHARS);

    /* convert first char to int */
    number = strtol(buf, &long_ptr, STRTOL);

    *output = number;
}

/**
 * Initalise the menu with the correct strings and function pointers.
 * You must not stored the menu numbers and the structure should be
 * initialised in a maintainable way such that it will be relatively
 * easy to add menu items.
 **/
void menu_init(struct menuitem menu[]) {
    /* create the menu system and copy over */
    struct menuitem themenu[NUM_MENU_ITEMS] = {
	    { "load a file", &menu_load_file },
	    { "most common words", &menu_most_common },
	    { "delete a word", &menu_delete_word },
	    { "save stats", &menu_save_stats },
	    { "quit", &menu_quit }
    };

    memcpy(menu, &themenu, sizeof(themenu));
}

/**
 * display the menu
 *
 **/
void display_menu_options(struct menuitem themenu[NUM_MENU_ITEMS]) {
    int iterator;

    printf("Data Structure Tester\n=====================\n");

    for (iterator = 0; iterator < NUM_MENU_ITEMS; iterator++) {
      printf("%d) ", iterator + 1);
      printf("%s\n", themenu[iterator].menu_text);
    }

    printf("Please enter your choice:\n");
}

/* prompt to screen for delete a word */
void delete_word_prompt() {
    printf("Delete a Word\n=============\n");
}

/* prompt to screen for most word occurences */
void most_word_occurences_prompt(int num) {
    printf("%d Most Common Words\n===================\n", num);
}

/* prompt to screen for save to stats */
void save_stats_prompt() {
    printf("Save Stats\n==========\n");
}

void timing_prompt(double time) {
    printf("took %f seconds to complete.\n", time);
}

/**
 * kickstarts the menu system and performs the menu loop of display,read and
 * process input.
 **/
void run_menu(void) {
    /* declare and intialise the menu array correctly using the menu_init function */
    struct menuitem menu[NUM_MENU_ITEMS];
    struct file_data* file;
    clock_t start, end;
    int menu_choice;
    double seconds;

    file = (struct file_data*)malloc(sizeof(struct file_data));
    file->valid = FALSE;
    menu_init(menu);

    while (TRUE) {
      /* display the menu */
      display_menu_options(menu);
      /* get users choice */
      get_int_input("", &menu_choice);

      switch (menu_choice) {
        case LOAD_FILE_OPTION:
	  start = clock();
	  menu[LOAD_FILE_OPTION - 1].function(file);
	  end = clock();
          seconds = ((double)end - start) / CLOCKS_PER_SEC;
          timing_prompt(seconds);
	  break;

  	case COMMON_WORDS_OPTION:
	  start = clock();
	  menu[COMMON_WORDS_OPTION - 1].function(file);
	  end = clock();
	  seconds = ((double)end - start) / CLOCKS_PER_SEC;
          timing_prompt(seconds);
	  break;

        case DELETE_WORD_OPTION:
	  start = clock();
	  menu[DELETE_WORD_OPTION - 1].function(file);
	  end = clock();
	  seconds = ((double)end - start) / CLOCKS_PER_SEC;
          timing_prompt(seconds);
	  break;

        case SAVE_STATS_OPTION:
	  start = clock();
	  menu[SAVE_STATS_OPTION - 1].function(file);
	  end = clock();
          seconds = ((double)end - start) / CLOCKS_PER_SEC;
          timing_prompt(seconds);
	  break;

        case QUIT_OPTION:
	  menu[QUIT_OPTION - 1].function(file);
	  break;
      }

      if (menu_choice < 1 || menu_choice > 5) {
        fprintf(stderr, "Error: invalid option. Please try again.\n\n");
      }

      /* quit the program */
      if (menu_choice == QUIT_OPTION) {
        break;
      }
    }

    free(file);
}

/**
 * handle a request to load the file.
 **/
#define LIST_TYPE 0
BOOLEAN menu_load_file(struct file_data* thedata) {
    /* replace this return value with the correct implementation for this
     * function consistent with the specifications */
    char buf[LINELEN + 1];
    char file[LINELEN + 1];

    get_string_input("Enter the path to the filename you want to load:\n", file, LINELEN + EXTRACHARS);

    get_string_input("Would you like to load this into an (a)rraylist or a (l)inkedlist ?\n (Enter a or l): ", buf, LINELEN + EXTRACHARS);

    switch(buf[LIST_TYPE]) {
      case 'l':
      thedata->type = LINKEDLIST;
      break;

      case 'a':
      thedata->type = ARRAYLIST;
      break;

      default:
        fprintf(stderr, "Please enter either (a) for arraylist or (l) for linkedlist\n");
        return FALSE;
        break;
    }

    *thedata = load_file(file, thedata->type);

    return TRUE;
}

/**
 * retrieve the N most common words from the list
 **/
BOOLEAN menu_most_common(struct file_data* thedata) {
    struct linked_node *cur;
    int iterator; int num; int index;

    if (thedata->valid == FALSE) {
      fprintf(stderr, "Error: data file is not loaded.\n\n");
      return FALSE;
    }

    get_int_input("Please enter how many items to display\n", &num);

    most_word_occurences_prompt(num);

    if (thedata->type == LINKEDLIST) {
      cur = thedata->whichlist.linked_list.head;
      index = 1;
      while (num != 0) {
        if (cur == NULL) {
	  printf("There are only %ld in the list\n", thedata->whichlist.linked_list.word_count);
	  break;
	}
	printf("%d) %s - %ld occurences\n", index++, cur->theword.text, cur->theword.count);
	cur = cur->next;
	num--;
      }
    }
    else {
      for (iterator = 0; iterator < num; iterator++) {
	 if (thedata->whichlist.array_list.word_count == iterator) {
	   printf("There is only %ld word(s) in the list\n", thedata->whichlist.array_list.word_count);
	   break;
	 }
	 printf("%d) %s - %ld occurences\n", (iterator + 1), thedata->whichlist.array_list.words[iterator].text, thedata->whichlist.array_list.words[iterator].count);
      }
    }
    return TRUE;
}

/**
 * search the list and delete the word specified
 **/
BOOLEAN menu_delete_word(struct file_data* thedata) {
    char word[LINELEN + 1];
    long word_count = 0;
    long length = 0;
    struct linked_node *cur;
    int iterator;

    if (thedata->valid == FALSE) {
      fprintf(stderr, "Error: data file is not loaded.\n\n");
      return FALSE;
    }

    delete_word_prompt();

    get_string_input("Input a word to delete from the list: ", word, LINELEN + EXTRACHARS);

    if (thedata->type == LINKEDLIST){
      length = thedata->whichlist.linked_list.word_count;
      cur = thedata->whichlist.linked_list.head;
      while (cur != NULL) {
	if (strcmp(cur->theword.text, word) == 0) {
	  word_count = cur->theword.count;
	}
	cur = cur->next;
      }
      thedata->whichlist.linked_list = delete_word_linkedlist(thedata->whichlist.linked_list, word);

      if (length == thedata->whichlist.linked_list.word_count) {
	fprintf(stderr, "%s was not found\n\n", word);
	perror("");
      }
      else {
	printf("Succesfully deleted %s from the linked list - there were %ld occurences\n", word, word_count);
      }
    }
    else {
      length = thedata->whichlist.array_list.word_count;
      for (iterator = 0; iterator < thedata->whichlist.array_list.word_count; iterator++) {
	if (strcmp(thedata->whichlist.array_list.words[iterator].text, word) == 0)
	  word_count = thedata->whichlist.array_list.words[iterator].count;
	}
	thedata->whichlist.array_list = delete_word_arraylist(thedata->whichlist.array_list, word);
	if (length == thedata->whichlist.linked_list.word_count) {
	  fprintf(stderr, "%s was not found\n\n", word);
	  perror("");
	}
	else {
	  printf("Succesfully deleted %s from the Array list - there were %ld occurences\n", word, word_count);
	}
    }

    return TRUE;
}

/**
 * save the stats to a text file
 **/
BOOLEAN menu_save_stats(struct file_data* thedata) {
    char line[LINELEN + 1];

    if (thedata->valid == FALSE) {
      fprintf(stderr, "Error: data file is not loaded.\n\n");
      return FALSE;
    }

    save_stats_prompt();

    get_string_input("Please enter a filename to save the stats to: ", line, LINELEN + EXTRACHARS);

    save_data(thedata, line);

    if (thedata->valid == FALSE)
      fprintf(stderr, "Error: couldn't save file.\n\n");
    else {
      printf("File saved successfully.\n");
    }

    return TRUE;
}

/**
 * quit the program and clean up memory.
 **/
BOOLEAN menu_quit(struct file_data* thedata) {
    struct linked_node *cur;
    int iterator;

    if (thedata->valid == FALSE) {
      fprintf(stderr, "Error: no File loaded\n\n");
      return FALSE;
    }

    /* free the linkedlist from memory */
    if (thedata->type == LINKEDLIST) {
      cur = thedata->whichlist.linked_list.head;
      while (thedata->whichlist.linked_list.head != NULL) {
        cur = thedata->whichlist.linked_list.head;
	thedata->whichlist.linked_list.head = thedata->whichlist.linked_list.head->next;
	free(cur->theword.text);
	free(cur);
      }
    }
    /* free the arraylist from memory */
    else {
      for (iterator = 0; iterator < thedata->whichlist.array_list.word_count; iterator++) {
	free(thedata->whichlist.array_list.words[iterator].text);
      }
      free(thedata->whichlist.array_list.words);
    }

    printf("Exit successful.\n\n");
    return TRUE;
}
