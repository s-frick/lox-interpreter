#include "tokenizer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_contents(const char *filename);

int main(int argc, char *argv[]) {
  int exit_code = 0;

  // Disable output buffering
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  if (argc < 3) {
    fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
    return 1;
  }

  const char *command = argv[1];

  if (strcmp(command, "tokenize") == 0) {
    char *file_contents = read_file_contents(argv[2]);

    if (strlen(file_contents) > 0) {
      Scanner *scanner = (Scanner *)scanner_malloc(sizeof(Scanner));

      scanner_init(scanner, file_contents);

      scanner_scan_tokens(scanner);

      for (size_t i = 0; i < scanner->tokens_size; i++) {
        Token *token = &scanner->tokens[i];

        // Check if `lexeme` is NULL
        const char *lexeme = (token->lexeme) ? token->lexeme : "null";
        const char *literal = (token->literal) ? token->literal : "null";

        fprintf(stdout, "%s %s %s\n", token_type_to_string(token->type), lexeme,
                literal);
      }

      if (scanner->error != 0) {
        exit_code = scanner->error;
      }

      scanner_free(scanner);
      free(scanner);
    } else {
      Token *tok = Token_new_eof(1);
      const char *lexeme = (tok->lexeme) ? tok->lexeme : "null";
      const char *literal = (tok->literal) ? tok->literal : "null";
      printf("%s %s %s\n", token_type_to_string(tok->type), lexeme, literal);
      if (tok->lexeme) {
        free((char *)tok->lexeme);
        tok->lexeme = NULL;
      }
      if (tok->literal) {
        free((char *)tok->literal);
        tok->literal = NULL;
      }
      free(tok);
    }

    free(file_contents);
    exit(exit_code);
  } else {
    fprintf(stderr, "Unknown command: %s\n", command);
    return 1;
  }

  return exit_code;
}

char *read_file_contents(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error reading file: %s\n", filename);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *file_contents = malloc(file_size + 1);
  if (file_contents == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(file_contents, 1, file_size, file);
  if (bytes_read < file_size) {
    fprintf(stderr, "Error reading file contents\n");
    free(file_contents);
    fclose(file);
    return NULL;
  }

  file_contents[file_size] = '\0';
  fclose(file);

  return file_contents;
}
