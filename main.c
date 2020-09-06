#include "fileio.h"
#include "menu.h"
#include <stdlib.h>

/* enum for command line argc */
enum files {
    NO_FILE,
    IN_FILE,
    OUT_FILE,
    LIST_FILE,
    COMPLETE_FILES
};

int main(int argc, char* argv[]) {
    /* check the command line args */
    struct file_data data;

    if (argc == NO_FILE) {
      fprintf(stderr, "Error: invalid file count passed in.\n\n");
      return EXIT_FAILURE;
    }

    else if (argc == COMPLETE_FILES) {
      /* list type */
      if (strcmp(argv[LIST_FILE], "linkedlist") == 0) {
	data.type = LINKEDLIST;
      }
      else if (strcmp(argv[LIST_FILE], "arraylist") == 0) {
	data.type = ARRAYLIST;
      }
      else {
	fprintf(stderr, "Please select either (a) for arraylist or (l) for linkedlist\n");
	return EXIT_FAILURE;
      }

      /* load in the in file */
      data = load_file(argv[IN_FILE], data.type);

      /* save out to the out fiel */
      save_data(&data, argv[OUT_FILE]);

      menu_quit(&data);
    }
    else {
      run_menu();
    }

    return EXIT_SUCCESS;
}
