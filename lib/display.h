#ifndef AFTEIC_DISPLAY_H
#define AFTEIC_DISPLAY_H

int getCursorXY(int *rows, int *cols);
int getWinsize(int *rows, int *cols);
void printRows(struct to_write *tw);
void refreshScreen();

#endif