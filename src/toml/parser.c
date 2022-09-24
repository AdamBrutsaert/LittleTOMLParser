#include "toml/parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "toml/reader.h"
#include "toml/tokenizer.h"
#include "toml/variant.h"
#include "utils/my_lib.h"

typedef struct {
    toml_map_t root;
    toml_map_t current;
} context_t;

static char *parse_key(toml_tokenizer_t tokenizer)
{
    toml_token_t token = toml_tokenizer_next(tokenizer);
    return token.buffer; 
}

static toml_variant_t parse_value(toml_tokenizer_t tokenizer)
{
    toml_token_t token = toml_tokenizer_next(tokenizer);
    while (!toml_tokenizer_reached_end(tokenizer) && token.type != TOML_TOKEN_TYPE_NEWLINE) {
        toml_token_destroy(token);
        token = toml_tokenizer_next(tokenizer);
    }
    toml_token_destroy(token);

    return toml_variant_create_integer(0);
}

static void parse_keyval(context_t *ctx, toml_tokenizer_t tokenizer)
{
    // peek 0 -> string <dot string>...
    char *key = parse_key(tokenizer);

    // peek 1 -> equal (TODO verify that its indeed equal)
    toml_token_t token = toml_tokenizer_next(tokenizer);
    toml_token_destroy(token);

    // peek 2 -> string | LBRACE | LBRACKET (TODO verify the token is indeed one of the previous)
    toml_variant_t variant = parse_value(tokenizer);

    toml_map_set_integer(ctx->current, key, variant.as.integer);
    free(key);
}

toml_map_t toml_parse(char const *file)
{
    context_t ctx;
    ctx.root = toml_map_create();
    ctx.current = ctx.root;

    toml_reader_t reader = toml_reader_create(file);
    toml_tokenizer_t tokenizer = toml_tokenizer_create(reader);

    while (!toml_tokenizer_reached_end(tokenizer)) {
        parse_keyval(&ctx, tokenizer);
    }
    
    toml_tokenizer_destroy(tokenizer);
    toml_reader_destroy(reader);

    return ctx.root;
}
