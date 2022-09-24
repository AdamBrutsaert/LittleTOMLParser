#include "toml/token.h"

#include <stdlib.h>

#include "toml/type.h"

toml_token_t toml_token_create_none()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_NONE,
        .buffer = nullptr
    };
}

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

void toml_token_destroy(toml_token_t token)
{
    free(token.buffer);
}

// debug
#include <stdio.h>

void toml_token_print(toml_token_t token)
{
    switch (token.type) {
        case TOML_TOKEN_TYPE_NONE:
            puts("NONE");
            break;
        case TOML_TOKEN_TYPE_EQUAL:
            puts("EQUAL\t\t\t=");
            break;
        case TOML_TOKEN_TYPE_STRING:
            printf("STRING\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_DOT:
            puts("DOT\t\t\t.");
            break;
        case TOML_TOKEN_TYPE_COMMA:
            puts("COMMA\t\t\t,");
            break;
        case TOML_TOKEN_TYPE_LBRACKET:
            puts("LBRACKET\t\t[");
            break;
        case TOML_TOKEN_TYPE_RBRACKET:
            puts("RBRACKET\t\t]");
            break;
        case TOML_TOKEN_TYPE_LBRACE:
            puts("LBRACE\t\t\t{");
            break;
        case TOML_TOKEN_TYPE_RBRACE:
            puts("RBRACE\t\t\t}");
            break;
        case TOML_TOKEN_TYPE_NEWLINE:
            puts("NEWLINE");
            break;
    }
}
