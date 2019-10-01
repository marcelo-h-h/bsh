#include "../include/parser/parser.h"

string_t get_line()
{
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

string_t* split_line(string_t line)
{
  string_t* tokens = NULL;
  string_t token;
  string_t delim = " \0";
  int sz = 0;
  int pos = 0;

  token = strtok(line, delim);

  while (token != NULL) {
    if (pos + 1 >= sz) {
      sz = sz * 2 + 1;
      tokens = (string_t*) realloc(tokens, sizeof(string_t) * sz);
    }

    tokens[pos++] = token;
    token = strtok(NULL, delim);
  }

  sz = pos + 1;
  tokens = (string_t*) realloc(tokens, sizeof(string_t) * sz);
  tokens[pos] = NULL;

  return tokens;
}
