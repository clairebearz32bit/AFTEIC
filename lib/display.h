#ifndef AFTEIC_DISPLAY_H
#define AFTEIC_DISPLAY_H

<<<<<<< HEAD
int getCursorXY(int *rows, int *cols);
int getWinsize(int *rows, int *cols);
void printRows(struct to_write *tw);
void refreshScreen();
=======
void printRows(struct to_write *tw);
void refreshScreen();
void moveCursor();
>>>>>>> 8e849872a531c74918017b821e1594247ff95256

#endif