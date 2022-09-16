#include <stdio.h>

#include "map/toml_map.h"
#include "map/toml_array.h"

int main()
{
    /* toml_array_t array = toml_array_create();

    toml_array_push_integer(array, 25);
    toml_array_push_float(array, 45.0);
    toml_array_push_boolean(array, true);
    toml_array_push_string(array, "hello, world!");
    toml_array_push_array(array, toml_array_create());

    printf("array[0] = %lld\n", toml_array_get_integer(array, 0));
    printf("array[1] = %f\n", toml_array_get_float(array, 1));
    printf("array[2] = %s\n", toml_array_get_boolean(array, 2) ? "true" : "false");
    printf("array[3] = \"%s\"\n", toml_array_get_string(array, 3));
    printf("array[4].length = %lu\n", toml_array_length(toml_array_get_array(array, 4)));

    toml_array_destroy(array); */

    toml_map_t map = toml_map_create();

    toml_map_set_integer(map, "test123456", 3);
    toml_map_set_integer(map, "test123456", 45);

    toml_map_set_float(map, "float", 0.56);
    toml_map_set_float(map, "float", 69.420);

    toml_map_set_boolean(map, "bool", false);
    toml_map_set_boolean(map, "bool", true);

    toml_map_set_string(map, "str", "heyyyyy");
    toml_map_set_string(map, "str", "non");

    toml_map_set_map(map, "yolo", toml_map_create());
    toml_map_set_array(map, "yolo", toml_array_create());

    printf("Integer = %lld\n", toml_map_get_integer(map, "test123456"));
    printf("Float = %f\n", toml_map_get_float(map, "float"));
    printf("Boolean = %s\n", toml_map_get_boolean(map, "bool") ? "true" : "false");
    printf("String = %s\n", toml_map_get_string(map, "str"));
    printf("Array = %p\n", (void*)toml_map_get_array(map, "yolo"));

    toml_map_destroy(map);

    return 0;
}
