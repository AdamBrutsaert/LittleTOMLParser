#include "toml/tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

#include "utils/my_lib.h"

struct toml_tokenizer {
    toml_reader_t reader;
    toml_boolean_t reached_end;
    
    size_t capacity;
    size_t length;
    size_t index;
    toml_token_t *tokens;
};

static toml_boolean_t will_reach_end(toml_tokenizer_t tokenizer, size_t offset)
{
    return tokenizer->length != tokenizer->capacity && tokenizer->index + offset >= tokenizer->length;
}

static void push_token(toml_tokenizer_t tokenizer, toml_token_t token)
{
    tokenizer->tokens[tokenizer->length++] = token;
}

static void on_whitespace(toml_tokenizer_t tokenizer)
{
    toml_reader_next(tokenizer->reader);
}

static void on_newline(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_newline());
    toml_reader_next(tokenizer->reader);
}

static void on_equal(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_equal());
    toml_reader_next(tokenizer->reader);
}

static void on_double_quote(toml_tokenizer_t tokenizer)
{
    // TODO handle triple quote 
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

    push_token(tokenizer, toml_token_create_string(string));
}

static void on_comma(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_comma());
    toml_reader_next(tokenizer->reader);
}

static void on_dot(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_dot());
    toml_reader_next(tokenizer->reader);
}

static void on_lbracket(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_lbracket());
    toml_reader_next(tokenizer->reader);
}

static void on_rbracket(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_rbracket());
    toml_reader_next(tokenizer->reader);
}

static void on_lbrace(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_lbrace());
    toml_reader_next(tokenizer->reader);
}

static void on_rbrace(toml_tokenizer_t tokenizer)
{
    push_token(tokenizer, toml_token_create_rbrace());
    toml_reader_next(tokenizer->reader);
}

static void on_default(toml_tokenizer_t tokenizer)
{
    size_t capacity = 8;
    size_t length = 0;
    toml_string_t string = malloc(capacity * sizeof(char));

    while (!toml_reader_reached_end(tokenizer->reader)) {
        char c = toml_reader_peek(tokenizer->reader, 0);

        if (c == ' ' || c == '\t' || c == '\r' || c == '\n'
            || c == ',' || c == '.' || c == '[' || c == ']'
            || c == '{' || c == '}')
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

    push_token(tokenizer, toml_token_create_string(string));
}

static void tokenize_some(toml_tokenizer_t tokenizer, size_t offset)
{
    tokenizer->length = offset;
    tokenizer->index = 0;

    while (!toml_reader_reached_end(tokenizer->reader) && tokenizer->length < tokenizer->capacity) {
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

            case '.':
                on_dot(tokenizer);
                break;
                
            case ',':
                on_comma(tokenizer);
                break;

            case '[':
                on_lbracket(tokenizer);
                break;

            case ']':
                on_rbracket(tokenizer);
                break;

            case '{':
                on_lbrace(tokenizer);
                break;

            case '}':
                on_rbrace(tokenizer);
                break;
                
            default:
                on_default(tokenizer);
        }
    }

    tokenizer->reached_end = will_reach_end(tokenizer, 0);
}

toml_tokenizer_t toml_tokenizer_create(toml_reader_t reader)
{
    toml_tokenizer_t tokenizer = malloc(sizeof(struct toml_tokenizer));

    tokenizer->reader = reader;
    tokenizer->reached_end = false;
    tokenizer->capacity = 8;
    tokenizer->length = 0;
    tokenizer->index = 0;
    tokenizer->tokens = malloc(tokenizer->capacity * sizeof(toml_token_t));
    tokenize_some(tokenizer, 0);
    return tokenizer;
}

void toml_tokenizer_destroy(toml_tokenizer_t tokenizer)
{
    free(tokenizer->tokens);
    free(tokenizer);
}

toml_boolean_t toml_tokenizer_reached_end(toml_tokenizer_t tokenizer)
{
    return tokenizer->reached_end;
}

toml_token_t toml_tokenizer_next(toml_tokenizer_t tokenizer)
{
    if (tokenizer->reached_end)
        return toml_token_create_none();

    toml_token_t token = tokenizer->tokens[tokenizer->index++];
    tokenizer->reached_end = will_reach_end(tokenizer, 0);

    if (tokenizer->index == tokenizer->length)
        tokenize_some(tokenizer, 0);

    return token;
}

toml_token_t toml_tokenizer_peek(toml_tokenizer_t tokenizer, size_t offset)
{
    if (offset >= tokenizer->capacity || will_reach_end(tokenizer, offset))
        return toml_token_create_none();

    if (tokenizer->index + offset >= tokenizer->capacity) {
        my_memmove(tokenizer->tokens, &tokenizer->tokens[tokenizer->index], 
                   (tokenizer->capacity - tokenizer->index) * sizeof(toml_token_t));
        tokenize_some(tokenizer, tokenizer->capacity - tokenizer->index);
    }

    return tokenizer->tokens[tokenizer->index + offset];
}
