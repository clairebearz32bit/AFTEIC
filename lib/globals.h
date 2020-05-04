#ifndef AFTEIC_GLOBALS_H
#define AFTEIC_GLOBALS_H

#define VERSION "0.0.1"
#define CTRL_KEY(k) ((k) & 0x1f)
#define CARRIAGE "\r\n"
#define SHOW_CURSOR "\x1b[?251"
#define TW_INIT {NULL, 0}

// Simple macro to check whether or not the CTRL key is pressed.
struct termios original, raw;

// Two different variables to differentiate the original terminal settings and raw settings.

<<<<<<< HEAD
typedef struct Row {
    int size;
    char *chars;
} Row;

=======
>>>>>>> 8e849872a531c74918017b821e1594247ff95256
struct to_write {
    char *b;
    int len;
};

<<<<<<< HEAD
=======
typedef struct Row {
    int size;
    char *chars;
} Row;

>>>>>>> 8e849872a531c74918017b821e1594247ff95256
struct displaySettings {
    int x, y;
    int rows, cols;
    int n;
    Row row;
<<<<<<< HEAD

=======
>>>>>>> 8e849872a531c74918017b821e1594247ff95256
} ds;

enum Keys {
    ARR_L,
    ARR_R,
    ARR_U,
    ARR_D,
    BACK
};
#endif
