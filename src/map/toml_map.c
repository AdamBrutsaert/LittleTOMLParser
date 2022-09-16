#include "map/toml_map.h"

#include <stdlib.h>

#include "map/toml_variant.h"
#include "utils/my_lib.h"

typedef struct node {
    toml_string_t key;
    toml_variant_t variant;
    struct node *next;
} node_t;

struct toml_map {
    size_t capacity;
    node_t **nodes;
};

toml_map_t toml_map_create()
{
    toml_map_t map = malloc(sizeof(struct toml_map));

    map->capacity = 64;
    map->nodes = malloc(map->capacity * sizeof(node_t*));
    my_memset(map->nodes, 0, map->capacity * sizeof(node_t*));
    return map;
}

void toml_map_destroy(toml_map_t map)
{
    for (size_t i = 0; i < map->capacity; i++) {
        node_t *node = map->nodes[i];
        while (node) {
            node_t *next = node->next;
            free(node->key);
            toml_variant_destroy(node->variant);
            free(node);
            node = next;
        }
    }

    free(map->nodes);
    free(map);
}

void toml_map_set_integer(toml_map_t map, toml_string_t key, toml_integer_t value)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != nullptr; node = node->next) {
        if (!my_strcmp(node->key, key)) {
            toml_variant_destroy(node->variant);
            node->variant = toml_variant_create_integer(value);
            return;
        }
    }
    node_t *node = malloc(sizeof(node_t));
    node->key = my_strdup(key);
    node->variant = toml_variant_create_integer(value);
    node->next = map->nodes[index];
    map->nodes[index] = node; 
}

void toml_map_set_float(toml_map_t map, toml_string_t key, toml_float_t value)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != nullptr; node = node->next) {
        if (!my_strcmp(node->key, key)) {
            toml_variant_destroy(node->variant);
            node->variant = toml_variant_create_float(value);
            return;
        }
    }
    node_t *node = malloc(sizeof(node_t));
    node->key = my_strdup(key);
    node->variant = toml_variant_create_float(value);
    node->next = map->nodes[index];
    map->nodes[index] = node; 
}

void toml_map_set_boolean(toml_map_t map, toml_string_t key, toml_boolean_t value)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != nullptr; node = node->next) {
        if (!my_strcmp(node->key, key)) {
            toml_variant_destroy(node->variant);
            node->variant = toml_variant_create_boolean(value);
            return;
        }
    }
    node_t *node = malloc(sizeof(node_t));
    node->key = my_strdup(key);
    node->variant = toml_variant_create_boolean(value);
    node->next = map->nodes[index];
    map->nodes[index] = node; 
}

void toml_map_set_string(toml_map_t map, toml_string_t key, toml_string_t value)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != nullptr; node = node->next) {
        if (!my_strcmp(node->key, key)) {
            toml_variant_destroy(node->variant);
            node->variant = toml_variant_create_string(value);
            return;
        }
    }
    node_t *node = malloc(sizeof(node_t));
    node->key = my_strdup(key);
    node->variant = toml_variant_create_string(value);
    node->next = map->nodes[index];
    map->nodes[index] = node; 
}

void toml_map_set_array(toml_map_t map, toml_string_t key, toml_array_t value)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != nullptr; node = node->next) {
        if (!my_strcmp(node->key, key)) {
            toml_variant_destroy(node->variant);
            node->variant = toml_variant_create_array(value);
            return;
        }
    }
    node_t *node = malloc(sizeof(node_t));
    node->key = my_strdup(key);
    node->variant = toml_variant_create_array(value);
    node->next = map->nodes[index];
    map->nodes[index] = node; 
}

void toml_map_set_map(toml_map_t map, toml_string_t key, toml_map_t value)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != nullptr; node = node->next) {
        if (!my_strcmp(node->key, key)) {
            toml_variant_destroy(node->variant);
            node->variant = toml_variant_create_map(value);
            return;
        }
    }
    node_t *node = malloc(sizeof(node_t));
    node->key = my_strdup(key);
    node->variant = toml_variant_create_map(value);
    node->next = map->nodes[index];
    map->nodes[index] = node; 
}

toml_integer_t toml_map_get_integer(toml_map_t map, toml_string_t key)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != NULL; node = node->next) {
        if (!my_strcmp(node->key, key))
            return node->variant.as.integer;
    }
    return 0;
}

toml_float_t toml_map_get_float(toml_map_t map, toml_string_t key)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != NULL; node = node->next) {
        if (!my_strcmp(node->key, key))
            return node->variant.as.floating;
    }
    return 0.0;
}

toml_boolean_t toml_map_get_boolean(toml_map_t map, toml_string_t key)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != NULL; node = node->next) {
        if (!my_strcmp(node->key, key))
            return node->variant.as.boolean;
    }
    return false;
}

toml_string_t toml_map_get_string(toml_map_t map, toml_string_t key)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != NULL; node = node->next) {
        if (!my_strcmp(node->key, key))
            return node->variant.as.string;
    }
    return nullptr;
}

toml_array_t toml_map_get_array(toml_map_t map, toml_string_t key)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != NULL; node = node->next) {
        if (!my_strcmp(node->key, key))
            return node->variant.as.array;
    }
    return nullptr;
}

toml_map_t toml_map_get_map(toml_map_t map, toml_string_t key)
{
    size_t index = my_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node != NULL; node = node->next) {
        if (!my_strcmp(node->key, key))
            return node->variant.as.map;
    }
    return nullptr;
}
