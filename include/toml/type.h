#pragma once

#include <stddef.h>

#define nullptr NULL
#define true 1
#define false 0

typedef enum {
    TOML_TYPE_INTEGER,
    TOML_TYPE_FLOAT,
    TOML_TYPE_STRING,
    TOML_TYPE_BOOLEAN,
    TOML_TYPE_ARRAY,
    TOML_TYPE_MAP,
} toml_type_t;

typedef long long toml_integer_t;
typedef double toml_float_t;
typedef char *toml_string_t;
typedef char toml_boolean_t;
typedef struct toml_array toml_array_t;
typedef struct toml_map toml_map_t; 
