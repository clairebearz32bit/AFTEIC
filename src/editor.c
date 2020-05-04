#include "../include.h"

void Open(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        raise("fopen");
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t len;
    len = getline(&line, &cap, fp);

    if(len != -1) {
        while(len > 0 && (line[len - 1] == '\n' || line[len] == '\r')) {
            len--;
        }

        ds.row.size = len;
        ds.row.chars = malloc(len + 1);
        memcpy(ds.row.chars, line, len);
        ds.row.chars[len] = '\0';
        ds.nrows = 1;

    }
    free(line);
    fclose(fp);
}