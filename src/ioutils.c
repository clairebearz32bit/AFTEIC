#include "../include.h"

void raise(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 1);
    write(STDOUT_FILENO, "\x1b[H", 1);

    perror(s);
    exit(1);
}

void exitRaw() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1) {
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
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            raise("read");
        }
    }

    if (c == '\x1b') {
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1) {
            return '\x1b';
        }
        if (read(STDIN_FILENO, &seq[1], 1) != 1) {
            return '\x1b';
        }

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return ARR_U;
                case 'B': return ARR_D;
                case 'C': return ARR_R;
                case 'D': return ARR_L;
            }
        }

        return '\x1b';
    }

    else {
        return c;
    }
}

void processKey() {
    int c = readKey();

    switch (c) {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);

        case ARR_U:
        case ARR_D:
        case ARR_R:
        case ARR_L:
            moveCursor(c);
    }
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