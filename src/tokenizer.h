#include <stddef.h> 

typedef enum TokenType {
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  IDENTIFIER, STRING, NUMBER,

  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  EOFILE
} TokenType;


char *token_type_to_string(TokenType type);

typedef struct Str Str;

typedef struct Num Num;

typedef struct Identifier Identifier;

typedef struct Str {
  char tag; 
  char *lexeme;
  char *literal;
} Str;

typedef struct Num {
  char tag;
  char *lexeme;
  int value;
} Num;

typedef struct Identifier {
  char tag;
  char *lexeme;
} Identifier;

typedef struct Eof {
  char tag;
  char *lexeme;
} Eof;

typedef struct Token {
  TokenType type;
  union {
    struct Str str_variant;
    struct Num num_variant;
    struct Identifier id_variant;
  } value;

  char *lexeme;
  char *literal;
  int line;

} Token;

typedef struct Scanner {
  const char *source;
  size_t start;
  size_t current;
  int line;
  Token *tokens;
  size_t tokens_size;
  size_t tokens_capacity;
} Scanner;


void scanner_init(Scanner *scanner, const char *source);

void *scanner_malloc(size_t size);

void scanner_tokens_init(Scanner *scanner, size_t capacity);

void scanner_free(Scanner *scanner);

void scanner_scan_tokens(Scanner *scanner);
