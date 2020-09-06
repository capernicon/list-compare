#include "helpers.h"
#include "shared.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * function for copying a string to another pointer
 **/
char* strdup(const char orig[]) {
    /* allocate the space for the copy */
    char* copy;
    copy = (char*)malloc(strlen(orig) + 1);
    if (!copy) {
        perror("malloc");
        return NULL;
    }
    /* copy the string */
    strcpy(copy, orig);
    return copy;
}
