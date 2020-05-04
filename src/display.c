#include "../include.h"

void printRows(struct to_write *tw) {
    for(int i = 0; i < ds.rows; i++) {
        if(i == ds.rows / 3) {
            char welcome[128];
            int len = snprintf(welcome, sizeof(welcome),
                    "Another Fucking Text Editor in C99 -- version %s", VERSION);
            if(len > ds.cols) {
                len = ds.cols;
            }
            int padding = (ds.cols - len) / 2;
            if(padding) {
                Append(tw, "~", 1);
                padding--;
            }
        }
    }

}

void refreshScreen() {
    struct to_write tw = TW_INIT;

    Append(&tw, SHOW_CURSOR, 6);
    Append(&tw, "\x1b[H", 3);

}