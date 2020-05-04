#include "include.h"

void Init() {
    ds.x = 0;
    ds.y = 0;
    ds.rows = 0;

    if(getWinsize(&ds.rows, &ds.cols) == -1) {
        raise("getWinsize");
    }
}

int Start() {
    enterRaw();
    Init();

    return 0;
}

int main() {
    while(Start() == 0) {
        refreshScreen();
    }

    return 0;
}