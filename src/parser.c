#include "../include/parser/parser.h"

string_t get_line() {
  string_t buf = NULL;
  int ch;
  int sz = 0;
  int pos = 0;

  while ((ch = getchar()) != EOF && ch != '\n') {
    if (pos + 1 >= sz) {
      sz = sz * 2 + 1;
      buf = (string_t) realloc(buf, sizeof(char) * sz);
    }

    buf[pos++] = ch;
  }

  sz = pos + 1;
  buf = (string_t) realloc(buf, sizeof(char) * sz);
  buf[pos] = '\0';

  return buf;
}
