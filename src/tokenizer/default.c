#include "toml/tokenizer.h"

#include <stdlib.h>

void toml_tokenizer_on_default(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer)
{
    size_t line = toml_file_reader_get_line(file_reader);
    size_t column = toml_file_reader_get_column(file_reader);

    size_t capacity = 8;
    size_t length = 0;
    toml_string_t string = malloc(capacity * sizeof(char));
    
    char c = toml_file_reader_peek(file_reader, 0);
    toml_boolean_t is_number = c >= '0' && c <= '9';

    while (!toml_file_reader_end(file_reader)) {
        c = toml_file_reader_peek(file_reader, 0);

        if (c == ' ' || c == '\t' || c == '\r' || c == '\n'
            || c == ',' || c == '[' || c == ']'
            || c == '{' || c == '}' || c == '#')
            break;
        
        if (!is_number && c == '.')
            break;

        if (capacity == length) {
            capacity *= 2;
            string = realloc(string, capacity * sizeof(char));
        }
        string[length++] = c;

        toml_file_reader_next(file_reader);
    }

    if (capacity == length) {
        capacity++;
        string = realloc(string, capacity * sizeof(char));
    }
    string[length++] = '\0';

    toml_tokenizer_push(tokenizer, toml_token_create_string(string, line, column));
}
