#include "../include.h"

void Open(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        raise("fopen");
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t len;

    while((len = getline(&line, &cap, fp)) != -1) {
        while(len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            len--;
        }

        appendRow(line, len);
    }
}

void appendRow(char *s, size_t len) {
    ds.row = realloc(ds.row, sizeof(Row) * (ds.nrows + 1));
    int at = ds.nrows;
    ds.row[at].size = len;
    ds.row[at].chars = malloc(len + 1);
    memcpy(ds.row[at].chars, s, len);
    ds.row[at].chars[len] = '\0';
    ds.nrows++;
}