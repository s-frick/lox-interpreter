#include <stddef.h>

typedef enum TokenType {
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  IDENTIFIER,
  STRING,
  NUMBER,

  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  EOFILE
} TokenType;

char *token_type_to_string(TokenType type);

typedef struct Token {
  TokenType type;

  const char *lexeme;
  const char *literal;
  int line;

} Token;

typedef struct Scanner {
  const char *source;
  size_t start;
  size_t current;
  size_t line;
  Token *tokens;
  size_t tokens_size;
  size_t tokens_capacity;
  int error;
} Scanner;

Token *Token_new_eof(int line);

void scanner_init(Scanner *scanner, const char *source);

void *scanner_malloc(size_t size);

void scanner_tokens_init(Scanner *scanner, size_t capacity);

void scanner_free(Scanner *scanner);

void scanner_scan_tokens(Scanner *scanner);
