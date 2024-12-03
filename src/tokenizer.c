#include <stddef.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

#define SCANNER_IMPLEMENTATION

char *token_type_to_string(TokenType type) {
  switch (type) {
      case LEFT_PAREN: return "LEFT_PAREN";
      case RIGHT_PAREN: return "RIGHT_PAREN";
      case LEFT_BRACE: return "LEFT_BRACE";
      case RIGHT_BRACE: return "RIGHT_BRACE";
      case COMMA: return "COMMA";
      case DOT: return "DOT";
      case MINUS: return "MINUS";
      case PLUS: return "PLUS";
      case SEMICOLON: return "SEMICOLON";
      case SLASH: return "SLASH";
      case STAR: return "STAR";

      case BANG: return "BANG";
      case BANG_EQUAL: return "BANG_EQUAL";
      case EQUAL: return "EQUAL";
      case EQUAL_EQUAL: return "EQUAL_EQUAL";
      case GREATER: return "GREATER";
      case GREATER_EQUAL: return "GREATER_EQUAL";
      case LESS: return "LESS";
      case LESS_EQUAL: return "LESS_EQUAL";

      case IDENTIFIER: return "IDENTIFIER";
      case STRING: return "STRING";
      case NUMBER: return "NUMBER";

      case AND: return "AND";
      case CLASS: return "CLASS";
      case ELSE: return "ELSE";
      case FALSE: return "FALSE";
      case FUN: return "FUN";
      case FOR: return "FOR";
      case IF: return "IF";
      case NIL: return "NIL";
      case OR: return "OR";
      case PRINT: return "PRINT";
      case RETURN: return "RETURN";
      case SUPER: return "SUPER";
      case THIS: return "THIS";
      case TRUE: return "TRUE";
      case VAR: return "VAR";
      case WHILE: return "WHILE";

      case EOFILE: return "EOF";

      default: return "UNKNOWN";
  }
}

Token *Token_new(TokenType type, char *lexeme, char *literal, int line) {
  Token *token = (Token*)malloc(sizeof(Token));
  token->type = type;
  token->line = line;
  token->lexeme = lexeme;
  token->literal = literal;
  return token;
}

Token *Token_new_eof(int line) {
  return Token_new(EOFILE, "", NULL, line);
}

void scanner_init(Scanner *scanner, const char *source) {
  scanner->source = source;
  scanner->start = scanner->current = 0;
  scanner->line = 1;
  scanner_tokens_init(scanner, 20);
}

void *scanner_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "[ERROR] Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *scanner_realloc(void *ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "[ERROR] Unable to reallocate memory to %zu bytes.\n", size);
        free(ptr); // Free the old memory to prevent a leak
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

void scanner_tokens_init(Scanner *scanner, size_t capacity) {
    if (capacity == 0) {
        capacity = 8; // Default initial capacity
    }

    scanner->tokens = scanner_malloc(capacity * sizeof(Token));
    scanner->tokens_capacity = capacity;
    scanner->tokens_size = 0;

    // fprintf(stdout, "[INFO] Successfully initialized tokens array\n");
}

void scanner_free(Scanner *scanner) {
  // TODO: Free allocated tokens, e.g. lexeme etc
  free(scanner->tokens);
  scanner->tokens = NULL;
  scanner->tokens_capacity = 0;
  scanner->tokens_size = 0;
}

int is_at_end(Scanner *scanner) {
  return scanner->current >= strlen(scanner->source);
}

void scanner_scan_token(Scanner *scanner) {
  scanner->current++;
}

void scanner_add_token(Scanner *scanner, Token *token) {
    if (scanner->tokens_size >= scanner->tokens_capacity) {
        if (scanner->tokens_capacity == 0) {
            scanner->tokens_capacity = 8; // Start with a small non-zero capacity
        } else {
            scanner->tokens_capacity *= 2; // Double the capacity
        }

        scanner->tokens = scanner_realloc(scanner->tokens, scanner->tokens_capacity * sizeof(Token));
    }

    // Safely add the token
    scanner->tokens[scanner->tokens_size++] = *token;
}


void scanner_scan_tokens(Scanner *scanner) {
  while (!is_at_end(scanner)) {
    scanner->start = scanner->current;
    scanner_scan_token(scanner);
  }
  scanner_add_token(scanner, Token_new_eof(scanner->line));
}


