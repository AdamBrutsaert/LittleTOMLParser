#include <stdio.h>

#include "map/toml_array.h"

int main()
{
    toml_array_t array = toml_array_create();

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

    toml_array_destroy(array);

    return 0;
}
