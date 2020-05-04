#include "../include.h"

void raise(const char *s) {
    write(STDOUT_FILENO, "\x1b[J", 1);
    write(STDOUT_FILENO, "\x1b[H", 1);

    perror(s);
    exit(1);
// Program fucked up, print why (hopefully).

}

void exitRaw() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1) {
        raise("tcsetattr");
    }
}

void enterRaw() {
    if (tcgetattr(STDIN_FILENO, &original) == -1) {
        raise("tcgetattr");
    }
    atexit(exitRaw);

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        raise("tcsetattr");
    }
}

int readKey() {
    int read_code;
    char c;

    while((read_code = read(STDIN_FILENO, &c, 1)) != 1) {
        if(read_code == -1 && errno != EAGAIN) {
            raise("read");
        }
    }

    return c;
}

void Append(struct to_write *tw, const char *s, int len) {
    char *ptr = realloc(tw->b, tw->len + len);

    if(ptr == NULL) {
        return;
    }

    memcpy(&ptr[tw->len], s, len);

    tw->b = ptr;
    tw->len += len;
}

void Free(struct to_write *tw) {
    free(tw->b);
}