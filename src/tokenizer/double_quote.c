#include "toml/tokenizer.h"

#include <stdlib.h>

void toml_tokenizer_on_double_quote(toml_file_reader_t *file_reader, toml_tokenizer_t *tokenizer)
{
    // TODO handle triple quote 
    size_t line = toml_file_reader_get_line(file_reader);
    size_t column = toml_file_reader_get_column(file_reader);

    size_t capacity = 8;
    size_t length = 0;
    toml_string_t string = malloc(capacity * sizeof(char));

    string[length++] = toml_file_reader_next(file_reader);

    while (!toml_file_reader_end(file_reader)) {
        char c = toml_file_reader_next(file_reader);

        if (capacity == length) {
            capacity *= 2;
            string = realloc(string, capacity * sizeof(char));
        }
        string[length++] = c;

        if (c == '"')
            break;
    }

    if (capacity == length) {
        capacity++;
        string = realloc(string, capacity * sizeof(char));
    }
    string[length++] = '\0';

    toml_tokenizer_push(tokenizer, toml_token_create_string(string, line, column));
}
