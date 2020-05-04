#include "include.h"

void Init() {
    ds.x = 0;
    ds.y = 0;
    ds.nrows = 0;
    ds.row = NULL;

    if(getWinsize(&ds.rows, &ds.cols) == -1) {
        raise("getWinsize");
    }
}

int Start() {
    enterRaw();
    Init();
    Open("/home/claire/CLionProjects/AFTEiC/dummyfile.txt");

    return 0;
}

int main() {
    Start();

    while(1) {
        refreshScreen();
        processKey();
    }
}