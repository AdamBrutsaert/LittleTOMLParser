#pragma once

#include "map/toml_type.h"

typedef enum {
    TOML_TOKEN_TYPE_KEY,
    TOML_TOKEN_TYPE_SET,
    TOML_TOKEN_TYPE_NUMERIC,
    TOML_TOKEN_TYPE_BOOLEAN,
    TOML_TOKEN_TYPE_STRING,
    TOML_TOKEN_TYPE_END_OF_STATEMENT,
    TOML_TOKEN_TYPE_END_OF_FILE,
} toml_token_type_t;

typedef struct {
    toml_token_type_t type;
    toml_string_t buffer;
} toml_token_t;

toml_token_t toml_token_create_key(toml_string_t buffer);
toml_token_t toml_token_create_set();
toml_token_t toml_token_create_numeric(toml_string_t buffer);
toml_token_t toml_token_create_boolean(toml_string_t buffer);
toml_token_t toml_token_create_string(toml_string_t buffer);
toml_token_t toml_token_create_end_of_statement();
toml_token_t toml_token_create_end_of_file();

// debug
void toml_token_print(toml_token_t token);
