#include "../include.h"

int getCursorXY(int *rows, int *cols) {
    char buffer[32];
    unsigned int i = 0;

    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
        return -1;
    }

    while(i < sizeof(buffer) - 1) {
        if(read(STDIN_FILENO, &buffer[i], 1) != 1 || buffer[i] == 'R') {
            break;
        }

        i++;
        buffer[i] = '\0';
    }

    if(buffer[0] != '\x1b' || buffer[1] != '[') {
        return -1;
    }

    if(sscanf(&buffer[2], "%d;%d", rows, cols) != 2) {
        return -1;
    }

    return 0;
}

int getWinsize(int *rows, int *cols) {
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
            return -1;
        }

        else {
            *cols = ws.ws_col;
            *rows = ws.ws_row;
        }

        return getCursorXY(rows, cols);
    }

    return 0;
}

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
                padding--;
            }

            while(padding--) {
                Append(tw, " ", 1);
            }

            Append(tw, welcome, len);
            Append(tw, "\x1b[K", 3);

            if(i < ds.rows - 1) {
                Append(tw, "\r\n", 2);
            }

        }
    }
}

void refreshScreen() {
    struct to_write tw = TW_INIT;

    Append(&tw, "\x1b[?251", 6);
    Append(&tw, "\x1b[H", 3);

    printRows(&tw);

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "\x1b[%d:%dH", ds.x + 1, ds.y + 1);

    Append(&tw, buffer, strlen(buffer));
    Append(&tw, "\x1b[?25h", 6);

    write(STDOUT_FILENO, tw.b, tw.len);
    Free(&tw);
}

void moveCursor(int key) {
    switch (key) {
        case ARR_L:
            if(ds.x != 0) {
                ds.x--;
            }

        case ARR_R:
            if(ds.x != ds.cols - 1) {
                ds.x++;
            }

        case ARR_U:
            if(ds.y != 0) {
                ds.y--;
            }

        case ARR_D:
            if(ds.y != ds.rows - 1) {
                ds.y++;
            }
    }
}