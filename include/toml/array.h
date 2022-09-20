#pragma once

#include "type.h"

toml_array_t toml_array_create();
void toml_array_destroy(toml_array_t array);

size_t toml_array_get_length(toml_array_t array);
toml_type_t toml_array_get_type(toml_array_t array, size_t index);

toml_map_t toml_array_get_map(toml_array_t array, size_t index);
toml_array_t toml_array_get_array(toml_array_t array, size_t index);
toml_integer_t toml_array_get_integer(toml_array_t array, size_t index);
toml_float_t toml_array_get_float(toml_array_t array, size_t index);
toml_boolean_t toml_array_get_boolean(toml_array_t array, size_t index);
toml_string_t toml_array_get_string(toml_array_t array, size_t index);

void toml_array_push_map(toml_array_t array, toml_map_t value);
void toml_array_push_array(toml_array_t array, toml_array_t value);
void toml_array_push_integer(toml_array_t array, toml_integer_t value);
void toml_array_push_float(toml_array_t array, toml_float_t value);
void toml_array_push_boolean(toml_array_t array, toml_boolean_t value);
void toml_array_push_string(toml_array_t array, toml_string_t value);
