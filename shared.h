#ifndef SHARED_H
#define SHARED_H
/**
 * definition of the boolean type
 **/
typedef enum truefalse {
    FALSE,
    TRUE
} BOOLEAN;

#define EXTRACHARS 2

#define PUNCTUATION "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define SPACES " \n\t\v\f\r"
#define NUMBERS "0123456789"

struct word {
    /* the string data for the word */
     char* text;
    /* the length of the word */
    long len;
    /* how many times this word has been seen */
    long count;
};
#endif
