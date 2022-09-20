#pragma once

#include "map/toml_type.h"

typedef enum {
    TOML_TOKEN_TYPE_EQUAL,
    TOML_TOKEN_TYPE_STRING,
    TOML_TOKEN_TYPE_NEWLINE,
    TOML_TOKEN_TYPE_END_OF_FILE,
} toml_token_type_t;

typedef struct {
    toml_token_type_t type;
    toml_string_t buffer;
} toml_token_t;

toml_token_t toml_token_create_equal();
toml_token_t toml_token_create_string(toml_string_t buffer);
toml_token_t toml_token_create_newline();
toml_token_t toml_token_create_end_of_file();
void toml_token_destroy(toml_token_t token);

// debug
void toml_token_print(toml_token_t token);
