#include "tokenizer/toml_tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

struct toml_tokenizer {
    toml_reader_t reader;
    
    size_t capacity;
    size_t length;
    size_t index;
    toml_token_t *tokens;
};

static void on_whitespace(toml_tokenizer_t tokenizer)
{
    toml_reader_next(tokenizer->reader);
}

static void on_newline(toml_tokenizer_t tokenizer)
{
    toml_tokenizer_push(tokenizer, toml_token_create_newline());
    toml_reader_next(tokenizer->reader);
}

static void on_equal(toml_tokenizer_t tokenizer)
{
    toml_tokenizer_push(tokenizer, toml_token_create_equal());
    toml_reader_next(tokenizer->reader);
}

static void on_double_quote(toml_tokenizer_t tokenizer)
{
    size_t capacity = 8;
    size_t length = 0;
    toml_string_t string = malloc(capacity * sizeof(char));

    string[length++] = toml_reader_next(tokenizer->reader);

    while (!toml_reader_reached_end(tokenizer->reader)) {
        char c = toml_reader_next(tokenizer->reader);

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

    toml_tokenizer_push(tokenizer, toml_token_create_string(string));
}

static void on_default(toml_tokenizer_t tokenizer)
{
    size_t capacity = 8;
    size_t length = 0;
    toml_string_t string = malloc(capacity * sizeof(char));

    while (!toml_reader_reached_end(tokenizer->reader)) {
        char c = toml_reader_peek(tokenizer->reader, 0);

        if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            break;

        if (capacity == length) {
            capacity *= 2;
            string = realloc(string, capacity * sizeof(char));
        }
        string[length++] = c;

        toml_reader_next(tokenizer->reader);
    }

    if (capacity == length) {
        capacity++;
        string = realloc(string, capacity * sizeof(char));
    }
    string[length++] = '\0';

    toml_tokenizer_push(tokenizer, toml_token_create_string(string));
}

static void tokenize_some(toml_tokenizer_t tokenizer)
{
    tokenizer->length = 0;
    tokenizer->index = 0;

    while (tokenizer->length < tokenizer->capacity) {
        if (toml_reader_reached_end(tokenizer->reader)) {
            toml_tokenizer_push(tokenizer, toml_token_create_end_of_file());
            return;
        }

        switch(toml_reader_peek(tokenizer->reader, 0)) {
            case '\t':
            case '\r':
            case ' ':
                on_whitespace(tokenizer);
                break;

            case '\n':
                on_newline(tokenizer);
                break;

            case '=':
                on_equal(tokenizer);
                break;
            
            case '"':
                on_double_quote(tokenizer);
                break;
                
            default:
                on_default(tokenizer);
        }
    }
}

toml_tokenizer_t toml_tokenizer_create(toml_reader_t reader)
{
    toml_tokenizer_t tokenizer = malloc(sizeof(struct toml_tokenizer));

    tokenizer->reader = reader;
    tokenizer->capacity = 8;
    tokenizer->length = 0;
    tokenizer->index = 0;
    tokenizer->tokens = malloc(tokenizer->capacity * sizeof(toml_token_t));
    return tokenizer;
}

void toml_tokenizer_destroy(toml_tokenizer_t tokenizer)
{
    free(tokenizer->tokens);
    free(tokenizer);
}

void toml_tokenizer_push(toml_tokenizer_t tokenizer, toml_token_t token)
{
    if (tokenizer->length == tokenizer->capacity) {
        tokenizer->capacity *= 2;
        tokenizer->tokens = realloc(tokenizer->tokens, tokenizer->capacity * sizeof(toml_token_t));
    }

    tokenizer->tokens[tokenizer->length++] = token;
}

void toml_tokenizer_print_error(toml_tokenizer_t tokenizer, toml_string_t msg)
{
    toml_string_t filename = toml_reader_get_filename(tokenizer->reader);
    size_t line = toml_reader_get_line(tokenizer->reader);
    size_t column = toml_reader_get_column(tokenizer->reader);
    fprintf(stderr, "[%s:%lu:%lu] Error: %s\n", filename, line, column, msg);
}

toml_token_t toml_tokenizer_next(toml_tokenizer_t tokenizer)
{
    if (tokenizer->index == tokenizer->length)
        tokenize_some(tokenizer);

    return tokenizer->tokens[tokenizer->index++];
}
