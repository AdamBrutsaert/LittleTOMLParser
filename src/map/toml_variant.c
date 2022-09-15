#include "map/toml_variant.h"

#include <stdlib.h>

toml_variant_t toml_variant_create_integer(toml_integer_t value)
{
    return (toml_variant_t) {
        .type = TOML_VARIANT_TYPE_INTEGER,
        .as.integer = value,
    };
}

toml_variant_t toml_variant_create_float(toml_float_t value)
{
    return (toml_variant_t) {
        .type = TOML_VARIANT_TYPE_FLOAT,
        .as.floating = value,
    };
}

toml_variant_t toml_variant_create_boolean(toml_boolean_t value)
{
    return (toml_variant_t) {
        .type = TOML_VARIANT_TYPE_BOOLEAN,
        .as.boolean = value,
    };
}

toml_variant_t toml_variant_create_string(toml_string_t value)
{
    return (toml_variant_t) {
        .type = TOML_VARIANT_TYPE_STRING,
        .as.string = value,
    };
}

toml_variant_t toml_variant_create_array()
{
    return (toml_variant_t) {
        .type = TOML_VARIANT_TYPE_ARRAY,
        .as.array = nullptr, // TODO implement this
    };
}

toml_variant_t toml_variant_create_map()
{
    return (toml_variant_t) {
        .type = TOML_VARIANT_TYPE_MAP,
        .as.map = nullptr, // TODO implement this
    };
}

void toml_variant_destroy(toml_variant_t variant)
{
    if (variant.type == TOML_VARIANT_TYPE_STRING) {
        free(variant.as.string);
    } else if (variant.type == TOML_VARIANT_TYPE_ARRAY) {
        // TODO destroy array
    } else if (variant.type == TOML_VARIANT_TYPE_MAP) {
        // TODO destroy map
    }
}
