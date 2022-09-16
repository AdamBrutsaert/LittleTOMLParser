#include "tokenizer/toml_tokenizer.h"

#include <stdlib.h>

#include "tokenizer/toml_state.h"

struct toml_tokenizer {
    toml_reader_t reader;
    
    size_t capacity;
    size_t length;
    size_t index;
    toml_token_t *tokens;
};

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

toml_token_t toml_tokenizer_next(toml_tokenizer_t tokenizer)
{
    // TODO call tokenize some if needed

    return tokenizer->tokens[tokenizer->index++];
}
