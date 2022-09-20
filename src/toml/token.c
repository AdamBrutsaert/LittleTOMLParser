#include "toml/token.h"

#include <stdlib.h>

#include "toml/type.h"

toml_token_t toml_token_create_string(char *buffer)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_STRING,
        .buffer = buffer
    };
}

toml_token_t toml_token_create_equal()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_EQUAL,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_dot()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_DOT,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_comma()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_COMMA,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_lbracket()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_LBRACKET,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_rbracket()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_RBRACKET,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_lbrace()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_LBRACE,
        .buffer = nullptr
    };
}

toml_token_t toml_token_create_rbrace()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_RBRACE,
        .buffer = nullptr
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
        case TOML_TOKEN_TYPE_DOT:
            puts("DOT");
            break;
        case TOML_TOKEN_TYPE_COMMA:
            puts("COMMA");
            break;
        case TOML_TOKEN_TYPE_LBRACKET:
            puts("LBRACKET");
            break;
        case TOML_TOKEN_TYPE_RBRACKET:
            puts("RBRACKET");
            break;
        case TOML_TOKEN_TYPE_LBRACE:
            puts("LBRACE");
            break;
        case TOML_TOKEN_TYPE_RBRACE:
            puts("RBRACE");
            break;
        case TOML_TOKEN_TYPE_NEWLINE:
            puts("NEWLINE");
            break;
        case TOML_TOKEN_TYPE_END_OF_FILE:
            puts("END_OF_FILE");
            break;
    }
}
