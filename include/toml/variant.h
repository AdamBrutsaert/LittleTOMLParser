#pragma once

#include "type.h"

typedef struct {
    toml_type_t type;

    union {
        toml_integer_t integer;
        toml_float_t floating;
        toml_string_t string;
        toml_boolean_t boolean;
        toml_array_t *array;
        toml_map_t *map;
    } as;
} toml_variant_t;

toml_variant_t toml_variant_create_integer(toml_integer_t value);
toml_variant_t toml_variant_create_float(toml_float_t value);
toml_variant_t toml_variant_create_string(toml_string_t value);
toml_variant_t toml_variant_create_boolean(toml_boolean_t value);
toml_variant_t toml_variant_create_array(toml_array_t *value);
toml_variant_t toml_variant_create_map(toml_map_t *value);
void toml_variant_destroy(toml_variant_t variant);
