#include "toml/tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

#include "toml/memory.h"

struct toml_tokenizer {
    toml_file_reader_t *file_reader;
    toml_boolean_t end;
    
    size_t capacity;
    size_t length;
    size_t index;
    toml_token_t *tokens;
};

static toml_boolean_t will_reach_end(toml_tokenizer_t *tokenizer, size_t n)
{
    toml_boolean_t last_buffer = tokenizer->length != tokenizer->capacity;
    toml_boolean_t last_token = tokenizer->index + n >= tokenizer->length;

    return last_buffer && last_token;
}

static void tokenize(toml_tokenizer_t *tokenizer)
{
    if (tokenizer->end)
        return;
    
    toml_file_reader_t *file_reader = tokenizer->file_reader;
    
    size_t index = tokenizer->index;
    size_t capacity = tokenizer->capacity;
    size_t count = (index != 0) * (capacity - index);

    toml_token_t *tokens = tokenizer->tokens;
    toml_token_t *tokens_pos = &tokenizer->tokens[tokenizer->index];

    toml_memmove(tokens, tokens_pos, count);
    tokenizer->length = count;

    while (!toml_file_reader_end(file_reader) && tokenizer->length < tokenizer->capacity) {
        switch(toml_file_reader_peek(file_reader, 0)) {
            case '#':
                toml_tokenizer_on_comment(file_reader);
                break;

            case '\t':
            case '\r':
            case ' ':
                toml_file_reader_next(file_reader);
                break;

            case '\n':
                toml_tokenizer_on_newline(file_reader, tokenizer);
                break;

            case '=':
                toml_tokenizer_on_equal(file_reader, tokenizer);
                break;
            
            case '.':
                toml_tokenizer_on_dot(file_reader, tokenizer);
                break;
                
            case ',':
                toml_tokenizer_on_comma(file_reader, tokenizer);
                break;

            case '[':
                toml_tokenizer_on_lbracket(file_reader, tokenizer);
                break;

            case ']':
                toml_tokenizer_on_rbracket(file_reader, tokenizer);
                break;

            case '{':
                toml_tokenizer_on_lbrace(file_reader, tokenizer);
                break;

            case '}':
                toml_tokenizer_on_rbrace(file_reader, tokenizer);
                break;

            case '"':
                toml_tokenizer_on_double_quote(file_reader, tokenizer);
                break;

            case '\'':
                toml_tokenizer_on_single_quote(file_reader, tokenizer);
                break;
                
            default:
                toml_tokenizer_on_default(file_reader, tokenizer);
        }
    }

    tokenizer->index = 0;
    tokenizer->end = will_reach_end(tokenizer, 0);
}

toml_tokenizer_t *toml_tokenizer_create(toml_file_reader_t *file_reader, size_t capacity)
{
    toml_tokenizer_t *tokenizer = malloc(sizeof(toml_tokenizer_t));

    tokenizer->file_reader = file_reader;
    tokenizer->end = false;
    
    tokenizer->capacity = capacity;
    tokenizer->length = 0;
    tokenizer->index = 0;
    tokenizer->tokens = malloc(tokenizer->capacity * sizeof(toml_token_t));

    tokenize(tokenizer);

    return tokenizer;
}

void toml_tokenizer_destroy(toml_tokenizer_t *tokenizer)
{
    for (size_t i = tokenizer->index; i < tokenizer->length; i++)
        toml_token_destroy(tokenizer->tokens[i]);

    free(tokenizer->tokens);
    free(tokenizer);
}

toml_token_t toml_tokenizer_next(toml_tokenizer_t *tokenizer)
{
    if (tokenizer->end)
        return toml_token_create_none();
    
    toml_token_t token = tokenizer->tokens[tokenizer->index];
    tokenizer->index++;
    tokenizer->end = will_reach_end(tokenizer, 0);
    
    if (tokenizer->index == tokenizer->length)
        tokenize(tokenizer);

    return token;
}

toml_token_t toml_tokenizer_peek(toml_tokenizer_t *tokenizer, size_t n)
{
    if (n >= tokenizer->capacity || will_reach_end(tokenizer, n))
        return toml_token_create_none();

    if (tokenizer->index + n >= tokenizer->capacity)
        tokenize(tokenizer);

    return tokenizer->tokens[tokenizer->index + n];
}

toml_boolean_t toml_tokenizer_end(toml_tokenizer_t *tokenizer)
{
    return tokenizer->end;
}

void toml_tokenizer_push(toml_tokenizer_t *tokenizer, toml_token_t token)
{
    tokenizer->tokens[tokenizer->length] = token;
    tokenizer->length++;
}
