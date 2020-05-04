#include "include.h"

<<<<<<< HEAD
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

=======
void init() {
    enterRaw();
}

int main() {
    init();
    readKey();
>>>>>>> 8e849872a531c74918017b821e1594247ff95256
    return 0;
}