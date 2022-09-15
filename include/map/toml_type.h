#pragma once

#define nullptr (void*)0
#define true 1
#define false 0

typedef long long toml_integer_t;
typedef double toml_float_t;
typedef char toml_boolean_t;
typedef char *toml_string_t;

typedef struct toml_array *toml_array_t;
typedef struct toml_map *toml_map_t;
