#pragma once

typedef enum {
    TOML_TOKEN_TYPE_NONE,
    TOML_TOKEN_TYPE_STRING,
    TOML_TOKEN_TYPE_EQUAL,
    TOML_TOKEN_TYPE_DOT,
    TOML_TOKEN_TYPE_COMMA,
    TOML_TOKEN_TYPE_LBRACKET,
    TOML_TOKEN_TYPE_RBRACKET,
    TOML_TOKEN_TYPE_LBRACE,
    TOML_TOKEN_TYPE_RBRACE,
    TOML_TOKEN_TYPE_NEWLINE,
} toml_token_type_t;

typedef struct {
    toml_token_type_t type;
    char *buffer;
} toml_token_t;


toml_token_t toml_token_create_none();
toml_token_t toml_token_create_string(char *buffer);
toml_token_t toml_token_create_equal();
toml_token_t toml_token_create_dot();
toml_token_t toml_token_create_comma();
toml_token_t toml_token_create_lbracket();
toml_token_t toml_token_create_rbracket();
toml_token_t toml_token_create_lbrace();
toml_token_t toml_token_create_rbrace();
toml_token_t toml_token_create_newline();
void toml_token_destroy(toml_token_t token);

// debug
void toml_token_print(toml_token_t token);
