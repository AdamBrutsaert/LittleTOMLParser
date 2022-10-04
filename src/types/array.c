#include "toml/array.h"

#include <stdlib.h>

#include "toml/variant.h"

struct toml_array {
    size_t capacity;
    size_t length;
    toml_variant_t *variants;
};

toml_array_t *toml_array_create()
{
    toml_array_t *array = malloc(sizeof(toml_array_t));

    array->length = 0;
    array->capacity = 0;
    array->variants = nullptr;

    return array;
}

void toml_array_destroy(toml_array_t *array)
{
    for (size_t i = 0; i < array->length; i++)
        toml_variant_destroy(array->variants[i]);

    free(array->variants);
    free(array);
}

size_t toml_array_get_length(toml_array_t *array)
{
    return array->length;
}

toml_type_t toml_array_get_type(toml_array_t *array, size_t index)
{
    return array->variants[index].type;
}

toml_integer_t toml_array_get_integer(toml_array_t *array, size_t index)
{
    return array->variants[index].as.integer;
}

toml_float_t toml_array_get_float(toml_array_t *array, size_t index)
{
    return array->variants[index].as.floating;
}

toml_string_t toml_array_get_string(toml_array_t *array, size_t index)
{
    return array->variants[index].as.string;
}

toml_boolean_t toml_array_get_boolean(toml_array_t *array, size_t index)
{
    return array->variants[index].as.boolean;
}

toml_array_t *toml_array_get_array(toml_array_t *array, size_t index)
{
    return array->variants[index].as.array;
}

toml_map_t *toml_array_get_map(toml_array_t *array, size_t index)
{
    return array->variants[index].as.map;
}

static inline void reserve_more_if_needed(toml_array_t *array)
{
    if (array->length == array->capacity) {
        array->capacity = array->capacity * 2 + !array->capacity;
        array->variants = realloc(array->variants, array->capacity * sizeof(toml_variant_t));
    }
}

void toml_array_push_integer(toml_array_t *array, toml_integer_t value)
{
    reserve_more_if_needed(array);
    array->variants[array->length++] = toml_variant_create_integer(value);
}

void toml_array_push_float(toml_array_t *array, toml_float_t value)
{
    reserve_more_if_needed(array);
    array->variants[array->length++] = toml_variant_create_float(value);
}

void toml_array_push_string(toml_array_t *array, toml_string_t value)
{
    reserve_more_if_needed(array);
    array->variants[array->length++] = toml_variant_create_string(value);
}

void toml_array_push_boolean(toml_array_t *array, toml_boolean_t value)
{
    reserve_more_if_needed(array);
    array->variants[array->length++] = toml_variant_create_boolean(value);
}

void toml_array_push_array(toml_array_t *array, toml_array_t *value)
{
    reserve_more_if_needed(array);
    array->variants[array->length++] = toml_variant_create_array(value);
}

void toml_array_push_map(toml_array_t *array, toml_map_t *value)
{
    reserve_more_if_needed(array);
    array->variants[array->length++] = toml_variant_create_map(value);
}
