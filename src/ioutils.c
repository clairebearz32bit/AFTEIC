<<<<<<< HEAD
#include <printf.h>
=======
<<<<<<< HEAD
#include <printf.h>
=======
>>>>>>> 8e849872a531c74918017b821e1594247ff95256
>>>>>>> 81da059c803a4129d227ffdc12629bde2762ade0
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

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 81da059c803a4129d227ffdc12629bde2762ade0
    while((read_code = read(STDIN_FILENO, &c, 1)) != -1) {
        if(read_code == -1 && errno != EAGAIN) {
            raise("read");
        }

        if(c == '\x1b') {
            char seq[32];

            if(read(STDIN_FILENO, &seq[0], 1) != 1) {
                return '\x1b';
            }

            if(read(STDIN_FILENO, &seq[1], 1) != 1) {
                return '\x1b';
            }

            if(seq[0] == '[') {
                if(seq[1] >= '0'&& seq[1] <= '9') {
                    if(read(STDIN_FILENO, &seq[2], 1) != 1) {
                        return '\x1b';
                    }

                    if(seq[2] == '~') {
                        switch (seq[1]) {

                        }
                    }
                }
            }
        }
    }


    return c;
}

void processKey() {
    int c = readKey();

    switch (c) {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
    }
}

<<<<<<< HEAD
=======
=======
    while((read_code = read(STDIN_FILENO, &c, 1)) != 1) {
        if(read_code == -1 && errno != EAGAIN) {
            raise("read");
        }
    }

    return c;
}

>>>>>>> 8e849872a531c74918017b821e1594247ff95256
>>>>>>> 81da059c803a4129d227ffdc12629bde2762ade0
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