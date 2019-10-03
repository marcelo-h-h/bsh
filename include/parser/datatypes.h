#ifndef PARSER_DATATYPES
#define PARSER_DATATYPES

#define FORK_STR "&"

typedef char* string_t;

typedef enum {
  TRUE,
  FALSE
} bool_t;

typedef enum {
  EXEC,
  FORK
} cmd_type_t;

typedef struct {
  cmd_type_t   type;
} cmd_t;

typedef struct {
  cmd_type_t  type;
  string_t*   argv;
} exec_cmd_t;

typedef struct {
  cmd_type_t  type;
  cmd_t*      left;
} fork_cmd_t;

#endif