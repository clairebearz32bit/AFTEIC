#ifndef AFTEIC_IOUTILS_H
#define AFTEIC_IOUTILS_H

void raise(const char *s);
void exitRaw();
void enterRaw();
int readKey();
void processKey();
void Append(struct to_write *tw, const char *s, int len);
void Free(struct to_write *tw);

#endif
