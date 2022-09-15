#include <stdio.h>

#include "map/toml_variant.h"

int main()
{
    toml_variant_t v = toml_variant_create_float(25.0);
    printf("Float = %f\n", v.as.floating);
    toml_variant_destroy(v);

    return 0;
}
