#include "tokenizer/toml_token.h"

toml_token_t toml_token_create_equal()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_EQUAL,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_string(toml_string_t buffer)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_STRING,
        .buffer = buffer
    };
}

toml_token_t toml_token_create_newline()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_NEWLINE,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_end_of_file()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_END_OF_FILE,
        .buffer = nullptr
    };
}

void toml_token_destroy(toml_token_t token)
{
    free(token.buffer);
}

// debug
#include <stdio.h>

void toml_token_print(toml_token_t token)
{
    switch (token.type) {
        case TOML_TOKEN_TYPE_EQUAL:
            puts("EQUAL\t\t\t=");
            break;
        case TOML_TOKEN_TYPE_STRING:
            printf("STRING\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_NEWLINE:
            puts("NEWLINE");
            break;
        case TOML_TOKEN_TYPE_END_OF_FILE:
            puts("END_OF_FILE");
            break;
    }
}
