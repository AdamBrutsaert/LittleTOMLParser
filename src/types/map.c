#include "toml/map.h"

#include <stdlib.h>

#include "toml/variant.h"
#include "toml/memory.h"
#include "toml/string.h"

typedef struct node {
    char *key;
    toml_variant_t variant;
    struct node *next;
} node_t;

struct toml_map {
    size_t capacity;
    node_t **nodes;
};

toml_map_t *toml_map_create()
{
    toml_map_t *map = malloc(sizeof(struct toml_map));

    map->capacity = 64;
    map->nodes = malloc(map->capacity * sizeof(node_t*));
    toml_memset(map->nodes, 0, map->capacity * sizeof(node_t*));

    return map;
}

void toml_map_destroy(toml_map_t *map)
{
    for (size_t i = 0; i < map->capacity; i++) {
        node_t *next = map->nodes[i];
        for (node_t *node = next; node; node = next) {
            next = node->next;
            free(node->key);
            toml_variant_destroy(node->variant);
            free(node);
        }
    }

    free(map->nodes);
    free(map);
}

static node_t *find(toml_map_t *map, char const *key)
{
    size_t index = toml_strhash(key) % map->capacity;

    for (node_t *node = map->nodes[index]; node; node = node->next) {
        if (!toml_strcmp(node->key, key))
            return node;
    }

    return nullptr;
}

toml_boolean_t toml_map_exists(toml_map_t *map, char const *key)
{
    return find(map, key) != nullptr;
}

toml_type_t toml_map_get_type(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.type;
}

toml_integer_t toml_map_get_integer(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.as.integer;
}

toml_float_t toml_map_get_float(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.as.floating;
}

toml_string_t toml_map_get_string(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.as.string;
}

toml_boolean_t toml_map_get_boolean(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.as.boolean;
}

toml_array_t *toml_map_get_array(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.as.array;
}

toml_map_t *toml_map_get_map(toml_map_t *map, char const *key)
{
    return find(map, key)->variant.as.map;
}

static void append_node(toml_map_t *map, char *key, toml_variant_t variant)
{
    node_t *node = find(map, key);

    if (node) {
        toml_variant_destroy(node->variant);
        node->variant = variant;
        return;
    }

    size_t index = toml_strhash(key) % map->capacity;

    node = malloc(sizeof(node_t));
    node->key = key;
    node->variant = variant;
    node->next = map->nodes[index];
    map->nodes[index] = node;
}

void toml_map_set_integer(toml_map_t *map, char *key, toml_integer_t value)
{
    append_node(map, key, toml_variant_create_integer(value));
}

void toml_map_set_float(toml_map_t *map, char *key, toml_float_t value)
{
    append_node(map, key, toml_variant_create_float(value));
}

void toml_map_set_string(toml_map_t *map, char *key, toml_string_t value)
{
    append_node(map, key, toml_variant_create_string(value));
}

void toml_map_set_boolean(toml_map_t *map, char *key, toml_boolean_t value)
{
    append_node(map, key, toml_variant_create_boolean(value));
}

void toml_map_set_map(toml_map_t *map, char *key, toml_map_t *value)
{
    append_node(map, key, toml_variant_create_map(value));
}

void toml_map_set_array(toml_map_t *map, char *key, toml_array_t *value)
{
    append_node(map, key, toml_variant_create_array(value));
}
