#include "fileio.h"
#define LINELEN 80
#define NUM_MENU_ITEMS 5

enum themenu_choices {
    LOAD_FILE_OPTION = 1,
    COMMON_WORDS_OPTION,
    DELETE_WORD_OPTION,
    SAVE_STATS_OPTION,
    QUIT_OPTION
};

/**
 * definition of a menu item as a pair of the menu text and a function pointer
 * that points to the implementation of that option.
 **/
struct menuitem {
    char menu_text[LINELEN + 1];
    BOOLEAN (*function)(struct file_data*);
};

/**
 * functions implemented for the menu
 **/
void run_menu(void);
BOOLEAN menu_load_file(struct file_data*);
BOOLEAN menu_most_common (struct file_data*);
BOOLEAN menu_delete_word(struct file_data*);
BOOLEAN menu_save_stats(struct file_data*);
BOOLEAN menu_quit(struct file_data*);
