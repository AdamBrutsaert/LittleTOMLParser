#include "tokenizer/toml_token.h"

toml_token_t toml_token_create_key(toml_string_t buffer)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_KEY,
        .buffer = buffer
    };
}

toml_token_t toml_token_create_set()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_SET,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_numeric(toml_string_t buffer)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_NUMERIC,
        .buffer = buffer
    };
}

toml_token_t toml_token_create_boolean(toml_string_t buffer)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_BOOLEAN,
        .buffer = buffer
    };
}

toml_token_t toml_token_create_string(toml_string_t buffer)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_STRING,
        .buffer = buffer
    };
}

toml_token_t toml_token_create_end_of_statement()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_END_OF_STATEMENT,
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

// debug
#include <stdio.h>

void toml_token_print(toml_token_t token)
{
    switch (token.type) {
        case TOML_TOKEN_TYPE_KEY:
            printf("KEY\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_SET:
            puts("SET");
            break;
        case TOML_TOKEN_TYPE_NUMERIC:
            printf("NUMERIC\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_BOOLEAN:
            printf("BOOLEAN\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_STRING:
            printf("STRING\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_END_OF_STATEMENT:
            puts("END_OF_STATEMENT");
            break;
        case TOML_TOKEN_TYPE_END_OF_FILE:
            puts("END_OF_FILE");
            break;
    }
}
