#include "toml/variant.h"

#include <stdlib.h>

#include "toml/map.h"
#include "toml/array.h"

toml_variant_t toml_variant_create_integer(toml_integer_t value)
{
    return (toml_variant_t) {
        .type = TOML_TYPE_INTEGER,
        .as.integer = value,
    };
}

toml_variant_t toml_variant_create_float(toml_float_t value)
{
    return (toml_variant_t) {
        .type = TOML_TYPE_FLOAT,
        .as.floating = value,
    };
}

toml_variant_t toml_variant_create_string(toml_string_t value)
{
    return (toml_variant_t) {
        .type = TOML_TYPE_STRING,
        .as.string = value,
    };
}

toml_variant_t toml_variant_create_boolean(toml_boolean_t value)
{
    return (toml_variant_t) {
        .type = TOML_TYPE_BOOLEAN,
        .as.boolean = value,
    };
}

toml_variant_t toml_variant_create_array(toml_array_t *value)
{
    return (toml_variant_t) {
        .type = TOML_TYPE_ARRAY,
        .as.array = value,
    };
}

toml_variant_t toml_variant_create_map(toml_map_t *value)
{
    return (toml_variant_t) {
        .type = TOML_TYPE_MAP,
        .as.map = value,
    };
}

void toml_variant_destroy(toml_variant_t variant)
{
    if (variant.type == TOML_TYPE_MAP)
        toml_map_destroy(variant.as.map);
    else if (variant.type == TOML_TYPE_ARRAY)
        toml_array_destroy(variant.as.array);
    else if (variant.type == TOML_TYPE_STRING)
        free(variant.as.string);
}
