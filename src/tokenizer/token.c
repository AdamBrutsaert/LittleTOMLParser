#include "toml/token.h"

#include <stdlib.h>

#include "toml/type.h"

toml_token_t toml_token_create_none()
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_NONE,
        .buffer = nullptr,
        .line = 0,
        .column = 0,
    };
}

toml_token_t toml_token_create_string(char *buffer, size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_STRING,
        .buffer = buffer,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_equal(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_EQUAL,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_dot(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_DOT,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_comma(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_COMMA,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_lbracket(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_LBRACKET,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_rbracket(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_RBRACKET,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_lbrace(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_LBRACE,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_rbrace(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_RBRACE,
        .buffer = nullptr,
        .line = line,
        .column = column
    };
}

toml_token_t toml_token_create_newline(size_t line, size_t column)
{
    return (toml_token_t) {
        .type = TOML_TOKEN_TYPE_NEWLINE,
        .buffer = nullptr,
        .line = line,
        .column = column
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
    printf("[%02lu:%02lu] ", token.line, token.column);

    switch (token.type) {
        case TOML_TOKEN_TYPE_NONE:
            fputs("NONE\n", stdout);
            break;
        case TOML_TOKEN_TYPE_EQUAL:
            fputs("EQUAL\t\t\t=\n", stdout);
            break;
        case TOML_TOKEN_TYPE_STRING:
            printf("STRING\t\t\t%s\n", token.buffer);
            break;
        case TOML_TOKEN_TYPE_DOT:
            fputs("DOT\t\t\t.\n", stdout);
            break;
        case TOML_TOKEN_TYPE_COMMA:
            fputs("COMMA\t\t\t,\n", stdout);
            break;
        case TOML_TOKEN_TYPE_LBRACKET:
            fputs("LBRACKET\t\t[\n", stdout);
            break;
        case TOML_TOKEN_TYPE_RBRACKET:
            fputs("RBRACKET\t\t]\n", stdout);
            break;
        case TOML_TOKEN_TYPE_LBRACE:
            fputs("LBRACE\t\t\t{\n", stdout);
            break;
        case TOML_TOKEN_TYPE_RBRACE:
            fputs("RBRACE\t\t\t}\n", stdout);
            break;
        case TOML_TOKEN_TYPE_NEWLINE:
            fputs("NEWLINE\n", stdout);
            break;
    }
}
